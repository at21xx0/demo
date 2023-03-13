var NodeMediaServer = require('node-media-server');

// https://www.npmjs.com/package/node-media-server
// https://github.com/illuspas/Node-Media-Server


console.log('rtmp://127.0.0.1:1925/live/name');
console.log('http://127.0.0.1:2667/livelive/name.flv');


// http://localhost:2667/admin

const config = {
	rtmp: {
		port: 1925, 
		chunk_size: 60000,
		gop_cache: true,
		ping: 30,
		ping_timeout: 60
	},
	http: {
		port: 2667,
		allow_origin: '*'
	}
};
var nms = new NodeMediaServer(config);
nms.run();


