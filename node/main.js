var fs = require('fs');
var events = require('events');
var zlib = require('zlib');
var http = require('http');
var url = require('url');
var querystring = require('querystring'); // var querystring = require('node:querystring');
var process = require('process');
var util = require('util');
var os = require('os');
var path = require('path');
var net = require('net');
var dns = require('dns');
var domain = require('domain');
var child_process = require('child_process');
var dgram = require('dgram');
var crypto = require('crypto');
var readline = require('readline');

var lib = require('./lib.js'); // ./lib.js

H = new lib.H('name');
H.setName('h_name');
console.log(H.getName());


var eventEmitter = new events.EventEmitter();


console.log(fs.readFileSync('hello.js').toString());
fs.readFile('hello.js', function(err, data) {
	if(err)
	{
		return console.log(err);
	}
	// console.log(data.toString());
	console.log('hello_js_len: ', data.length);
});
var listener1 = function(arg1)
{
	console.log('eventName', arg1);
};
eventEmitter.addListener('newListener', function(eventName, listener)
	{
		console.log('newListener', eventName, listener);
	});
eventEmitter.addListener('removeListener', function(eventName, listener)
	{
		console.log('removeListener', eventName, listener);
	});

eventEmitter.on('eventName', listener1);
eventEmitter.addListener('eventName', function(arg1)
	{
		console.log('eventName', arg1);
	});
eventEmitter.once('eventName', function(arg1)
	{
		console.log('eventName', 'once' , arg1);
	});
eventEmitter.emit('eventName', 'arg1');
// eventEmitter.addListener('eventName', function(){}); // 仅仅能使用一次
eventEmitter.emit('eventName', eventEmitter.listenerCount('eventName'));
eventEmitter.removeListener('eventName', listener1);
eventEmitter.removeAllListeners('eventName');
eventEmitter.removeAllListeners();
// eventEmitrer.setMaxListeners(20); default 10
// listeners(event) // return listener_array

// eventEmitter.emit('error');

buf = Buffer.alloc(4 * 1024);
const buf2 = Buffer.alloc(10, 1, 'utf8'); // Buffer.alloc(size[, fill[, encoding]])
const buf3 = Buffer.allocUnsafe(10); // no_init
// Buffer.allocUnsafeSlow(size)
const buf4 = Buffer.from("test");
const buf5 = Buffer.from([0x74, 0x65, 0x73, 0x74], "utf8")
// console.log(buf4.toString('hex'));
// encoding: ascii utf8 utf16le(2 - 4 byte) ucs2(utf16le) Base64 hex latin(binary) binary
len = buf.write("[str]"); // buf.write(string[, offset[, length]][, encoding]);
console.log(buf.toString("utf8", 0, len), len); // buf.toString([encoding[, start[, end]]])
console.log(buf.type);
console.log(buf2.toJSON());
json1 = '{"code":200}';
console.log(JSON.stringify(JSON.parse(json1)));
buf6 = Buffer.concat([buf4, buf5]); // Buffer.concat(list[, totalLength])
console.log(buf4.compare(buf5));
buf.write("0123456789", 0);
console.log(buf.toString());
buf4.copy(buf, 0, 0, 5); //buf.copy(targetBuffer[, targetStart[, sourceStart[, sourceEnd]]])
console.log(buf.toString());
console.log("buf.length: ", buf.length);





