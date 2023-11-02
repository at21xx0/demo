"use strict";
var fs = require('fs');
var path = require('path');

function htmlObj2IterF(iter, f) {
	let s = '';
	while(iter.call(this)) {
		s += f.call(this);
	}
	return s;
}

function htmlObj2(str, isPath = false, obj) {
	const markL = '<!--JS_MARK_';
	const markR = '-->';
	const varL = '<!--JS_VAR_';
	const varR = '-->';
	if(isPath === false)
		void(0);
	else if(typeof str === 'array') {
		let arr = str;
		str = '';
		for(let i = 0, j = arr.length;i !== j;i++) {
			let v = fs.readFileSync(arr[i]).toString();
			str += makrL + arr[i] + markR + v; 
		}
	} else
		str = fs.readFileSync(str).toString();
	let arr = str.split(markL);
	let ret = obj || {};
	let key = [], func = [];
	ret.get = function(name){return this[name];};
	ret.setF = function(key, f) {
		const invalid = (d) => undefined;
		Object.defineProperty(this, key, {
			configurable: true,
			get: f,
			set: invalid
		});
	};
	for(let i = 0, j = arr.length;i !== j;i++) {
		let s = arr[i];
		let pos = s.indexOf(markR);
		if(pos === -1)
			continue;
		let mark = s.slice(0, pos);
		if(mark.indexOf('<!--') !== -1) continue;
		s = s.slice(pos + 3);
		let end = 0, bz = 0;
		let ar = [];
		pos = 0;
		end = s.indexOf(varL, pos);
		if(end === -1) {
			ret[mark] = s;
			continue;
		}
		let f = 'function(){return \'\'';
		while(1) {
			if(end === -1)
				end = s.length;
			if(pos !== end)
				f += '+\'' + s.slice(pos, end).replace(/'/g, '\\\'').replace(/\n/g, '\\n') + '\''; // replaceAll('\'', '\\\'');
			if(end === s.length)
				break;
			pos = s.indexOf(varR, end + 11);
			if(pos === -1)
				throw new Error('excepted token \'' + varR + '\'');
			f += '+this.' + s.slice(end + 11, pos);
			pos = pos + 3;
			end = s.indexOf(varL, pos);
		}
		f += ';}';
		/*
		let f = 'function(){return `';
				let rarr = s.slice(pos, end).split('`');
				if(rarr.length === 1) {
					f += rarr[0];
				} else {
					let rs = '';
					for(let i = 1, j = rarr.length;i < j;i += 2)
						rarr[i] = rarr[i].replaceAll('${', '\\${');;
					f += rarr.join('');
			f += '${this.' + s.slice(end + 11, pos) + '}';
		f += '`;}';
		*/
		key.push(mark);
		func.push(f);
	}
	if(key.length !== 0) {
		let funcArr = eval('([' + func.join(',') + '])');
		for(let i = 0, j = key.length;i !== j;i++) {
			let k = key[i];
			let fn = funcArr[i];
			let setter = function(iter) {
				Object.defineProperty(ret, k, {
					configurable: true,
					get: htmlObj2IterF.bind(ret, iter, fn),
					set: setter
				});
			};
			Object.defineProperty(ret, k, {
				configurable: true,
				get: fn, 
				set: setter
			});
		}
	}
	return ret;
}

function htmlObjGet(str, obj, toBuffer = false) {
	let end = 0;
	let bz = 0;
	let pos = 0;
	let arr = [];
	if(typeof obj === 'function') { // iter
		let o = null;
		while((o = obj.call(this)))
			arr.push(htmlObjGet(str, o, false));
		let buf = Buffer.concat(arr);
		if(toBuffer === true)
			return buf;
		else
			return buf.toString(); // String.prototype.call('', arr);
	}
	while(1) {
		end = str.indexOf('<!--JS_VAR_', pos);
		if(end === -1) {
			bz += str.length - pos;
			arr.push(str.slice(pos));
			break;
		} else if(pos !== end) {
			arr.push(str.slice(pos, end));
			bz += end - pos;
		}
		pos = str.indexOf('-->', end + 11);
		if(pos === -1)
			throw new Error('excepted token \'-->\'');
		let name = str.slice(end + 11, pos);
		// if(name.indexOf('<!--') !== -1) return '';
		let t = obj[name];
		if(typeof t !== 'function') {
			let s = String(t);
			arr.push(s);
			bz += s.length;
		} else {
			let s = t.call(obj);
			bz += s.length;
			arr.push(s);
		}
		pos = pos + 3;
	}
	let buf = Buffer.alloc(bz);
	pos = 0;
	for(let i = 0, j = arr.length;i !== j;i++) {
		buf.write(arr[i], pos);
		pos += arr[i].length;
	}
	if(toBuffer === true) 
		return buf;
	else
		return buf.toString();
}
// console.log('ret', htmlObjGet('<div><!--JS_VAR_a--></div><span><!--JS_VAR_b--></span><code><!--JS_VAR_c--></code>', {a: 'a', b: 'b', c: function() { return this.a + '+' + this.b;}}));
function htmlObj(str, isPath = false) {
	if(isPath === true)
		str = fs.readFileSync(str).toString();
	// JS_SPLIT
	let arr = str.split('<!--JS_MARK_');
	let ret = {};
	for(let i = 0, j = arr.length;i !== j;i++) {
		let s = arr[i];
		let pos = s.indexOf('-->');
		if(pos === -1)
			continue;
		let mark = s.slice(0, pos);
		if(mark.indexOf('<!--') === -1)
			ret[mark] = s.slice(pos + 3);
	}
	const get = function(name) { return htmlObjGet.call(this, this[name], this[name + 'Iter'] || this);};
	ret.get = ret.get || get;
	return ret;
}

