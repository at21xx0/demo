var path = require('path');
var fs = require('fs');
var http = require('http');
var https = require('https');
var util = require('util');
var express = require('express');
var bodyParser = require('body-parser');
var cookieParser = require('cookie-parser');
var multer = require('multer');
var app = express();

var urlencodeParser = bodyParser.urlencoded({extended: false}); // applition/x-www-form-urlencoded
 
app.get('/', function (req, res) {
   res.send('Hello World');
})

app.get('/get', function (req, res) {
	console.assert(req.app === app && req.app === res.app, 'app');
	// res.redirect('upload.html'); // 302 // '/api/v7/upload' 'http://xxx.com/' '../xx' // res.redirect(301, '../');
	// res.set('Age', 12); // {'Age': 12} 
	// res.cookie(name，value [，option]) // opition: domain string / expires Date new Date(Date.now() + 40000) / httpOnly Boolean / maxAge String Number_sm / path String '/' / secure Boolean https / signed Boolean
	// res.clearCookie(name [, options]); // res.cookie('name', {'path': '/'});
	//
	// res.download(path.normalize(__dirname + '/' + 'upload.html'), save.html) // res.download(path[, filename][, fn]);
	// res.end([data], [, encoding]);
	// res.get('Content-Type')
	// res.sendFile(path [，options] [，fn]) // { root:__dirname + '/public', dotfile:'deny', headers:{ 'x-timestamp':Date.now(), 'x-sent':true }
	// res.status(200);
	// res.send('ok'); // Buffer string json 
	// res.SendStatus(404); res.status(404).send('Not Found');
	// res.type('text/plain'); // html .html json application/json png
	// res.append('Set-cookie', 'token=let-cin;path=/;HttpOnly'); // res.append('Lind', ['<http://localost>', '<https:localhost:3000>']); 
	// res.attchment('logo.png'); // Content-Disposition: attachment; filename="logo.png"

	res.json({
		// app: req.app, express()
		baseUrl: req.baseUrl, // parentapp.use(baseUrl, app)
		// body: req.body,
		fresh: req.fresh, 
		stale: req.stale,
		hostname: req.hostname,
		ip: req.ip,
		OriginalUrl: req.originalUrl,
		params: req.params,
		path: req.path, // '/get'
		protocol: req.protocol, // http
		query: req.query, // get?xx=xx // {xx: xx}
		route: req.route,
		subdomains: req.subdomains,
		acceptsCharsets: req.acceptsCharsets('utf8'),
		acceptsEncodings: req.acceptsEncodings('gzip'),
		acceptsLanguages:req.acceptsLanguages('en'),
		req_get_host: req.get('Host'),
		req_accepts_json: req.accepts('json'), // html text/html ['json', 'html'] 'application/json'
		req_is_json: req.is('json') // json application/json application/*
	});
	// req,params('id')
	// req.accepts()
});
app.post('/post', urlencodeParser, function(req, res) { // form
	res.json(req.body);
});


// enctype multipart/form-data
// https://github.com/expressjs/multer/blob/master/doc/README-zh-cn.md
app.post('/api/v6/upload', multer({dest: 'upload/'}).any(), function(req, res) {
	// .single(fieldname) // req.file
	// .array(fieldname[, maxCount]);
	// .fields(fields) // fields = [{name: 'file', maxCount: 10}, {name: 'img', maxCount: 2}]
	// .none()
	// .any()


	console.log(req.files);
	res.send('ok');
	// fieldname originalname encoding mimetype destination filename path size
/*[{ // upload_html /api/v7/upload
    fieldname: 'file', // form.append("file", file);
    originalname: 'hello.js',
    encoding: '7bit',
    mimetype: 'text/javascript', // random
    destination: 'upload/',
    filename: 'a530685d2b2f1a80ab0eddb65812dee7',
    path: 'upload/a530685d2b2f1a80ab0eddb65812dee7',
    size: 221 // length
    // buffer
}]*/
});
// const storage_1 = multer.memoryStorage();
const storage_1 = multer.diskStorage({
	destination: function(req, file, cb) {
		cb(null, path.normalize(__dirname + '/' + 'upload/'));
	}, 
	filename: function(req, file, cb) {
		let dir1 = path.dirname(__dirname + path.sep + 'upload' + path.sep + file.originalname);
		/*
		let mkdircallback = function(err) {
			if(err)
				cb(err);
			else
				cb(null, file.originalname);
		}
		let existscallback = function(e) {
			if(e)
				cb(null, file.originalname);
			else
				fs.mkdir(dir1, {recursive: true}, mkdircallback);
		}
		fs.mkdir(dir1, {recursive: true}, existscallback);
		console.log('info: ', dir1, file.originalname);
		*/
		new Promise(function(resolve, reject) {
			fs.exists(dir1, (e) => resolve(e));
		}).then((e) => new Promise(function(resolve, reject) {
				if(e)
					resolve(null);
				else 
					fs.mkdir(dir1, {recursive: true}, (err) => resolve(err));
		})).then(function(err){
			if(err)
				cb(err);
			else
				cb(null, file.originalname);
		});
	}
});
function fileFilter_1(req, file, cb) {
	// console.log(req.body);
	cb(null, true);
	return;
	cb(null, false); // reject
	cb(new Error('error'));
}
app.post('/api/v7/upload', multer({storage: storage_1, fileFilter: fileFilter_1, preservePath: true}).any(), function(req, res) {
	res.send('ok');
});
app.post('/api/v6/img', function(req, res, next) {
	upl = multer({dest: 'img/'}).single('img');
	upl(req, res, function(err = undefined) {
		if(err instanceof multer.MulterError) {
			console.log(err);
			next();
		}
		else
			next(err);
	});
}, function(req, res) {
	res.send('ok');
});
/*
dest: 'upload'
limits:
	Description	Default
	fieldNameSize	Max field name size	100 bytes
	fieldSize	Max field value size (in bytes)	1MB
	fields	Max number of non-file fields	Infinity
	fileSize	For multipart forms, the max file size (in bytes)	Infinity
	files	For multipart forms, the max number of file fields	Infinity
	parts	For multipart forms, the max number of parts (fields + files)	Infinity
	headerPairs	For multipart forms, the max number of header key=>value pairs to parse	2000
*/
/*
app.get('/*.html', function(req, res) {
	res.sendFile(path.normalize(__dirname + req.path));
});
*/
// app.use(multer({dest: 'upload/'}).array('any'));