/*
new Buffer(str[, encoding])
buf.length // bytes
buf.write(string[, offset[, length]][, encoding])
buf.writeUIntLE(value, offset, byteLength[, noAssert])
const buf = Buffer.allocUnsafe(6);
buf.writeUIntLE(0x1234567890ab, 0, 6);
buf.writeUIntBE(value, offset, byteLength[, noAssert])
const buf = Buffer.allocUnsafe(6);

buf.writeUIntBE(0x1234567890ab, 0, 6);

buf.writeIntLE(value, offset, byteLength[, noAssert])
buf.writeIntBE(value, offset, byteLength[, noAssert])
buf.readUIntLE(offset, byteLength[, noAssert])
buf.readUIntBE(offset, byteLength[, noAssert])
buf.readIntLE(offset, byteLength[, noAssert])
buf.readIntBE(offset, byteLength[, noAssert])
buf.toString([encoding[, start[, end]]])
buf.toJSON()
buf[index]
buf.equals(otherBuffer)
buf.compare(otherBuffer)
buf.copy(targetBuffer[, targetStart[, sourceStart[, sourceEnd]]])
buf.slice([start[, end]])
buf.readUInt8(offset[, noAssert])
buf.readUInt16LE(offset[, noAssert])
buf.readUInt16BE(offset[, noAssert])
buf.readUInt32LE(offset[, noAssert])
buf.readUInt32BE(offset[, noAssert])
buf.readInt8(offset[, noAssert])
buf.readInt16LE(offset[, noAssert])
buf.readInt16BE(offset[, noAssert])
buf.readInt32LE(offset[, noAssert])
buf.readInt32BE(offset[, noAssert])
buf.readFloatLE(offset[, noAssert])
buf.readFloatBE(offset[, noAssert])
buf.readDoubleLE(offset[, noAssert])
buf.readDoubleBE(offset[, noAssert])
buf.writeUInt8(value, offset[, noAssert])
buf.writeUInt16LE(value, offset[, noAssert])
buf.writeUInt16BE(value, offset[, noAssert])
buf.writeUInt32LE(value, offset[, noAssert])
buf.writeUInt32BE(value, offset[, noAssert])
buf.writeInt8(value, offset[, noAssert])
buf.writeInt16LE(value, offset[, noAssert])
buf.writeInt16BE(value, offset[, noAssert])
buf.writeInt32LE(value, offset[, noAssert])
buf.writeInt32BE(value, offset[, noAssert])
buf.writeFloatLE(value, offset[, noAssert])
buf.writeFloatBE(value, offset[, noAssert])
buf.writeDoubleLE(value, offset[, noAssert])
buf.writeDoubleBE(value, offset[, noAssert])
buf.fill(value[, offset][, end])
*/

// Stream 
// Readable Writable Duplex Transform R W R|W PIPE
var data1 = '';

var readerStream = fs.createReadStream('hello.js');
// readerStream.setEncoding('binary');
readerStream.on('data', function(chunk){
	data1 += chunk;
});
readerStream.on('end', function(chunk){
	console.log("s_len", data1.length);
});
var writerStream = fs.createWriteStream('a.txt');
writerStream.on('finish', function(){
	console.log('Write: done.');
	writerStream.end();
});
writerStream.on('error', function(err){
	console.log(err.stack);
});
// fs.createReadStream('hello.js').pipe(zlib.createGzip()).pipe(fs.createWriteStream('hello.js.gz'));

/* fs.createReadStream(path[, options])#
path <string> | <Buffer> | <URL>
options <string> | <Object>
flags <string> See support of file system flags. Default: 'r'.
encoding <string> Default: null
fd <integer> | <FileHandle> Default: null
mode <integer> Default: 0o666
autoClose <boolean> Default: true
emitClose <boolean> Default: true
start <integer>
end <integer> Default: Infinity
highWaterMark <integer> Default: 64 * 1024
fs <Object> | <null> Default: null
Returns: <fs.ReadStream>
*/



var u = url.parse("http://127.0.0.1:8080/api/v6/node?time=0&tk=6&ul=5"); // url.parse('/s?q=lt', true)
console.log('path_name', u.pathname, 'query', u.query, 'tk:', querystring.parse(u.query)["tk"]);
console.log(__filename, __dirname); // global.__filename
clearTimeout(setTimeout(() => true, 0));
clearInterval(setInterval(() => true, 0));
console.assert(true, 'message');
console.time('label1');
console.timeEnd('label1');
console.info("%d %s", 5, 'str'); // log error
console.dir(u);
console.trace("message");

process.on('exit', (code) => console.log('exit: %d', code)); // beforeExit
process.on('uncaughtException', (err, origin) => console.log('uncaughtException:', err, origin, err.stack));
process.on('SIGINT', () => {console.log('SIGINT');process.exit(0);}); // SIGTERM SIGKILL
// process.abort();
console.log(process.cwd());
// console.exit(0);
// process.chdir('..');
// console.log('gid: %d uid: %d', process.getgid(), process.getuid());
// process.setuid(uid); // gid
// process.kill(pid, sig);
console.log(process.memoryUsage());
// process.nextTick(callback) 下个事件循环结束，回调函数
console.log(process.umask(process.umask())); // (new) => old
console.log('uptime hrtime:', process.uptime(), process.hrtime());
console.log(process.version);

