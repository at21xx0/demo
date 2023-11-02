"use strict";
var fs = require('fs');
var path = require('path');
var crypto = require('crypto');
var url = require('url');
var querystring = require('querystring');
var http = require('http');
var process = require('process');
var os = require('os');
var lib = require('./lib.js');


var _server_root = path.resolve('.');

let passwd = Buffer.alloc(9);
crypto.randomFillSync(passwd);
let file_json = path.join(__dirname, 'file.json');
let files_json = path.join(__dirname, 'files.json');
let file_obj = (fs.existsSync(file_json))?JSON.parse(fs.readFileSync(file_json)):{}
let file_user = file_obj.user||{};
let file_token = {'custom-token': {absPath: false, user: 'custom', allowFiles: {}}}; // file_obj.token
let upload_files = (fs.existsSync(files_json))?JSON.parse(fs.readFileSync(files_json)):{};
file_user['custom'] = {absPath: false, passwd: passwd.toString('base64')};
crypto.randomFillSync(passwd);
file_user.admin = {absPath: true, passwd: passwd.toString('base64')};
function saveJSON() {
	fs.writeFileSync(file_json, JSON.stringify({user: file_user}));
	fs.writeFileSync(files_json, JSON.stringify(upload_files));
}
process.on('exit', saveJSON);
setInterval(saveJSON, 60000);
console.log('user: admin\npasswd: %s', passwd.toString('base64'));
{
	let user = Object.keys(file_user);
	let fpath = path.join(_server_root, 'Users');
	fs.readdir(fpath, function(err, files) {
		if(err)
			files = [];
		for(let i = 0, j = user.length;i !== j;i++) {
			let u = user[i];
			if(files.indexOf(u) !== -1)
				continue;
			fs.mkdir(fpath + path.sep + u, {recursive: true}, function(err) {
				if(err)
					throw err;
			});
		}
	});
}
file_obj = null;

function getToken(token_str) {
	let token = null;
	if(!token_str || !(token = file_token[token_str]))
		return null;
	else if(!file_user[token.user]) { // || token.now < Date.now();
		delete file_token[token_str];
		return null;
	}
	return token;
}
function pathPerm(fpath, token, pathname = false) {
	if(pathname === true)
		fpath = path.join(_server_root, fpath);
	return (token.absPath || fpath.indexOf(path.join(_server_root, 'Users', token.user)) === 0);
}