function rmPath(fpath, files, callback = null) {
	if(callback === null) {
		callback = files;
		files = null;
		// let file = path.basename(fpath);
		// files = [file];
	} else {
		let c = files.length;
		let lastError = null;
		let lcb = function(err) {
			if(err)
				lastError = err;
			if(--c === 0)
				callback(lastError);
		}
		if(c === 0)
			callback(null);
		for(let i = 0, j = c;i !== j;i++)
			rmPath(fpath + path.sep + files[i], lcb);
		return;
	}
	fs.stat(fpath, function(err, stats) {
		if(err) {
			callback(err);
			return; 
		}
		if(!stats.isDirectory()) {
			fs.unlink(fpath, callback);
			return;
		}
		fs.readdir(fpath, function(err, files) {
			if(err) {
				return callback(err);
			}
			rmPath(fpath, files, function(err) {
				if(err) {
					return callback(err);
				}
				fs.rmdir(fpath, callback);
			});
		});
	});
}

function cpPath(src, dst, force = false, callback) {
	if(!callback) {
		callback = force;
		force = false;
	}
	fs.stat(src, function(err, stats) {
		if(err) {
			callback(err);
			return;
		}
		if(!stats.isDirectory()) {
			fs.copyFile(src, dst, (force)?0:fs.constants.COPYFILE_EXCL, callback);
			return;
		}
		let rcb = function(err, files) {
			if(err) { 
				callback(err);
				return;
			}
			let ncb = function(err) {
				let file = files.pop();
				if(err)
					callback(err);
				else if(file)
					cpPath(src + path.sep + file, dst + path.sep + file, force, ncb);
				else
					callback(null);
			}
			ncb(null);
		};
		fs.exists(dst, function(e) {
			if(e) {
				fs.readdir(src, rcb);
			}
			else
				fs.mkdir(dst, function(err) {
					if(err)
						callback(err);
					else
						fs.readdir(src, rcb);
				});
		});
	});
}
function cpPathNormal(src, dst, force, callback) {
	fs.stats(dst, function(err, stats) {
		if(err)
			cpPath(src, dst, force, callback);
		else if(stats.isDirectory())
			cpPath(src, dst + path.sep + path.dirname(src), force, callback);
		else 
			cpPath(src, dst, force, callback);
	});
}
function cookieParse(cookie) {
	ret = {};
	let arr = cookie.split(';');
	for(let i = 0, j = arr.length;i !== j;i++) {
		let s = arr[i].trim();
		let p = s.indexOf('=');
		if(p !== -1)
			ret[s.slice(0, p)] = decodeURI(s.slice(p));
	}
	return ret;
}
function pstat(fpath, callback) {
	fs.stat(fpath, function(err, stats) {
		if(err) {
			callback(err, null);
			return;
		}
		if(!stats.isDirectory()) {
			callback(err, {stats: stats});
			return;
		}
		let ret = {stats: stats, files: [], length: 0, filestats: []};
		let lastError = null;
		let forEachF = function(fn) {
			fs.stat(fpath + fn, function(err, stats) {
				ret.files.push(fn);
				if(err) {
					lastError = err;
					ret.filestats.push(err);
				} else
					ret.filestats.push(stats);
				if(ret.filestats.length === ret.length) {
					callback(lastError, ret);
				}
			});
		};
		fs.readdir(fpath, function(err, files) {
			if(err) {
				callback(err, null);
				return;
			}
			fpath = path.normalize(fpath + '/');
			ret.length = files.length;
			if(ret.length === 0)
				callback(null, ret);
			files.forEach(forEachF);
		});
	});
}