//console.log(util.format('%s %d %j %%', '[str]', 5, {code: 200}));
async function fn()
{
	// return Promise.reject(new Error('error_message'));
	return Promise.reject(null);
	// return 'ret';
}
callbackFunction = util.callbackify(fn);
callbackFunction((err, ret) => {console.log(err, ret);return err && err.hasOwnProperty('reason') && err.reason === null;});
function Current1()
{
	this.name = "xxx";
	this.log = function()
	{
		console.log("log", this.name);
	};
}
util.inherits(Current1, lib.H);
c1 = new Current1();
c1.log();
// console.log(c1.i); 5
console.log(c1.id); // undefined
console.log(util.inspect(c1, true)); //util.inspect(object,[showHidden],[depth],[colors])
// util.isArray(obj) util.isRegExp(/exp/) util.isDate(new Date)
//
// 	fs.fstat(fd, callback) 	fs.lstat(path, callback)
fs.stat("hello.js", function(err, stats)
	{
		if(err)
		{
			return console.log(err);
		}
		console.log(stats.isFile()); // isDirectory isBlockDevice isCharacterDevice isSymbolicLink isFIFO isSocket
		console.dir(stats);
	});
fs.open("hello.js", "r", function(err, fd)
	{
		if(err)
		{
			return console.log(err);
		}
		// console.log("fd:", fd);
		// fs.ftruncate(fd, 10, function(err){}); // 截取文件，callback 中 fs.read  // ftuncateSync(fd, len)
		fs.read(fd, buf, 0, buf.length, null, function(err, bytes, buf)
			{
				// console.log("read: ", buf.slice(0, bytes).toString());
				fs.close(fd, function(err)
					{
						if(err)
						{
							console.log(err);
						}
					});
			});
	});
// fs.open(path, flags[, mode], callback); // mode: 0666 flags: r r+ rs(r + sync) rs+ w w+ wx(not_exist) wx+ a a+ ax ax+

// fs.read(fd, buffer, offset, length, position, callback)
// fs.writeFile(file, data[, options], callback) //options: {encoding:"utf8", mode:0666, flag:"w"}
// fs.writeFile(fd, data[, options], callback)
//
// remove file
fs.unlink("a.txt", function(err)
	{
		if(err)
		{
			console.log(err);
		}
	});
// fs.mkdir(path[, options], callback) // options:{recursive:false, mode:0777} recursive 是否递归
fs.mkdir("tmp", function(err){
	if(err)
		console.log(err);
	fs.rmdir("tmp", function(err){
		if(err)
			console.log(err);
	});
});
fs.readdir(__dirname, function(err, files){
	if(err)
	{
		return console.log(err);
	}
	files.forEach(function(file){
		console.log(file);
	});
});
// 	fs.rename(oldPath, newPath, callback)
//:
// fs.chown(path, uid, gid, callback)
// fs.chmod(path, mode, callback)
// fs.link(srcpath, dstpath, callback)
// fs.symlink(srcpath, dstpath[, type], callback)
// fs.fsync(fd, callback)
// fs.fsyncSync(fd)
// fs.write(fd, buffer, offset, length[, position], callback)
// fs.write(fd, data[, position[, encoding]], callback)
// fs.appendFile(filename, data[, options], callback)
// fs.exists(path, callback)
fs.exists(__dirname, function(e)
	{
		console.log(__dirname + " exist: ", e);
	});


/*
http.createServer(function(request, response){
	var u = url.parse(request.url, true);
	var postData = '';
	// console.log('path_name', u.pathname);
	// console.log(request.headers);
	// console.log(request.url);
	// console.log(request.method);
	// let range = req.headers["range"];
	if(request.method === "POST")
	{
		//request.pipe(response);
		request.on('data', function(chunk)
			{
				postData += chunk;
			});
		request.on('end', function()
			{
				response.writeHead(200, {"Content-Type": "text/plain"});
				response.end(postData);
			});
		return;
	}
	response.writeHead(200, {"Content-Type": "text/plain"});
	response.write(JSON.stringify({headers: request.headers, url: request.url, method: request.method}));
	response.write('\n');
	response.end(util.inspect(u));

}).listen(2667);
console.log('server: http://127.0.0.1:2667/');
*/
console.log(os.networkInterfaces());