function v7_user(request, response) {
	if(request.method !== 'POST') {
		response.writeHead(405, {"Content-Type": "text/plain"});
		response.end('405 Method Not Allowed.');
	}
	let bufs = [];
	request.on('data', function(data) {
		bufs.push(data);
	});
	request.on('end', function() {
		console.log('cookie', request.headers['cookie']);
		let buf = Buffer.concat(bufs);
		let query = querystring.parse(buf.toString());
		let user = decodeURI(query.user);
		let passwd = decodeURI(query.pass);
		let action = query.action;
		let cookie = ['file_user=;expires=Thu, 01 Jan 1970 00:00:00 GMT;path=/', 'file_token=;expires=Thu, 01 Jan 1970 00:00:00 GMT;path=/'];
		let lastError = '';
		if(action === 'logout')
			void(0);
		else if(file_user[user] === undefined) {
			const user_reg = /^[^\/\\:*?<>|]{1,30}$/;
			action = 'register';
			if(!user_reg.test(user))
				lastError = 'error: username is invalid';
			else {
				fs.mkdir(path.join(_server_root, 'Users', user), {recursive: true}, function(err) {
					console.log(err);
				});
				file_user[user] = {absPath: false, passwd: query.pass, user:user};
			}
		} else if(file_user[user].passwd !== passwd)
				lastError = 'error: password incorrect';
		if(lastError !== '') {
			response.writeHead(200, {"Content-Type": "text/html"});
			response.end('<!DOCTYPE html><html><head><title>Error</title></head><head><body><span>' + lastError + '</span></body></html>');
			return;
		}
		if(action === 'login' || action === 'register') {
			let token = Buffer.alloc(16);
			crypto.randomFillSync(token);
			let t = token.toString('hex');
			let d = new Date();
			d.setDate(d.getDate() + 3);
			let tm1 = d.toUTCString();
			cookie = ['file_user=' + user + ';expires=' + tm1 + ';path=/', 'file_token=' + t + ';expires=' + tm1 + ';path=/'];
			file_token[t] = {absPath: file_user[user].absPath, user: user, allowFiles: {}}; // now: d.getTime()
		} else if(action === 'logout') {
		} else if(action === 'close') {
			if(file_user[user].absPath) {
				response.writeHead(200, {"Content-Type": "text/plain"});
				response.end('failed.');
				return;
			}
			delete file_user[user];
		} else 
			action = 'unknown';

		response.writeHead(200, {"Content-Type": "text/html", "Set-Cookie": cookie});
		response.end('<!DOCTYPE html><html><head><title>message</title></head><body><span>' + action + ': ' + user + '</span></body></html>');
	});
}
function jsonAction(request, response, callback) {
	let recv = '';
	let write = false;
	let cb = function(data) {
		if(write === true)
			return;
		write = true;
		response.writeHead(200, {"Content-Type": "application/json"});
		if(!data) {
			response.end('{}');
		} else if(typeof data === 'object') {
			response.end(JSON.stringify(data));
		} else if(typeof data === 'string') {
			response.end(data);
		}
	}
	request.on('data', function(data) {
		recv += data.toString();
		// if(recv.length > 10000)
	});
	request.on('end', function() {
		let obj;
		let path = '';
		try { 
			obj = JSON.parse(recv);
		} catch(e) {
			cb('{"err": "JSON.parse()"}');
			return;
		}
		let r = callback(obj, cb);
		if(r)
			cb(r);
	});
}
function v7_path(request, response) {
	const convertF = function(fn, stats) { return {fn: fn, isDir: stats.isDirectory(), size: stats.size, ctime: stats.ctime}; };
	jsonAction(request, response, function(obj, cb) {
		let fpath = '';
		let action = obj.action || 'stat';
		let token = getToken(obj.token);
		let ecb = function(err) {
			if(err) 
				cb('{"err": "failed"}');
			else
				cb('{"message": "done"}');
		};
		// console.log(obj);
		const pd = '{"err": "Permission denied"}';
		if(!obj.path)
			return '{"err": "path is required."}';
		if(obj.absPath === true) {
			if(user === '')
				return '{"err": "invalid token"}';
			fpath = obj.path;
		} else
			fpath = path.join(_server_root, obj.path);
		if(action === 'stat') {
			lib.pstatConvert(fpath, convertF, function(err, ret) {
				if(err) {
					cb('{}');
				} else {
					ret.stats = null;
					cb(ret);
				}
			});
			return;
		}
		if(token === null)
			return '{"err": "invalid token"}';
		if(!Array.isArray(obj.files))
			return '{"err": "files is required"}';
		if(action === 'delete') {
			if(!pathPerm(fpath, token))
				return pd;
			lib.rmPath(fpath, obj.files, ecb);
			return;
		}
		if(!obj.dst)
			return '{"err": "dst is required"}';
		let dst = obj.dst;
		let files = obj.files;
		if(action === 'mkdir') {
			if(!pathPerm(fpath, token))
				return pd;
			fs.mkdir(path.join(fpath, dst), {recursive: true}, ecb);
		} else if(action === 'rename') {
			if(!pathPerm(fpath, token))
				return pd;
			fs.rename(path.join(fpath, files[0]), path.join(fpath, dst), ecb);
		} else if(action === 'move') {
			dst = path.join(_server_root, dst);
			if(!pathPerm(fpath, token) || !pathPerm(dst, token))
				return pd;
			let lastError = null;
			let ct = files.length
			for(let i = 0, j = ct;i !== j;i++) {
				fs.rename(path.join(fpath, files[i]), path.join(dst, files[i]), function(err) {
					if(err)
						lastError = err;
					if(--ct === 0)
						ecb(err);
				});
			}
		} else if(action === 'copy') {
			dst = path.join(_server_root, dst);
			if(!pathPerm(dst, token))
				return pd;
			let lastError = null;
			let ct = files.length;
			for(let i = 0, j = ct;i !== j;i++) {
				lib.cpPath(path.join(fpath, files[i]), path.join(dst, files[i]), function(err) {
					if(err)
						lastError = err;
					if(--ct === 0)
						ecb(err);
				});
			}
		} else 
			return '{"err": "unknown action: ' + action + '"}';
	});
}
function v7_upload2(request, response) {
	if(request.method !== "POST") {
		response.writeHead(405, {"Content-Type": "text/plain"});
		response.end('405 Method Not Allowed.');
		return;
	}
	if(request.headers['content-type'] === 'application/json')
		return jsonAction(request, response, function(obj, cb) {
			// console.log(obj);
			let token = getToken(obj.token);;
			if(!obj.path || typeof obj.path !== 'string')
				return '{"err": "path is required"}';
			else if(token === null)
				return '{"err": "invalid token"}';
			else if(!pathPerm(obj.path, token, true))
				return '{"err": "Permission denied"}';
			else if(!Array.isArray(obj.files) && obj.files.length === 0) {
				return '{"err": "file is required"}';
			}
			let files = obj.files;
			let ct = files.length;
			let list = {};
			let listPush = function(fpath, file) {
				list[file.fn] = file;
				if(file.done === false)
					token.allowFiles[file.md5] = {fpath: fpath, size: file.size, flags: ((file.start === 0)?'w':'a')};
				if(--ct === 0) {
					cb(JSON.stringify({err: null, files: list}));
				}
			}
			for(let i = 0, j = ct;i !== j;i++) {
				let file = obj.files[i];
				if(file === null || typeof file !== 'object' || typeof file.size !== 'number' || typeof file.fn !== 'string' || typeof file.md5 !== 'string')
					return '{"err": "json_err"}';
				file.done = false;
				file.start = 0;
				let fpath = path.join(obj.path, file.fn);
				let path1 = path.join(_server_root, fpath);
				fs.exists(path1, function(e) {
					let t = upload_files[file.md5];
					if(e) {
						if(!t || t.size === file.size) {
							fs.stat(path1, function(err, stats) {
								if(err) 
									void(0);
								else if(stats.size < file.size)
									file.size = stats.size;
								else
									file.done = true;
								listPush(fpath, file);
							});
							return; 
						}						file.done = true;
					} else if(t && t.size === file.size && fpath !== t.fpath) {
						let path2 = path.join(_server_root, t.fpath);
						fs.exists(path2, function(e) {
							if(e)
								file.done = true;
							else
								delete upload_files[file.md5];
							fs.link(path2, path1, function(err) {
								if(!err) return;
								fs.copyFile(path2, path1, (e) => 0);
							});
							listPush(fpath, file);
						});
						return;
					}
					listPush(fpath, file);
				});
			}
			// return obj;
		});
	let data = {};
	let prevName = null;
	let s = '';
	let dirs = [];
	let lastError = null;
	let token = null;
	let json = null;
	let failedList = [];
	let prevFileMD5 = null;
	let retJSON = function(json) {
		response.writeHead(200, {"Content-Type": "application/json"});
		if(typeof json === 'string')
			response.end(json);
		else
			response.end(JSON.stringify(json));
	}
	lib.formDataParse(request, function(obj) {
		if(prevName !== null) {
			// if(prevIsFile)
			data[prevName] = s;
			s = '';
			if(prevName === 'json') {
				try {
					json = JSON.parse(data.json);
				}catch(e) {
					void(e);
				}
				if(json === null) 
					lastError = 'JSON.parse()';
				else if((token = getToken(json.token)) === null)
					lastError = 'invalid token';
				else if(!json.path)
					lastError = 'path is require';
				else if(!pathPerm(json.path, token, true))
					lastError = 'Permission denied';
				else if(json.files === null || typeof json.files !== 'object')
					lastError = 'files is required';
				if(lastError !== null)
					json = null, token = null;
			}
			prevName = null;
		} else if(prevFileMD5 !== null) {
			let file = token.allowFiles[prevFileMD5];
			delete file.flags;
			upload_files[prevFileMD5] = file;
			delete token.allowFiles[prevFileMD5];
			prevFileMD5 = null;
		}
		if(obj === null)
			return;
		if(obj.filename) {
			let file = null;
			let md5 = '';
			const invalid = (data) => data.length;
			if(json !== null) {
				file = json.files[obj.filename];
				if(file) {
					md5 = file.md5;
					file = token.allowFiles[file.md5];
				}
			}
			if(!file) {
				failedList.push(obj.filename);
				return invalid;
			}
			let fpath = path.join(_server_root, file.fpath);
			let dir1 = path.dirname(fpath);
			// let wcb = fopen
			let resumeStream = function(ret = false) {
				prevFileMD5 = md5;
				let wStream = fs.createWriteStream(fpath, {flags: file.flags});
				if(ret === true)
					return wStream;
				else
					obj.pipe(wStream);
			}
			if(dirs.indexOf(dir1) !== -1)
				return resumeStream(true);
			fs.exists(dir1, function(e) {
				if(e) {
					dirs.push(dir1);
					resumeStream();
					return;
				}
				fs.mkdir(dir1, {recursive: true}, function(err) {
					if(err) {
						failedList.push(obj.filename);
						obj.pipe(invalid);
					} else {
						dirs.push(dir1);
						resumeStream();
					}
				});
			});
			return false; // async
		}
		prevName = obj.name;
		return (data) => s += data.toString(); // invalid
	}, function(err) {
		retJSON({err: lastError || err, failedList: failedList});
	});
}
var l_map = {'/api/v7/user': v7_user, '/api/v7/upload2': v7_upload2, '/api/v7/path': v7_path};