let pstatConvert_cache = {};
let pstatConvert_defaultF = function(err, stats) {
	stats.filename = fn;
	return stats;
};

function pstatConvert(fpath, convertF = null, callback = null) { // callbackEnd
	if(callback === null)
		callback = convertF, convertF = null;
	convertF = convertF || pstatConvert_defaultF;
	if(!pstatConvert_cache[convertF]) {
		pstatConvert_cache[convertF] = {};
	}
	fs.stat(fpath, function(err, stats){
		if(err) {
			callback(err, null);
			return;
		}
		if(!stats.isDirectory()) {
			callback(null, {stats: stats, file: convertF(path.basename(fpath), stats)});
			return;
		}
		let tmpObj = pstatConvert_cache[convertF];
		let ctime = stats.ctime;
		let t = tmpObj[fpath];
		let cblist = [];
		if(t) {
			if(ctime - t.ctime !== 0) {
				if(t.callback)
					cblist = t.callback;
			} else if(t.callback) {
				t.callback.push(callback);
				return;
			} else {
				callback(t.lastError, t);
				return;
			}
		}
		let path2 = path.normalize(fpath + '/');
		cblist.push(callback);
		let ret = {stats: stats, callback: cblist, files: [], lastError: null, ctime: ctime, ct: 0};
		tmpObj[fpath] = ret;
		let forEachF = function(fn) {
			let _path = path2 + fn;
			fs.stat(_path, function(err, stats) {
				if(err)
					ret.lastError = err;
				else
					ret.files.push(convertF(fn, stats));
				if(--ret.ct === 0) {
					let cblist = ret.callback;
					delete ret.callback;
					if(tmpObj[fpath].ctime !== ctime)
						return;
					for(let cb of cblist) {
						cb(ret.lastError, ret);
					}
					// setTimeout(() => {delete tmpObj[fpath];}, 50000);
				}
			});
		};
		// if(stats.stats.ctime === tmpObj[fpath].stats.ctime) return callback(null, tmpObj[fpath]);
		fs.readdir(fpath, function(err, files) {
			if(err) {
				callback(err, null);
				return;
			}
			ret.ct = files.length;
			if(files.length === 0) {
				delete ret.callback;
				callback(null, ret);
			}
			files.forEach(forEachF);
		});
	});
}
function formDataParse(src, callback, callbackEnd) {
	let boundary;
	let dst = null;
	let wStatus = 0;
	let s = src.headers["content-type"];
	let prevBuffer = null;
	let isPaused = false;
	const reg_1 = /[\w]+="([^"]+|\\")+"/g;
	if(s.indexOf('multipart/form-data') === -1) {
		callbackEnd(new Error('Bad Request'));
		return false;
	}
	s = '\r\n--' + s.split('boundary=')[1];
	boundary = Buffer.from(s);
	var dataF = function(data) {
		let i = 0;
		let j = 0;
		if(prevBuffer !== null) {
			if(wStatus === 1 && (j = data.indexOf('\r\n\r\n', 0)) !== -1) { 
				let prevBuf = Buffer.concat([prevBuffer, data.slice(0, j + 4)], prevBuffer.length + j + 4);
				data = data.slice(j + 4, data.length);
				prevBuffer = null;
				// wStatus = 3;
				dataF(prevBuf);
				if(dst === null) {
					prevBuffer = data;
					return;
				}
			} else
				data = Buffer.concat([prevBuffer, data], prevBuffer.length + data.length);
			prevBuffer = null;
		}
		while(1) {
			if(wStatus === 2) {
				j = data.indexOf(boundary, i);
				if(j === -1) {
					let buf = data.slice(data.length - boundary.length, data.length);
					j = buf.lastIndexOf('\r');
					if(j !== -1 && (buf = buf.slice(j, buf.length)) !== null && boundary.indexOf(buf) === 0) {
						if(dst.write(data.slice(i, data.length - boundary.length + j)) === false) {
							src.pause();
							isPaused = true;
						}
						prevBuffer = buf;
					} else if(dst.write(data.slice(i, data.length)) === false) {
						src.pause();
						isPaused = true;
					}
					if(isPaused === false && src.isPaused() === true) {
						src.resume();
					}
					break;
				}
				if(dst.write(data.slice(i, j)) === false) {
					src.pause();
					isPaused = true;
				}
				i = j + boundary.length;
				wStatus = 1;
				isPaused = false;
				dst.close(); // dst.destroy();
				dst = null;
			} else if(wStatus === 1) {
				j = data.indexOf('\r\n\r\n', i);
				if(j === -1) {
					if(data.length - i === 4 && data.indexOf('--\r\n', i) === i) {
						callback(null);
						callbackEnd(null);
					} else {
						if(i !== data.length)
							prevBuffer = data.slice(i, data.length);
						if(src.isPaused())
							src.resume();
					}
					break;
				}
				i += 2;
				let arr = data.toString('utf8', i, j).split('\r\n');
				var obj = {};
				while(arr.length) {
					let t = arr.pop().split(': ');
					let a2 = t[1].match(reg_1)
					obj[t[0].toLowerCase()] = t[1];
					if(a2 === null)
						continue;
					while(a2.length) {
						let a3 = a2.pop().split('=');
						let s2 = a3[1];
						obj[a3[0].toLowerCase()] = s2.substr(1, s2.length - 2);
					}
				}
				i = j + 4;
				wStatus = 2;
				obj.pipe = function(r) {
					if(typeof r === "function") {
						dst = {write: r, close: function(){}};
					} else if(typeof r === "object" && r.on) {
						dst = r;
						dst.on('drain', function() {
								src.resume();
								isPaused = false;
						});
					}
					if(prevBuffer !== null) {
						let prevBuf = prevBuffer;
						prevBuffer = null;
						dataF(prevBuf);
					} else if(src.isPaused()) {
						src.resume();
					}
				};
				var r = callback(obj);
				if(!r) {
					if(src.isPaused() === false)
						src.pause();
					if(i !== data.length)
						prevBuffer = data.slice(i, data.length);
					break;
				} else
					obj.pipe(r);
			} else if(wStatus === 0) {
				i = data.indexOf(boundary.slice(2, boundary.length), i);
				if(i === -1) {
					callbackEnd(new Error('Bad Request'));
					break;
				}
				wStatus = 1;
				i += boundary.length - 2;
			}
		}
	};
	src.on('data', dataF);
	// src.on('end', () => {callback(null);callbackEnd()});
	src.on('error', callbackEnd);
	return true;
}

