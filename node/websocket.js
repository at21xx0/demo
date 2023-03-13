var http = require('http');
var url = require('url');
let fs = require('fs');
let querystring = require('querystring');
var ws = require('nodejs-websocket');


let server = ws.createServer(function(connection) {
	// connection.on() text(t) connect(code) close(code, reason) error(code)
	let n;
	console.log('connect', connection.path); // headers, protocols, protocol
	n = parseInt(connection.path.replace('/', ''));
	connection.on('text', function(t) {
		console.log('text', t);
		if(n === 4)
			setTimeout(() => connection.sendText(t), 50);
		else {
			let s = connection.beginBinary(); // WritableStream
			s.end(Buffer.from(t));
			connection.close();
			// connection.sendBinary(Buffer.from(t), () => connection.close());
		}
	});
	connection.on('close', function(code) {
		console.log('close', code);
	});
	connection.on('binary', function(s) {
		// let buf2 = [];
		let i = 0;
		s.on('data', function(data) {
			// buf2.push(data);
			i += data.length;
		});
		s.on('end', function() {
			// let buf = Buffer.concat(buf2);
			console.log('recvRinary:', i);
			connection.send(i.toString());
		});
	});
	connection.on('error', function(err) {
		console.log(err);
	});
	if(n !== 4) {
	}
}).listen(8077);
// server.on() listening() close() error(err) connection(connection)

let ws_html = fs.readFileSync('websocket.html');
http.createServer(function(request, response) {
	let pathname = url.parse(request.url).pathname;
	let websocket_port = 8077;
	if(pathname === '/websocket_port') {
		response.writeHead(200, {"Content-Type": "text/plain"});
		response.end(websocket_port.toString());
		return;
	}
	else if(pathname === '/websocket_port_jsonp') {
		let callback = querystring.parse(url.parse(request.url).query)['callback'] || 'callback';
		response.writeHead(200, {"Content-Type": "application/javascript;charset=utf-8"});
		response.end(`${callback}('${websocket_port.toString()}')`);
		return;
	}
	else if(pathname !== '/websocket.html') {
		response.writeHead(404, {"Connect-Type": "text/plain"});
		response.end('404 Not Found.');
		return;
	}
	response.writeHead(200, {"Content-Type": "text/html", "Content-Length": ws_html.length});
	response.end(ws_html);
}).listen(2667);