// os.tmpdir() 
// os.endianness() // 大小端
// os.hostname()
// os.type() 
// os.platform()
// os.arch()
// os.release()
// os.uptime()
// os.loadavg() 1 分钟 10 分钟 15 分钟平均负载
// os.totalmem()
// os.freemem()
// os.cpus()

console.log(path.normalize('./../'));
var path2 = path.join(__dirname, "file.txt"); // path.join([path1][, path2][, ...]) // concat_path
var path3 = path.resolve(__dirname, "tmp"); // absoulte_path//path.resolve([from ...], to)
console.assert(path.isAbsolute(path3), "err");
var rel_path1 = path.relative(__dirname, path3); // path.relative(from, to)

console.assert(path3 === path.normalize(path.join(__dirname, rel_path1)), "err1");
console.assert(path.dirname(path3) === "tmp", "err2");
console.assert(path.basename(path2, ".txt") === "file", "err3"); // path.basename(p[, ext])
console.assert(path.extname(path2) === ".txt", "err4");
// path.format(path.parse(path3));
console.log(path.sep, path.delimiter);



// n = 1;
var server = net.createServer(function(connect){ // {localAddress: '0.0.0.0'}
	// console.log("n: ", i++);
	connect.on("end", function() {
		console.log("server_close");
	});
	console.log("client: ", connect.remoteFamily, connect.remoteAddress, connect.remotePort);
	connect.pipe(connect);
});
server.listen(8084, () => void(0));
client = net.connect({port: 8084}, function() {
	console.log("client_connect");
}); // {host: localhost, port: 8084}
client.on("end", () => console.log("client_close"));
client.on("data", function(data) {
	console.assert(data.toString() === "test_data", "sock_assert_1");
	client.end();
});
client.write("test_data");

// net.createServer([options][, connectionListener])
// net.connect(options[, connectionListener]) // options: {port: 8080, host: localhost, family: 4, localAddress: local_address, localPort: local_port, path: local_socket_path}
// net.createConnection(options[, connectionListener])
// net.connect(port[, host][, connectListener])
// net.connect(path[, connectListener]) // socket_path
// net.createConnection(port[, host][, connectListener])
var ip_1 = '127.0.0.1';
console.assert(net.isIP(ip_1) == 4, "net_err1");
console.assert(net.isIPv4(ip_1), "net_err2");
console.assert(!net.isIPv6(ip_1), "net_err3");

// server.listen(port[, host][, backlog][, callback]) // port 0 随机端口
// server.listen(path[, callback]) server.listen(handle[, callback])
// server.listen(options[, callback]) // options_attr: port host backlog
// server.close([callback])
// server.address()
// server.unref() 作为唯一服务器，允许退出
// server.ref()
// server.getConnections(callback) // (err, count) => console.log(count)
// server_event : listening connection close error

// net.Socket event: lookup(解析域名后，连接前) connect data end timeout drain(写缓存为空) error close
// socket.bufferSize
// socket.remoteAddress 
// socket.remoteFamily socket.remoteAddress socket.remotePort
// socket.localAddress socker.localPort
// socket.bytesRead socket.byteWritten
//
// net.Socket([options])
// socket.connect(port[, host][, connectListener])
// socket.connect(path[, connectListener])
// socket.setEncoding([encoding])
// socket.write(data[, encoding][, callback])
// socket.end([data][, encoding])
// socket.destroy() // socket.on('error', callback);
// socket.pause() // no_data_event  disable_upload      socket.resume() 
// socket.setTimeout(timeout[, callback])
// socket.setNoDelay([noDelay])
// socket.setKeepAlive([enable][, initialDelay])
// socket.address()
// socket.unref() socket.ref()


dns.lookup('runoob.com', function(err, address, family) {
	if(err)
	{
		return console.log(err);
	}
	console.log('address: ', address, family);
});