function getMimeType(fpath) {
	// form web
	const mime_obj = {".323":"text/h323",".3gp":"video/3gpp",".aab":"application/x-authoware-bin",".aam":"application/x-authoware-map",".aas":"application/x-authoware-seg",".acx":"application/internet-property-stream",".ai":"application/postscript",".aif":"audio/x-aiff",".aifc":"audio/x-aiff",".aiff":"audio/x-aiff",".als":"audio/X-Alpha5",".amc":"application/x-mpeg",".ani":"application/octet-stream",".apk":"application/vnd.android.package-archive",".asc":"text/plain",".asd":"application/astound",".asf":"video/x-ms-asf",".asn":"application/astound",".asp":"application/x-asap",".asr":"video/x-ms-asf",".asx":"video/x-ms-asf",".au":"audio/basic",".avb":"application/octet-stream",".avi":"video/x-msvideo",".awb":"audio/amr-wb",".axs":"application/olescript",".bas":"text/plain",".bcpio":"application/x-bcpio",".bin ":"application/octet-stream",".bld":"application/bld",".bld2":"application/bld2",".bmp":"image/bmp",".bpk":"application/octet-stream",".bz2":"application/x-bzip2",".c":"text/plain",".cal":"image/x-cals",".cat":"application/vnd.ms-pkiseccat",".ccn":"application/x-cnc",".cco":"application/x-cocoa",".cdf":"application/x-cdf",".cer":"application/x-x509-ca-cert",".cgi":"magnus-internal/cgi",".chat":"application/x-chat",".class":"application/octet-stream",".clp":"application/x-msclip",".cmx":"image/x-cmx",".co":"application/x-cult3d-object",".cod":"image/cis-cod",".conf":"text/plain",".cpio":"application/x-cpio",".cpp":"text/plain",".cpt":"application/mac-compactpro",".crd":"application/x-mscardfile",".crl":"application/pkix-crl",".crt":"application/x-x509-ca-cert",".csh":"application/x-csh",".csm":"chemical/x-csml",".csml":"chemical/x-csml",".css":"text/css",".cur":"application/octet-stream",".dcm":"x-lml/x-evm",".dcr":"application/x-director",".dcx":"image/x-dcx",".der":"application/x-x509-ca-cert",".dhtml":"text/html",".dir":"application/x-director",".dll":"application/x-msdownload",".dmg":"application/octet-stream",".dms":"application/octet-stream",".doc":"application/msword",".docx":"application/vnd.openxmlformats-officedocument.wordprocessingml.document",".dot":"application/msword",".dvi":"application/x-dvi",".dwf":"drawing/x-dwf",".dwg":"application/x-autocad",".dxf":"application/x-autocad",".dxr":"application/x-director",".ebk":"application/x-expandedbook",".emb":"chemical/x-embl-dl-nucleotide",".embl":"chemical/x-embl-dl-nucleotide",".eps":"application/postscript",".epub":"application/epub+zip",".eri":"image/x-eri",".es":"audio/echospeech",".esl":"audio/echospeech",".etc":"application/x-earthtime",".etx":"text/x-setext",".evm":"x-lml/x-evm",".evy":"application/envoy",".exe":"application/octet-stream",".fh4":"image/x-freehand",".fh5":"image/x-freehand",".fhc":"image/x-freehand",".fif":"application/fractals",".flr":"x-world/x-vrml",".flv":"flv-application/octet-stream",".fm":"application/x-maker",".fpx":"image/x-fpx",".fvi":"video/isivideo",".gau":"chemical/x-gaussian-input",".gca":"application/x-gca-compressed",".gdb":"x-lml/x-gdb",".gif":"image/gif",".gps":"application/x-gps",".gtar":"application/x-gtar",".gz":"application/x-gzip",".h":"text/plain",".hdf":"application/x-hdf",".hdm":"text/x-hdml",".hdml":"text/x-hdml",".hlp":"application/winhlp",".hqx":"application/mac-binhex40",".hta":"application/hta",".htc":"text/x-component",".htm":"text/html",".html":"text/html",".hts":"text/html",".htt":"text/webviewhtml",".ice":"x-conference/x-cooltalk",".ico":"image/x-icon",".ief":"image/ief",".ifm":"image/gif",".ifs":"image/ifs",".iii":"application/x-iphone",".imy":"audio/melody",".ins":"application/x-internet-signup",".ips":"application/x-ipscript",".ipx":"application/x-ipix",".isp":"application/x-internet-signup",".it":"audio/x-mod",".itz":"audio/x-mod",".ivr":"i-world/i-vrml",".j2k":"image/j2k",".jad":"text/vnd.sun.j2me.app-descriptor",".jam":"application/x-jam",".jar":"application/java-archive",".java":"text/plain",".jfif":"image/pipeg",".jnlp":"application/x-java-jnlp-file",".jpe":"image/jpeg",".jpeg":"image/jpeg",".jpg":"image/jpeg",".jpz":"image/jpeg",".js":"application/x-javascript",".jwc":"application/jwc",".kjx":"application/x-kjx",".lak":"x-lml/x-lak",".latex":"application/x-latex",".lcc":"application/fastman",".lcl":"application/x-digitalloca",".lcr":"application/x-digitalloca",".lgh":"application/lgh",".lha":"application/octet-stream",".lml":"x-lml/x-lml",".lmlpack":"x-lml/x-lmlpack",".log":"text/plain",".lsf":"video/x-la-asf",".lsx":"video/x-la-asf",".lzh":"application/octet-stream",".m13":"application/x-msmediaview",".m14":"application/x-msmediaview",".m15":"audio/x-mod",".m3u":"audio/x-mpegurl",".m3url":"audio/x-mpegurl",".m4a":"audio/mp4a-latm",".m4b":"audio/mp4a-latm",".m4p":"audio/mp4a-latm",".m4u":"video/vnd.mpegurl",".m4v":"video/x-m4v",".ma1":"audio/ma1",".ma2":"audio/ma2",".ma3":"audio/ma3",".ma5":"audio/ma5",".man":"application/x-troff-man",".map":"magnus-internal/imagemap",".mbd":"application/mbedlet",".mct":"application/x-mascot",".mdb":"application/x-msaccess",".mdz":"audio/x-mod",".me":"application/x-troff-me",".mel":"text/x-vmel",".mht":"message/rfc822",".mhtml":"message/rfc822",".mi":"application/x-mif",".mid":"audio/mid",".midi":"audio/midi",".mif":"application/x-mif",".mil":"image/x-cals",".mio":"audio/x-mio",".mmf":"application/x-skt-lbs",".mng":"video/x-mng",".mny":"application/x-msmoney",".moc":"application/x-mocha",".mocha":"application/x-mocha",".mod":"audio/x-mod",".mof":"application/x-yumekara",".mol":"chemical/x-mdl-molfile",".mop":"chemical/x-mopac-input",".mov":"video/quicktime",".movie":"video/x-sgi-movie",".mp2":"video/mpeg",".mp3":"audio/mpeg",".mp4":"video/mp4",".mpa":"video/mpeg",".mpc":"application/vnd.mpohun.certificate",".mpe":"video/mpeg",".mpeg":"video/mpeg",".mpg":"video/mpeg",".mpg4":"video/mp4",".mpga":"audio/mpeg",".mpn":"application/vnd.mophun.application",".mpp":"application/vnd.ms-project",".mps":"application/x-mapserver",".mpv2":"video/mpeg",".mrl":"text/x-mrml",".mrm":"application/x-mrm",".ms":"application/x-troff-ms",".msg":"application/vnd.ms-outlook",".mts":"application/metastream",".mtx":"application/metastream",".mtz":"application/metastream",".mvb":"application/x-msmediaview",".mzv":"application/metastream",".nar":"application/zip",".nbmp":"image/nbmp",".nc":"application/x-netcdf",".ndb":"x-lml/x-ndb",".ndwn":"application/ndwn",".nif":"application/x-nif",".nmz":"application/x-scream",".nokia-op-logo":"image/vnd.nok-oplogo-color",".npx":"application/x-netfpx",".nsnd":"audio/nsnd",".nva":"application/x-neva1",".nws":"message/rfc822",".oda":"application/oda",".ogg":"audio/ogg",".oom":"application/x-AtlasMate-Plugin",".p10":"application/pkcs10",".p12":"application/x-pkcs12",".p7b":"application/x-pkcs7-certificates",".p7c":"application/x-pkcs7-mime",".p7m":"application/x-pkcs7-mime",".p7r":"application/x-pkcs7-certreqresp",".p7s":"application/x-pkcs7-signature",".pac":"audio/x-pac",".pae":"audio/x-epac",".pan":"application/x-pan",".pbm":"image/x-portable-bitmap",".pcx":"image/x-pcx",".pda":"image/x-pda",".pdb":"chemical/x-pdb",".pdf":"application/pdf",".pfr":"application/font-tdpfr",".pfx":"application/x-pkcs12",".pgm":"image/x-portable-graymap",".pict":"image/x-pict",".pko":"application/ynd.ms-pkipko",".pm":"application/x-perl",".pma":"application/x-perfmon",".pmc":"application/x-perfmon",".pmd":"application/x-pmd",".pml":"application/x-perfmon",".pmr":"application/x-perfmon",".pmw":"application/x-perfmon",".png":"image/png",".pnm":"image/x-portable-anymap",".pnz":"image/png",".pot,":"application/vnd.ms-powerpoint",".ppm":"image/x-portable-pixmap",".pps":"application/vnd.ms-powerpoint",".ppt":"application/vnd.ms-powerpoint",".pptx":"application/vnd.openxmlformats-officedocument.presentationml.presentation",".pqf":"application/x-cprplayer",".pqi":"application/cprplayer",".prc":"application/x-prc",".prf":"application/pics-rules",".prop":"text/plain",".proxy":"application/x-ns-proxy-autoconfig",".ps":"application/postscript",".ptlk":"application/listenup",".pub":"application/x-mspublisher",".pvx":"video/x-pv-pvx",".qcp":"audio/vnd.qcelp",".qt":"video/quicktime",".qti":"image/x-quicktime",".qtif":"image/x-quicktime",".r3t":"text/vnd.rn-realtext3d",".ra":"audio/x-pn-realaudio",".ram":"audio/x-pn-realaudio",".rar":"application/octet-stream",".ras":"image/x-cmu-raster",".rc":"text/plain",".rdf":"application/rdf+xml",".rf":"image/vnd.rn-realflash",".rgb":"image/x-rgb",".rlf":"application/x-richlink",".rm":"audio/x-pn-realaudio",".rmf":"audio/x-rmf",".rmi":"audio/mid",".rmm":"audio/x-pn-realaudio",".rmvb":"audio/x-pn-realaudio",".rnx":"application/vnd.rn-realplayer",".roff":"application/x-troff",".rp":"image/vnd.rn-realpix",".rpm":"audio/x-pn-realaudio-plugin",".rt":"text/vnd.rn-realtext",".rte":"x-lml/x-gps",".rtf":"application/rtf",".rtg":"application/metastream",".rtx":"text/richtext",".rv":"video/vnd.rn-realvideo",".rwc":"application/x-rogerwilco",".s3m":"audio/x-mod",".s3z":"audio/x-mod",".sca":"application/x-supercard",".scd":"application/x-msschedule",".sct":"text/scriptlet",".sdf":"application/e-score",".sea":"application/x-stuffit",".setpay":"application/set-payment-initiation",".setreg":"application/set-registration-initiation",".sgm":"text/x-sgml",".sgml":"text/x-sgml",".sh":"application/x-sh",".shar":"application/x-shar",".shtml":"magnus-internal/parsed-html",".shw":"application/presentations",".si6":"image/si6",".si7":"image/vnd.stiwap.sis",".si9":"image/vnd.lgtwap.sis",".sis":"application/vnd.symbian.install",".sit":"application/x-stuffit",".skd":"application/x-Koan",".skm":"application/x-Koan",".skp":"application/x-Koan",".skt":"application/x-Koan",".slc":"application/x-salsa",".smd":"audio/x-smd",".smi":"application/smil",".smil":"application/smil",".smp":"application/studiom",".smz":"audio/x-smd",".snd":"audio/basic",".spc":"application/x-pkcs7-certificates",".spl":"application/futuresplash",".spr":"application/x-sprite",".sprite":"application/x-sprite",".sdp":"application/sdp",".spt":"application/x-spt",".src":"application/x-wais-source",".sst":"application/vnd.ms-pkicertstore",".stk":"application/hyperstudio",".stl":"application/vnd.ms-pkistl",".stm":"text/html",".svg":"image/svg+xml",".sv4cpio":"application/x-sv4cpio",".sv4crc":"application/x-sv4crc",".svf":"image/vnd",".svh":"image/svh",".svr":"x-world/x-svr",".swf":"application/x-shockwave-flash",".swfl":"application/x-shockwave-flash",".t":"application/x-troff",".tad":"application/octet-stream",".talk":"text/x-speech",".tar":"application/x-tar",".taz":"application/x-tar",".tbp":"application/x-timbuktu",".tbt":"application/x-timbuktu",".tcl":"application/x-tcl",".tex":"application/x-tex",".texi":"application/x-texinfo",".texinfo":"application/x-texinfo",".tgz":"application/x-compressed",".thm":"application/vnd.eri.thm",".tif":"image/tiff",".tiff":"image/tiff",".tki":"application/x-tkined",".tkined":"application/x-tkined",".toc":"application/toc",".toy":"image/toy",".tr":"application/x-troff",".trk":"x-lml/x-gps",".trm":"application/x-msterminal",".tsi":"audio/tsplayer",".tsp":"application/dsptype",".tsv":"text/tab-separated-values",".ttf":"application/octet-stream",".ttz":"application/t-time",".txt":"text/plain",".uls":"text/iuls",".ult":"audio/x-mod",".ustar":"application/x-ustar",".uu":"application/x-uuencode",".uue":"application/x-uuencode",".vcd":"application/x-cdlink",".vcf":"text/x-vcard",".vdo":"video/vdo",".vib":"audio/vib",".viv":"video/vivo",".vivo":"video/vivo",".vmd":"application/vocaltec-media-desc",".vmf":"application/vocaltec-media-file",".vmi":"application/x-dreamcast-vms-info",".vms":"application/x-dreamcast-vms",".vox":"audio/voxware",".vqe":"audio/x-twinvq-plugin",".vqf":"audio/x-twinvq",".vql":"audio/x-twinvq",".vre":"x-world/x-vream",".vrml":"x-world/x-vrml",".vrt":"x-world/x-vrt",".vrw":"x-world/x-vream",".vts":"workbook/formulaone",".wav":"audio/x-wav",".wax":"audio/x-ms-wax",".wbmp":"image/vnd.wap.wbmp",".wcm":"application/vnd.ms-works",".wdb":"application/vnd.ms-works",".web":"application/vnd.xara",".wi":"image/wavelet",".wis":"application/x-InstallShield",".wks":"application/vnd.ms-works",".wm":"video/x-ms-wm",".wma":"audio/x-ms-wma",".wmd":"application/x-ms-wmd",".wmf":"application/x-msmetafile",".wml":"text/vnd.wap.wml",".wmlc":"application/vnd.wap.wmlc",".wmls":"text/vnd.wap.wmlscript",".wmlsc":"application/vnd.wap.wmlscriptc",".wmlscript":"text/vnd.wap.wmlscript",".wmv":"audio/x-ms-wmv",".wmx":"video/x-ms-wmx",".wmz":"application/x-ms-wmz",".wpng":"image/x-up-wpng",".wps":"application/vnd.ms-works",".wpt":"x-lml/x-gps",".wri":"application/x-mswrite",".wrl":"x-world/x-vrml",".wrz":"x-world/x-vrml",".ws":"text/vnd.wap.wmlscript",".wsc":"application/vnd.wap.wmlscriptc",".wv":"video/wavelet",".wvx":"video/x-ms-wvx",".wxl":"application/x-wxl",".x-gzip":"application/x-gzip",".xaf":"x-world/x-vrml",".xar":"application/vnd.xara",".xbm":"image/x-xbitmap",".xdm":"application/x-xdma",".xdma":"application/x-xdma",".xdw":"application/vnd.fujixerox.docuworks",".xht":"application/xhtml+xml",".xhtm":"application/xhtml+xml",".xhtml":"application/xhtml+xml",".xla":"application/vnd.ms-excel",".xlc":"application/vnd.ms-excel",".xll":"application/x-excel",".xlm":"application/vnd.ms-excel",".xls":"application/vnd.ms-excel",".xlsx":"application/vnd.openxmlformats-officedocument.spreadsheetml.sheet",".xlt":"application/vnd.ms-excel",".xlw":"application/vnd.ms-excel",".xm":"audio/x-mod",".xml":"text/plain",".xmz":"audio/x-mod",".xof":"x-world/x-vrml",".xpi":"application/x-xpinstall",".xpm":"image/x-xpixmap",".xsit":"text/xml",".xsl":"text/xml",".xul":"text/xul",".xwd":"image/x-xwindowdump",".xyz":"chemical/x-pdb",".yz1":"application/x-yz1",".z":"application/x-compress",".zac":"application/x-zaurus-zac",".zip":"application/zip",".json":"application/json"};

	return mime_obj[path.extname(fpath)]||"application/octet-stream";
}

