var http = require("http")
http.createServer(function(request, response) {
	response.writeHead(200, {'Content-Type': 'text/plain'});
	response.end('Hello, world!\n')
}).listen(2667)

console.log('http://127.0.0.1:2667/')
