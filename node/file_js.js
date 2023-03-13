function cookie1(name, value = null, d = -1, path = '', domain = '', sec = false) {
	if(value === null) {
		let arr = document.cookie.split(';');
		let k = name + '=';
		for(let i = 0, j = arr.length; i !== j;i++) {
			let s = arr[i].trim();
			if(s.indexOf(k) === 0)
				return s.slice(k.length);
		}
		return '';
	} else {
		let s = '';
		// if(value === '') d = 0;
		if(d instanceof Date)
			s = '; expires=' + d.toUTCString();
		else if(isNaN(d) === false)
			s = '; max-age=' + d.toString();
		let secure = (sec === true)?'secure':'';
		document.cookie = name + '=' + value + s + (path && ';path=' + path) + (domain && ';domain=' + domain) + s;
	}
}
function childEle() { // parent, n, n ...n // parent[n][n][n]
	if(!arguments[0])
		return undefined;
	let nodes = arguments[0].childNodes;
	if(arguments.length === 1) {
		let ret = [];
		for(let i = 0, j = nodes.length;i !== j;i++) {
			if(nodes[i].nodeType === 1)
				ret.push(nodes[i]);
		}
		return ret; // return arguments.children
	}
	for(let t = 1, k = arguments.length;;) {
		let i = 0, n = arguments[t] + 1;
		for(let j = nodes.length;i !== j;i++) {
			if(nodes[i].nodeType === 1 && --n === 0)
				break;
		}
		t++;
		if(n !== 0)
			return undefined;
		if(t === k)
			return nodes[i];
		else
			nodes = nodes[i].childNodes;
	}
	return undefined;
}
function getCheckedFiles() {
	let files = [];
	const elements = childEle(document.getElementById('files')); // .children
	const nodes = (elements[0].nodeName === 'TBODY')?childEle(elements[0]):elements;
	for(let i = 1, j = nodes.length;i !== j;i++) {
		if(childEle(nodes[i], 0, 0).checked === true)
			files.push(childEle(nodes[i], 1, 0).innerText); //nodes[i].children[1].children[0].innerText);
	}
	return files;
}
function unchecked() {
	const range = document.getElementById('files');
	let arr = range.getElementsByTagName('input');
	for(let i = 0, j = arr.length;i !== j;i++) {
		if(arr[i].checked === true)
			arr[i].checked = false;
	}
}
let lastAction = '';
let lastChoosePath = '';
let lastInputOnly = false;
let user = cookie1('file_user');
if(user)
	document.getElementById('username').value = user;