function fileSort(list, sort='') {
	let len = list.length;
	let border = len;
	let subsort = null;
	if(sort.search('r') !== -1) {
		// s d n
		if(sort.search('s') !== -1)
			subsort = (a, b) => b.size - a.size;
		else if(sort.search('t') !== -1)
			subsort = (a, b) => b.ctime - a.ctime;
		else // id (sort.search('n') !== -1)
			subsort = (a, b) => b.fn.localeCompare(a.fn);
	} else {
		if(sort.search('s') !== -1)
			subsort = (a, b) => a.size - b.size;
		else if(sort.search('t') !== -1)
			subsort = (a, b) => a.ctime - b.ctime;
		else
			subsort = (a, b) => a.fn.localeCompare(b.fn);
	}
	if(sort.search('T') === -1)
		list.sort(subsort);
	else
		list.sort(function(a, b) {
				return (b.isDir - a.isDir) || subsort(a, b);
		});
}


let htmlO = lib.htmlObj2('file.html', true);
htmlO.sparkMD5min = fs.readFileSync('spark-md5-min.js').toString();
htmlO.file_js = fs.readFileSync('file_js.js').toString();
http.createServer(function(request, response){
	const convertF = function(fn, stats) { return {fn: fn, size: stats.size, ctime: stats.ctime, isDir: stats.isDirectory()}; };
	let u = url.parse(request.url, true);
	let pathname = decodeURI(u.pathname);
	let sort = u.query['sort'];
	let f = l_map[pathname];
	if(request.method === 'POST' && f)
		return f(request, response);
	var fpath = path.join(_server_root, pathname);
	console.log("fpath: ", fpath);
	if(fpath.length < _server_root.length) {
		response.writeHead(403, {"Content-Type": "text/plain"});
		response.end('403 Forbidden.');
		return;
	}
	// if(pathname.indexOf('/file.json') === 0) return;
	lib.pstatConvert(fpath, convertF, function(err, ret) {
		if(err) {
			response.writeHead(404, {"Content-Type": "text/plain"});
			response.end('404 Not Found.');
			return;
		}
		/*
		if(!stats.isFile())
		{
			response.writeHead(400, {"Content-Type": "text/plain"});
			response.end('400 Bad Request.');
			return;
		}
		else */
		if(!ret.files) {
			lib.sendFile(request, response, fpath, ret.stats);
			return;
		}
		//response.writeHead(200, {"Content-Type": "application/json"});
		//response.end(JSON.stringify(ret));
		let html = '';
		let search = u.search||'';
		let files = ret.files;
		fileSort(files, sort);
		if(u.query['page'] === 'menu') {
			htmlO.checkbox = '<td><input type="checkbox" /></td>';
			htmlO.script = htmlO.menu;
		} else {
			htmlO.checkbox = '';
			let i = search.indexOf('page=');
			if(i === -1)
				search = (search.length === 0)?'?page=menu':search + '&page=menu';
			else {
				let e = search.indexOf('&', i);
				e = (e === -1)?search.length:e;
				search = search.slice(0, i) + 'page=menu' + search.slice(e);
			}
			htmlO.script = '<a href="./' + search + '">menu</a><br>';
		}
		htmlO.updir = '../' + search;
		htmlO.n = 0;
		htmlO.title = pathname;
		htmlO.list = function() {
			let file = files[this.n];
			if(!file) {
				// this.n = 0;
				return false;
			}
			const sizeArr = ['B', 'KB', 'MB', 'GB', 'TB'];
			let suffix1 = (file.isDir)?'/':'';
			let size = file.size;
			let n = 0;
			this.n++;
			while(size > 1024 && n !== 4) {
				size /= 1024;
				n++;
			}
			size = size.toFixed(2);
			this.href = encodeURI(file.fn + ((file.isDir)?'/' + search:''));
			this.size = size.toString() + sizeArr[n];
			this.ctime = file.ctime.toUTCString();
			this.fn = file.fn + ((file.isDir)?'/':'');
			// Object.assign(this, {href: ''});
			return true;
		};
		response.writeHead(200, {"Content-Type": "text/html"});
		response.end(htmlO.index);
	});
	return;
}).listen(8080);

(function(proto, port) {
	let tmp = Object.values(os.networkInterfaces());
	for(let values of tmp)
		for(let value of values) {
			let url = proto + '://' + ((value.family === 'IPv6')?'[' + value.address + ']':value.address) + ':' + port.toString() + '/';

			console.log(url);
		}
})("http", 8080);