// dns.lookup(hostname[, options], callback) // IPv4 or IPv6
// dns.lookupService(address, port, callback) // getnameinfo 
// dns.resolve(hostname[, rrtype], callback)
/*
dns.resolve4(hostname, callback) // ipv4 // rrtype: 'A'
dns.resolve6(hostname, callback) // ipv6 // rrtype: 'AAAA'
dns.resolveMx(hostname, callback) // 'MX' 
dns.resolveTxt(hostname, callback) // 'TXT'
dns.resolveSrv(hostname, callback) // 'SRV'
dns.resolveSoa(hostname, callback) // 'SOA'
dns.resolveNs(hostname, callback) // 'NS'
dns.resolveCname(hostname, callback) // 别名 // 'CNAME'
dns.reverse(ip, callback) // 反向 // 'PTR'
*/
// dns.setServers(servers) // dns_ip
// dns.getServers()
// https://www.runoob.com/nodejs/nodejs-dns-module.html

//domain // 异步 emitter 处理
var domain1 = domain.create();
domain1.on('error', function(err){
	console.log('domain_err:', err);
});
domain1.add(eventEmitter);

eventEmitter.on('error', function(err){
	console.log('emitter_err:', err);
});
eventEmitter.emit('error', new Error('new_Error_1'));
eventEmitter.removeAllListeners();
eventEmitter.emit('error', new Error('new_Error_2'));
// domain1.remove(eventEmitter);

// domain.run(function) // 绑定函数内所有Emitter
// domain,add(emitter)
// domain.remove(emitter)
// domain.bind(callback) // 包装函数 // fs.readFile('fn', domain.bind((err, data) => origincallback(err, data)));
// domain.intercept(callback) // domain.intercept((data) => origincallback(null, data));
// domain.enter(); // 进入异步调用上下文
// domain.exit() // 退出上下文
// domain.dispose() // 释放对象
// domain.create() //
// domain.nembers // 

var _server_root = path.resolve('.');

function v7_file(req, res)
{
}
function f_hello(req, res)
{
	response.writeHead(200, {"Content-Type": "text/plain"});
	response.end('hello, world!\n');
}
function v7_request_info(request, response)
{
	let u = url.parse(request.url);
	response.writeHead(200, {"Content-Type": "text/plain"});
	response.write(JSON.stringify({headers: request.headers, url: request.url, method: request.method}));
	response.write('\n');
	response.end(util.inspect(u));
}
function v7_jsonp(req, res) {
	let callback = url.parse(req.url, true).query['callback'] || 'callback';
	let data = {code: 200};
	res.writeHead(200, {"Content-Type": "application/javascript;charset=utf-8"});
	res.end(`${callback}(${JSON.stringify(data)})`);
}
function v7_upload(request, response)
{
	if(request.method !== "POST") {
		response.writeHead(405, {"Content-Type": "text/plain"});
		response.end('405 Method Not Allowed.');
		return;
	}
	// request.pipe(fs.createWriteStream("w.txt"));
	// response.writeHead(200, {"Content-Type": "text/plain"});
	// response.end('OK');
	var prevName = null;
	var pObj = {};
	var s = '';
	var i = 1;
	lib.formDataParse(request, function(obj) {
		if(prevName !== null) {
			pObj[prevName] = s;
			s = '';
			prevName = null;
		}
		if(obj === null)
			return;
		console.log('obj:', obj.name, obj.filename);
		if(obj.filename) {
			let basepath1 = path.normalize(_server_root + '/upload/' + obj.filename);
			let dir1 = path.dirname(basepath1);
			//return fs.createWriteStream(path.normalize(_server_root + '/upload/' + obj.filename));
			fs.exists(dir1, function(e) {
				if(e) {
					obj.pipe(fs.createWriteStream(basepath1));
				} else {
					fs.mkdir(dir1, {recursive: true}, function(err){
						if(err) {
							console.log(err);
							obj.pipe((data) => 0);
						} else
							obj.pipe(fs.createWriteStream(basepath1));
					});
				}
			});
			return false;
		}
		prevName = obj.name;
		return (data) => s += data.toString();
	}, () => {
		console.log(pObj);
		response.writeHead(200, {"Content-Type": "text/plain"});
		response.end('OK');
	});
}
function _server_index(request, response)
{
	response.writeHead(200, {"Content-Type": "text/plain"});
	response.end('hello, world!\n');
}
var l_map = {'/api/v7/file': v7_file, '/api/v7/requestinfo': v7_request_info, '/api/v7/upload': v7_upload, '/api/v7/jsonp': v7_jsonp, '/hello': f_hello};