let cookie_parser = cookieParser();
app.get('/cookie', cookie_parser, function(req, res) {
	res.send(util.inspect(req.cookies));
});
app.use('/static', express.static(__dirname));

/*
express.static(root_path, {
	dotfiles: 'ignore', // allow deny ignore
	etag: true,
	extensions: true, // ['html', 'htm']
	index: "index.html",
	lastModefied: true,
	maxAge: 0, // http_header[Age]
	redirect: true, // root_path/dir1 -> root_path/dir1/
	setHeaders: function(res, path, stat) {
		res.set('x-timestamp', Date.now());
		// stat = fs.statSync
	}
});
*/

app.locals.title = 'app';
// app.locals.email
var subapp = express();

subapp.get('/app', function(req, res) {
	res.json({
		mountpath: subapp.mountpath, // /subapp
		path: req.path, // /app
		baseUrl: req.baseUrl, // /subapp
		originalUrl: req.originalUrl // /subapp/app
	});
});

subapp.on('mount', function(parent) {
	console.assert(parent === app, 'mount_subapp');
});

app.use('/subapp', subapp);

console.log('subapp_path', subapp.path());

var router = express.Router({caseSenstive: true, mergeParams: false, strict: true});

router.param('id', function(req, res, next, id) {
	console.log('router_id', id);
	next()
});

router.use(function(req, res, next) {
	console.log('router', req.originalUrl);
	next();
});
router.get('/router/user/:id', function(req, res) {
	res.json(req.params);
});
// router.route
// router.use
app.use(router);

app.route('/route_')
	.all(function(req, res, next) {
		console.log('middleware', req.originalUrl);
		next();
	})
	.get(function(req, res, next) {
		res.send('get');
	})
	.post(function(req, res, next) {
		res.send('post');
	});




app.all('/404', function(req, res) {
	// app.all('*', callback[, callback])
	res.sendStatus(404);
	// console.log('log', req.originalUrl);
});

// app.METHOD('*', callback[, callback])
// METHOD : checkout connect copy delete get head lock merge mkactivity mkcol move m-search notify options patch post propfind proppatch purege put report search subscribe trace unlock unsubscribe

let log_middleware = function(req, res, next) {
	console.log('log', req.originalUrl);
	next();
}

app.get('/middleware', log_middleware, function(req, res) {
	res.send('ok');
});
// app.use(log_middleware);


app.param('id', function(req, res, next, id) {
	console.log('id', id);
	next();
});
app.get('/user/:id', function(req, res) {
	res.send(JSON.stringify(req.params));
});
// app.param(['id', 'page'], callback);
app.param('page', function(req, res, next, page) { 
	console.log('page', page);
	next();
});
app.get('/user/:id/:page', function(req, res) {
	res.send(JSON.stringify(req.params));
});


// app settings table
app.disable('trust proxy');
// app.get('trust proxy'); // false
// app.enable('trust proxy');
// app.set('trust proxy', true);
// Application Settings // https://expressjs.com/zh-cn/4x/api.html



// app.engine('jade', require('jade').__express); // /xxx.jade
// app.engine('html', require('ejs'_).renderFile);
// ./render.js







// app.listen(port, [hostname], [backlog], [callback])  // http.Server.listen()
var server = app.listen(2667, function () {
 
  var host = server.address().address;
  var port = server.address().port;
 
  console.log("addr: http://%s:%s", host, port);
 
})

http.createServer(app).listen(8080);

let options = {
	key: fs.readFileSync('../cert/rsa_private.key'), 
	cert: fs.readFileSync('../cert/cert.pem'),
	ca: fs.readFileSync('../cert/ca.pem')
};

https.createServer(options, app).listen(8043);