function sendFile(request, response, fpath, stats = null, charset = '') {
	if(stats === null) {
		fs.stats(fpath, function(err, stats) {
			if(err) {
				response.writeHead(404, {"Content-Type": "text/plain"});
				response.end('404 Not Found.');
				return;
			}
		});
		return;
	}
	let mimetype_1 = getMimeType(fpath) + (charset && ('; charset=' + charset));
	let range = request.headers['range'];
	if(range) {
		let size = stats.size;
		const reg_1 = new RegExp(/\d+/g);
		let t = range.match(reg_1);
		let end;
		let start;
		if(t.length === 0) {
			response.writeHead(400, {"Content-Type": "text/plain"});
			response.end('400 Bad Request.');
			return;
		}
		start = parseInt(t[0]);
		if(t.length === 2)
			end = parseInt(t[1]);
		else if(range[range.length - 1] !== '-') {
			end = size - 1;
			start = end - start;
		}
		else
			end = size - 1;
		if(end > size || start > size || start > end) {
			// 416	Requested range not satisfiable
			response.writeHead(416, {"Content-Type": "text/plain"});
			response.end('416');
			return;
		}
		// length = size;
		/*
			if(start === 0)
				response.setHeader("Accept-Range", "bytes");
			else
			*/
		response.writeHead(206, {"Content-Type": mimetype_1, "Content-Range": 'bytes ' + start + '-' + end + '/' + size, "Content-Length": (end - start + 1)});
		fs.createReadStream(fpath, {start: start, end: end}).pipe(response);
	} else {
		let lastModified = stats.ctime.toUTCString();
		let ETag = stats.ino.toString(16) + '-' + stats.size.toString(); // stats.ctime.toJSON()
		if(request.headers['if-none-match'] === ETag || request.headers['last-modified-since'] === lastModified)
		{
			response.writeHead(304, {"Content-Length": 0, "ETag": ETag, "Last-Modified": lastModified});
			response.end();
			return;
		}
		response.writeHead(200, {"Content-Type": mimetype_1, "Content-Length": stats.size, "ETag": ETag, "Last-Modified": lastModified, "Cache-Control": "max-age=3599"});
		fs.createReadStream(fpath).pipe(response);
		/*
			let file = fs.createReadStream(fpath);
			file.on('data', function(data) {
				console.log(data.length);
				if(response.write(data) === false) {
					file.pause();
				}
			});
			response.on('drain', function(){file.resume();});
			file.on('end', function() {
				response.end();
			});
			*/
	}
}






function H(name)
{
	this.name = name || '';
	this.id = 0;
	this.setName = function(name)
	{
		this.name = name;
	};
	this.getName = function(name)
	{
		return this.name;
	};
};
H.prototype.i = 5;

module.exports = {H: H, htmlObj2: htmlObj2, htmlObj2IterF: htmlObj2IterF, rmPath: rmPath, cpPath: cpPath, cpPathNormal: cpPathNormal, pstat: pstat, pstatConvert: pstatConvert, formDataParse: formDataParse, getMimeType: getMimeType, sendFile: sendFile};