function chooseAction(action, s = '', inputOnly = false) {
	const hint = document.getElementById('choose_hint');
	const choose_div = document.getElementById('choose_div');
	const choose_path = document.getElementById('choose_path');
	const files = document.getElementById('files');
	console.log('choose', action, s);
	if(action === 'choose') {
		lastAction = s;
		files.className = 'hide';
		choose_div.className = 'show';
		lastInputOnly = inputOnly;
		if(s === 'mkdir')
			hint.innerText = 'mkdir:';
		else if(s === 'rename')
			hint.innerText = 'name:';
		else
			hint.innerText = 'path:';
		if(inputOnly === false)
			chooseAction('cpath', location.pathname);
		return;
	} else if(action === 'cancel') {
		choose_div.className = 'hide';
		files.className = 'show';
		lastChoosePath = '';
		return;
	} else if(action === 'ok') {
		choose_div.className = 'hide';
		files.className = 'show';
		lastChoosePath = '';
		fileAction(lastAction, choose_path.value);
		return;
	} else if(action === 'click') {
		let e = event.target;
		let fn = childEle(e.parentNode, 1).innerText;
		let path = lastChoosePath + fn;
		if(fn === '../') {
			path = (lastChoosePath === '/')?'/':lastChoosePath.slice(0, lastChoosePath.lastIndexOf('/', lastChoosePath.length - 2) + 1);
		}
		choose_path.value = path;
		if(e.tagName === 'A' && fn[fn.length - 1] === '/') {
			chooseAction('cpath', path);
		}
		return;
	} else if(action === 'cpath' && lastChoosePath === s)
		return;
	else if(lastInputOnly !== false)
		return chooseAction('ok');
	console.log('ac', action, lastInputOnly);
	let func = function(text) {
		const values = document.getElementById('choose_values');
		let obj = JSON.parse(text);
		if(obj.file)
			obj.files = [obj.file];
		let files = obj.files;
		let path = (lastChoosePath[lastChoosePath.length - 1] === '/')?lastChoosePath:lastChoosePath + '/';
		let html = '<div><input type="radio" name="choose"><a href="javascript: void(0);">../</a></div>';
		lastChoosePath = path;
		if(!obj.files) {
			values.innerHTML = html;
			return;
		}
		obj.files.sort(function(a, b) {
			return b.isDir - a.isDir || a.fn.localeCompare(b.fn);
		});
		for(let i = 0, j = files.length;i !== j;i++) {
			let file = files[i];
			let fn = file.fn + ((file.isDir)?'/':'');
			html += '<div><input type="radio" name="choose"><a href="javascript: void(0);">' + fn + '</a></div>';
		}
		values.innerHTML = html;
	}
	let xhr = new XMLHttpRequest();
	xhr.open('POST', '/api/v7/path', true);
	xhr.setRequestHeader('Content-Type', 'application/json');
	xhr.onreadystatechange = function() {
		if(xhr.readyState === 4 && xhr.status === 200) {
			func(xhr.responseText);
		}
	}
	lastChoosePath = s;
	choose_path.value = lastChoosePath;
	xhr.send(JSON.stringify({action: 'stat', path: s}));
}
function fileAction(action, dst) {
	if(!dst) {
		if(action === 'upload') {
			const upload_div = document.getElementById('upload_div');
			upload_div.className = 'show';
			return;
		} else if(action !== 'delete' && action !== 'upload')
			return chooseAction('choose', action, (action === 'mkdir' || action === 'rename'));
	}
	let message = function(msg) {
		let message = document.getElementById('message');
		message.contentWindow.document.open();
		message.contentWindow.document.write('<!DOCTYPE html><html><head><title>message</title></head><body><span>' + msg + '</span></body></html>');
		message.contentWindow.document.close();
	}
	let xhr = new XMLHttpRequest();
	xhr.open('POST', '/api/v7/path', true);
	xhr.setRequestHeader('Content-Type', 'application/json');
	xhr.onreadystatechange = function() {
		if(xhr.readyState === 4 && xhr.status === 200) {
			let obj = JSON.parse(xhr.responseText);
			let msg = (obj.err && 'err: ' + obj.err)||obj.message||'unknown_error';
			message(msg);
			if(!obj.err)
				setTimeout(location.reload.bind(location, true), 500);
		}
	}
	xhr.onerror = function(e) {
		message('XMLHttpRequest ' + e.type + ': ' + e.loaded.toString() + ' loaded');
	};
	let files = getCheckedFiles();
	unchecked();
	if(files.length === 0 && action !== 'mkdir')
		return message('files: []');
	else if(action === 'rename' && files.length !== 1) {
		return message('files_length === 1');
	}
	xhr.send(JSON.stringify({action: action, path: location.pathname, files: files, dst: dst, token: cookie1('file_token')}));
}



function md5F(file, callback) {
	const slice = File.prototype.slice || File.prototype.mozSlice || File.prototype.webkitSlice;
	const bz = 20971520; // 20MB
	let size = file.size, start = 0, end = bz;
	if(size === 0) {
		callback(null, 'd41d8cd98f00b204e9800998ecf8427e');
		return;
	}
        let spark = new SparkMD5.ArrayBuffer();
	let reader = new FileReader();
	let oldCallback = callback;
	let next = function() {
		if(start >= size) 
			return false;
		if(end > size)
			end = size;
		reader.readAsArrayBuffer(slice.call(file, start, end));
		start += bz;
		end = start + bz;
		return true;
	};
	reader.onload = function(e) {
		spark.append(e.target.result);
		if(next() === false)
			callback(null, spark.end());
	};
	reader.onerror = function() {
		callback(reader.error);
	};
	next();
}
// md5(file, function(err, ret) { console.log(err, ret); });


function getUploadFiles(callback) {
	const d = document.getElementById('upload_div_1');
	const ei = document.getElementById('upload_input_1');
	ei.onchange = function(e) {
		callback(ei.files);
	}
	d.ondragover = function(){
		this.className = 'l_blue';
		return false;
	}
	d.ondragend = function(){
		this.className = 'l_white';
		return false;
	}
	d.ondrop = function(e){
		this.className = 'l_white';
		e.preventDefault();
		e.stopPropagation();
		//none copy copyLink copyMove link linkMove move all uninitialized
		let trans = e.dataTransfer;
		var files = [];
		var rCount = 0;
		var loopF = function(entry) {
			if (entry.isFile) {
				rCount++;
				entry.file((file) => {
					let path = entry.fullPath;
					if(path[0] === '/')
						path = path.slice(1);
					files.push(new File([file], path, {type:file.type}));
					rCount--;
					if(rCount === 0)
						callback(files);
				});
			} else if(entry.isDirectory){
				let reader = entry.createReader();
				reader.readEntries((entries) => {
					entries.forEach((entry) => loopF(entry));
				}, e => { console.log(e); });
			}
		}
		for(let i = 0; i < trans.items.length;i++) {
			let item = trans.items[i];
			if(item.kind === 'string') {
				item.getAsString(function(s) {
					console.log(item.type, s);
				});
				return;
			} else if(item.kind === 'file') {
				loopF(item.webkitGetAsEntry());
				/*
				let entry = item.webkitGetAsEntry();
				if(entry.isFile)
					files.push(item.getAsFile());
				*/
			}
		}
		return false;
	}
}