http.createServer(function(request, response){
	var pathname = url.parse(request.url).pathname;
	var f = l_map[pathname];
	if(f)
		return f(request, response);
	var fpath = path.normalize(_server_root + pathname); // path.join([path1][, path2][, ...]) // concat_path
	console.log("fpath: ", fpath);
	if(fpath.length < _server_root.length)
	{
		response.writeHead(403, {"Content-Type": "text/plain"});
		response.end('403 Forbidden.');
	}
	if(pathname[pathname.length - 1] === '/')
	{
		return _server_index(request, response);
	}
	fs.stat(fpath, function(err, stats) {
		let mimetype_1 = lib.getMimeType(pathname);
		let range_s = request.headers['range'];
		if(err)
		{
			response.writeHead(404, {"Content-Type": "text/plain"});
			response.end('404 Not Found.');
			return;
		}
		if(!stats.isFile())
		{
			response.writeHead(400, {"Content-Type": "text/plain"});
			response.end('400 Bad Request.');
			return;
		}
		else if(range_s)
		{
			let size = stats.size;
			const reg_1 = new RegExp(/\d+/g);
			let t = range_s.match(reg_1);
			let end;
			let start;
			if(t.length === 0)
			{
				response.writeHead(400, {"Content-Type": "text/plain"});
				response.end('400 Bad Request.');
				return;
			}
			start = parseInt(t[0]);
			if(t.length === 2)
			{
				end = parseInt(t[1]);
			}
			else if(range_s[range_s.length - 1] !== '-')
			{
				end = size - 1;
				start = end - start;
			}
			else
			{
				end = size - 1;
			}
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
				// response.setHeader("Content-Range", 'bytes ' + start + '-' + end + '/' + size);
			// console.log("info: ", range_s, start, end, size, end + 1 - start, mimetype_1);
			response.writeHead(206, {"Content-Type": mimetype_1, "Content-Range": 'bytes ' + start + '-' + end + '/' + size, "Content-Length": (end - start + 1)});
			fs.createReadStream(fpath, {start: start, end: end}).pipe(response);
		} else {
			let lastModified = stats.ctime.toUTCString();
			let ETag = stats.ino.toString(16) + '-' + stats.size.toString();
			if(request.headers['if-none-match'] === ETag || request.headers['last-modified-since'] === lastModified)
			{
				response.writeHead(304, {"Content-Length": 0});
				response.end();
				return;
			}
			response.writeHead(200, {"Content-Type": mimetype_1, "Content-Length": stats.size, "ETag": ETag, "Last-MOdified": lastModified, "Cache-Control": "max-age=3600"});
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
	});
	return;
}).listen(2667);
console.log('server: http://127.0.0.1:2667/');

request1 = http.request({host: '127.0.0.1', port: 2667, path: '/index.html'}, function(response){
	var bf = [];
	response.on('data', (data) => bf.push(data));
	response.on('end', function(){
		var buf = Buffer.concat(bf);
		console.log('data', buf.toString('utf8'));
	});
});
// http.request(options, callback); // options: host hostname port localAddress socketPath path headers auth
request1.end();

(function(skip){
	if(skip === true)
		return;
	// child_process.exec(command[, options], callback); // options: {cwd: '.', env:{PATH_:'path', encoding: 'utf8', shell: '/bin/sh', timeout: 0, maxBuffer: 200 * 1024, killSign: 'SIGTERM'} uid/gid
	// child_process.spawn(command[, args][, options]);
	// child_process.fork(modulePath[, args][, options]); // child_precess.on(close, (code) => console.log(code));
	var childProcess = child_process.exec('node javascript.js', function(err, stdout, stderr) {
		if(err)
		{
			console.log(err.stack);
			console.log('err:', err.code, err.signal);
			return;
		}
		console.log('stdout:', stdout);
	});
	childProcess.on('exit', function(code) {
		console.log('exit_code:', code);
	});
})(true);



(function(skip) {
	if(skip === true)
		return;

	let readStream = fs.createReadStream('./test.c', {
		highWaterMark: 100
	});
	// readStream.pause() readStream.resume() readStream.isPause()
	// readable.setEncoding(encoding); // 'utf8'


	/*
readStream.on('readable', () => {
	// console.log('readable');
	// readStream.read();
});
readStream.on('data', (data) => {
	let i = data.length;
	let e = (i < 10)?i:10; // full
	// console.log(i, data.slice(0, e).toString().replace('\n', '\\n'));
});
*/

	let count = 1000;

	let newReadStream = new stream.Readable({
		highWaterMark: 256,
		read: function(size) {
			let chunk = null;
			setTimeout(() => {
				if(count > 0) {
					let chunkLength = Math.min(count, size);
					chunk = Buffer.from('0'.repeat(chunkLength));
					count -= chunkLength;
				}
				this.push(chunk); // push(Buffer) push(string)
			}, 500);
			// console.log(this.readableFlowing);
		}, 
		destroy: function() {
			// console.log('destroy');
		}
	});

	/*
newReadStream.on('readable', () => {
	// const chunk = newReadStream.read();
	// console.log(chunk.toString());
	t = newReadStream.read();
	console.log('readable', t);
});
*/
	newReadStream.on('data', (data) => {
		let i = Math.min(16, data.length);
		console.log('data', data.length, data.slice(0, i).toString());
	});

	let buf = [];
	let newWriteStream = new stream.Writable({
		highWaterMark: 64, 
		write: function(chunk, encoding, callback) {
			setTimeout(() => {
				buf.push(chunk);
				callback();
			}, 50);
		},
		destroy: function () {
			let bf = Buffer.concat(buf);
			console.log('bf', bf.toString());
		}
	});

	newWriteStream.on('end', () => console.log('newWriteStream_end'));

	newWriteStream.write('0'.repeat(40));
	newWriteStream.write('1'.repeat(40));
	newWriteStream.write('2'.repeat(40));
	newWriteStream.end();


	// https://nodejs.org/dist/latest-v18.x/docs/api/stream.html#new-streamduplexoptions

	let upperStream = new stream.Transform({
		buffer0: null,
		highWaterMark: 64,
		transform(chunk, encoding, callback) {
			this.push(chunk.toString().toUpperCase());
			callback();
		},
		flush(callback) { // end
			// this.push('END');
			callback();
		}
	});
	let upper_1 = fs.createReadStream('hello.js').pipe(upperStream);
	upper_1.on('data', function(data) {
		console.log('upper: ', data.toString());
	});
})(true);


(function(skip) {
	if(skip === true)
		return;
	var rl = readline.createInterface({
		input: process.stdin,
		output: process.stdout,
		completer: function(line) {
			var completions = '.help .error .exit .quit .q'.split(' ');
			var hits = completions.filter(function(c) {return c.indexOf(line) === 0;});
			return [hits.length ? hits: completions, line];
		},
		terminal: true
	});
	/*
function completer(linePartial, callback) {
	callback(null, [['123'], linePartial]);
}
*/

	rl.setPrompt('>');
	rl.question('hello?', function(answer) {
		console.log('feedback:', answer);
		rl.prompt();

	});

	rl.on('line', function(line) {
		console.log(line);
		rl.close();
	});
	rl.on('SIGINT', function() {
		console.log('^C');
		process.exit();
	});
})(true);

(function(skip) {
	if(skip === true)
		return;
	// child_process.exec(command[, options], callback); // options: {cwd: '.', env:{PATH_:'path', encoding: 'utf8', shell: '/bin/sh', timeout: 0, maxBuffer: 200 * 1024, killSign: 'SIGTERM'} uid/gid
	// child_process.spawn(command[, args][, options]);
	// child_process.fork(modulePath[, args][, options]); // child_precess.on(close, (code) => console.log(code));
	var childProcess = child_process.exec('node -v', function(err, stdout, stderr) {
		if(err)
		{
			console.log(err.stack);
			console.log('err:', err.code, err.signal);
			return;
		}
		console.log('version:', stdout);
	});
	childProcess.on('exit', function(code) {
		console.log('exit_code:', code);
	});
	let child = child_process.spawn('node', ['-v'], {
		cwd: __dirname,
		env: process.env,
		argv0: 'node',
		// detached: false, uid: uid, gid: gid,
		serialization: 'json',
		shell: true, // '/bin/sh'
		windowHide: false,
		killSignal: 'SIGTERM',
		timeout: 0,
		stdio: [ // in out err
			0, // inherit pipe // parent
			fs.openSync('a.txt', 'w'),
			'pipe'
		] // pipe ipc overlapped ignore inherit Stream null
	});
	// child.stdout.on data(data) close(code)
	// child.stdin.write .end
	// child.on error(err) exit(code, signal) message(nessage, sendHandle) spawn
	child.on('close', function(code) { console.log(child.pid, code); });
	// child.kill('SIGINT'); // SIGTERM
	// child_process.fork(modulePath[, args][, options])
	let cp = child_process.fork(__dirname + path.sep + 'test_fork.js');
	cp.on('message', function(msg) {
		console.assert(msg.code === 200, 'message');
	});
	cp.send({code: 200});
})(true);
(function(skip) {
	if(skip === true)
		return;
	// console.log(crypto.getCiphers());
	// console.log(crypto.getHashes());
	let hello_sha1 = crypto.createHash('sha1'); // md5
	let hello_file = fs.createReadStream('hello.js');
	hello_file.pipe(hello_sha1); // hello_file.on('data', function(data) { hello_sha1.update(data);});
	hello_file.on('end', function() {
		// console.log('hello_sha1: ', hello_sha1.digest('hex'));
		console.assert(hello_sha1.digest('hex') === '5d48aaa91203229a19af1fb0c3ce2326eca56c3a', 'hello_sha1');
	});
	let md5 = crypto.createHash('md5');
	md5.update('password' + '_salt');
	// hash.update(data[, input_encoding])
	// hash.digest([encoding]) // hex binary base64
	console.assert(md5.digest('hex') === '685af19f02e9efbf8e8c7253a8ce7d72', 'md5');
	/*
	let hmac = crypto.createHmac('sha256', 'a secret');
	hmac.update('[str]');
	console.log(hmac.digest('hex'));
	*/
	let _key = '_prefix__password__suffix_';
	let _data = '[str]';
	const iv = Buffer.alloc(16);

	crypto.randomFillSync(iv); // buffer, offset=0, size=buffer.length-offset

	let dec = function(data_encrypted) {
		const key = crypto.scryptSync(_key, 'salt', 32);
		//let aes_decipher = crypto.createDecipheriv('aes-256-ecb', key, null);
		let aes_decipher = crypto.createDecipheriv('aes-256-cbc', key, iv);
		let d = Buffer.concat([aes_decipher.update(data_encrypted), aes_decipher.final()]);
		console.assert(d.toString('utf8') === _data, 'aes256');
	}

	// crypto.randomFill(new Uint8Array(16), (err, iv) => { });
	crypto.scrypt(_key, 'salt', 32, (err, key) => {
		if(err) throw err;
		if(err) throw err;
		let encrypted = '';
		let aes_cipher = crypto.createCipheriv('aes-256-cbc', key, iv);
		aes_cipher.setEncoding('binary');
		aes_cipher.on('data', (chunk) => encrypted += chunk);
		aes_cipher.on('end', () => {
			dec(Buffer.from(encrypted, 'binary'));
			/*
			console.log(JSON.stringify({
				algorithm: 'aes-256-cbc',
				iv: iv.toString('hex'),
				key: key.toString('hex'),
				data_encrypted: Buffer.from(encrypted).toString('hex')
			}));
			*/
		});
		aes_cipher.write(_data);
		aes_cipher.end();
	});
	
})(true);
(function(skip) {
	if(skip === true) 
		return;
	let str = '[str]';
	var s = dgram.createSocket('udp4'); // udp4 udp6
	s.bind(8088, function() {
		// socket.addMembership(multicastAddress[, multicastInterface])
		// socket.dropMembership(multicastAddress[, multicastInterface])
	});
	// socket.bind(port[, address][, callback])
	s.on('message', function(msg, rinfo) {
		// console.log('udp_recv: %s %d %s:%d', msg.toString(), msg.length, rinfo.address, rinfo.port);
		console.assert(msg.toString() === str, 'udp');
		s.close();
	});
	var client = dgram.createSocket('udp4');
	// socket.send(buf, offset, length, port, address[, callback])
	client.send(Buffer.from(str), 0, str.length, 8088, '127.0.0.1', function(err) {
		client.close();
	});
	// socket.setTTL(ttl) // 64 // 1 - 255 // socket.setMulticastTTL(ttl) // socket.setMulticastLoopback(flag)
	// socket.unref() socket.ref()
})(false);