const show = document.getElementById('upload_files');
var Files = [];
function recvFile(files) {
	Array.prototype.push.apply(Files, files);
	let str = '';
	for(let i = 0;i < Files.length;i++) {
		str += Files[i].name + '\t' + Files[i].size + '\n';
	}
	show.innerText = str;
}
getUploadFiles(recvFile);
function sendF() {
	// sendFiles(Files);
	if(Files.length === 0)
		return;
	let arr = [];
	const upload_message = document.getElementById('upload_message');
	let send = function(res) {
		console.log(res);
		let obj = JSON.parse(res);
		if(obj.err) {
			upload_message.innerText = obj.err;
			return;
		} else if(!obj.files) {
			upload_message.innerText = 'server_error';
			return;
		}
		let arr = [];
		let files = obj.files;
		for(let i = 0, j = Files.length;i !== j;i++) {
			let t = files[Files[i].name];
			if(t && t.done === false)
				arr.push(Files[i]);
		}
		sendFiles(files, Files);
		Files = [];
		recvFile(arr);
	}
	let xhr = new XMLHttpRequest();
	xhr.open('POST', '/api/v7/upload2', true);
	xhr.setRequestHeader('Content-Type', 'application/json');
	xhr.onreadystatechange = function() {
		if(xhr.readyState === 4 && xhr.status === 200) {
			send(xhr.responseText);
		}
	};
	let ct = Files.length;
	let lastError = null;

	let pathname = location.pathname;
	let token = cookie1('file_token');
	if(!token) {
		token = 'custom-token';
		pathname = '/Users/custom';
	}
	upload_message.innerText = 'md5';
	for(let i = 0, j = ct;i !== j;i++) {
		let file = Files[i];
		md5F(file, function(err, md5) {
			if(err)
				lastError = err;
			else
				arr.push({fn: file.name, size: file.size, md5: md5});
			if(--ct === 0)
				xhr.send(JSON.stringify({path: pathname, token: token, files: arr}));
		});
	}
}
function sendFiles(obj, files) {
	const slice = File.prototype.slice || File.prototype.mozSlice || File.prototype.webkitSlice;
	const rElement = document.getElementById('upload_range');
	const upload_message = document.getElementById('upload_message');
	if(files.length === 0) {
		upload_message.innerText = 'done.';
		Files = [];
		recvFile([]);
		return;
	}
	let uploadFiles = {};
	let fileList = [];
	for(let i = 0, j = files.length;i !== j;i++) {
		let file = files[i];
		let t = obj[file.name];
		if(!t || t.done === true)
			continue;
		else if(t.start !== 0)
			file = slice.call(file, t.start, file.size);
		uploadFiles[file.name] = t;
		fileList.push(file);
		// file.name file.size type
	}
	if(fileList.length === 0) {
		upload_message.innerText = 'done.';
		Files = [];
		recvFile([]);
		return;
	}
	let formData = new FormData();
	let pathname = location.pathname;
	let token = cookie1('file_token');
	if(!token) {
		token = 'custom-token';
		pathname = '/Users/custom';
	}
	formData.append("json", JSON.stringify({path: pathname, token: token, files: uploadFiles}));
	// formData.append('username', 'name');
	for(let i = 0, j = fileList.length;i !== j;i++)
		formData.append("file", fileList[i]);
	var req = new XMLHttpRequest();
	req.open("POST", "/api/v7/upload2");
	req.onreadystatechange = function() {
		if(req.readyState === 4 && req.status === 200) {
			let obj = JSON.parse(req.responseText);
			let failedList = obj.failedList;
			let arr = [];
			for(let i = 0, j = Files.length;i !== j;i++) {
				let file = Files[i];
				if(failedList.indexOf(file.name !== -1))
					arr.push(file);
			}
			Files = [];
			recvFile(arr);
			if(obj.err)
				upload_message.innerText = obj.err;
			else 
				upload_message.innerText = 'done.';

		}

	}
	req.upload.onprogress = function(e) {
		if(e.lengthComputable) {
			rElement.value = (e.loaded / e.total * 100);
		}
	}
	req.send(formData);
}



