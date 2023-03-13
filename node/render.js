var fs = require('fs');
var path = require('path');
const handlebars = require('handlebars');
const ejs = require('ejs');
var url = require('url');
var express = require('express');
var http = require('http');

let lib = require('./lib.js');



let files = (function() {
	let arr = fs.readdirSync(__dirname);
	let ret = [];
	for(let i = 0, j = arr.length;i !== j;i++) {
		let stats = fs.statSync(__dirname + path.sep + arr[i]);
		ret.push({fn: arr[i], isDir: stats.isDirectory(), size: stats.size, ctime: stats.ctime.toJSON()});
	}
	return ret;
})();

const template1 = handlebars.compile('Name: {{name}}');
console.log(template1({name: 'aa'}));

const template2 = handlebars.compile(fs.readFileSync('./views/index.hbs').toString());
console.log(template2({title: 'index', files: files, path: __dirname, menu: true, info: {message: 'msg'}}));

handlebars.registerHelper('wrap1', function(s) {
	return '[' + s +  ']';
});
const template3 = handlebars.compile('wrap[]: {{wrap1 num}}');
console.log(template3({num: 0}));

console.log(ejs.render('arr: <%= arr.join(", "); %>', {arr: [1, 2, 3]}));

const template4 = ejs.compile(fs.readFileSync('./views/index.ejs').toString());
console.log(template4({title: 'index', files: files, path: __dirname, menu: true, info: {message: 'msg'}}));

// a.ejs : <%- include(views/b) %>
// views/b.ejs : ..


let template5 = lib.htmlObj2('<!--JS_MARK_mark1-->name: <!--JS_VAR_name--> <!--JS_MARK_mark2-->'); 
template5.name = 'Rumia';
console.log(template5.mark1);

let template6 = lib.htmlObj2('./views/index.html', true);
template6.title = 'title';
template6.path = __dirname;
template6.files = files;
template6.menu = true;
template6.files_n = 0;

template6.setF('vMenu0', function() {
	return (this.menu === true)?this.vMenu1:this.vMenu2;
});
// template6.vMenu0 = {toString: function() { return (template6.menu === true)?template6.vMenu1:template6.vMenu2;}}
template6.list = function() {
	let file = this.files[this.files_n];
	if(!file) {
		this.files_n = 0;
		return false;
	}
	this.files_n++;
	this.size = file.size;
	this.ctime = file.ctime;
	this.fn = file.fn;
	this.href = this.fn;
	// Object.assign(this, {href: ''});
	return true;
}
console.log(template6.ret);


var app = express();
var hbsapp = express();
var ejsapp = express();
var objapp = express();
function middleware_pstat(req, res, next) {
	const convertF = function(fn, stats) {
		const sizeArr = ['B', 'KB', 'MB', 'GB', 'TB'];
		let size = stats.size;
		let n = 0;
		while(size > 1024 && n !== 4) {
			size /= 1024;
			n++;
		}
		size = size.toFixed(2);
		let filename = fn + ((stats.isDirectory())?'/':'');
		this.size = size.toString() + sizeArr[n];
		return {fn: filename, href: encodeURI(filename), isDir: stats.isDirectory(), size: size.toString() + sizeArr[n], ctime: stats.ctime.toJSON()};
	};
	lib.pstatConvert(path.join(__dirname, decodeURI(req.path)), convertF, function(err, ret) {
		if(err) {
			req.pstat = {err: err};
			next();
			return;
		}
		if(ret.files && ret.sorted !== true) {
			ret.files.sort((a, b) => (b.isDir - a.isDir) || (b.fn.localeCompare(a.fn)));
			ret.sorted = true;
		}
		req.pstat = ret;
		next();
	});
}
function middleware_sendFile(req, res, next) {

	if(req.pstat.err) {
		res.status(404);
		res.send('404 Not found.');
	}
	else if(!req.pstat.files)
		res.sendFile(path.join(__dirname, decodeURI(req.path)));
	next();
}


app.get('/', function(req, res) {
	res.type('html');
	res.send(`<!DOCTYPE html>
<html><head><title>index</title></head><body>
	<div><a href="/hbs/">handlebars</a></div>
	<div><a href="/ejs/">ejs</a></div>
	<div><a href="/obj/">obj</a></div>
</body></html>`);
});

hbsapp.set('views', __dirname + path.sep + 'views');
hbsapp.set('view engine', 'hbs');
// handlebars.__express
hbsapp.get('/*', middleware_pstat, middleware_sendFile, function(req, res) {
	if(req.pstat.files)
		res.render('index', {title: 'index of ' + req.path, files: req.pstat.files, path: req.path, menu: true, info: {message: ''}});
});
app.use('/hbs', hbsapp);

ejsapp.set('views', __dirname + path.sep + 'views');
ejsapp.set('view engine', 'ejs');
ejsapp.get('/*', middleware_pstat, middleware_sendFile, function(req, res) {
	if(req.pstat.files)
		res.render('index', {title: 'index of ' + req.path, files: req.pstat.files, path: req.path, menu: true, info: {message: ''}});
});
app.use('/ejs', ejsapp);

objapp.get('/*', middleware_pstat, middleware_sendFile, function(req, res) {
	if(!req.pstat.files)
		return;
	template6.title = 'title';
	template6.path = req.path;
	template6.files = req.pstat.files;
	template6.menu = true;
	res.type('html');
	res.send(template6.ret);
});
app.use('/obj', objapp);


http.createServer(app).listen(8080);

function shds() {
	const template = template2;
	let arr = [];
	let search = '?page=1';
	for(let i = 0, j = files.length;i !== j;i++) {
		let file = files[i];
		const sizeArr = ['B', 'KB', 'MB', 'GB', 'TB'];
		let size = file.size;
		let n = 0;
		while(size > 1024 && n !== 4) {
			size /= 1024;
			n++;
		}
		size = size.toFixed(2);
		let fn = file.fn + ((file.isDir)?'/':'');
		let href = encodeURI(file.fn + ((file.isDir)?'/' + search:''));
		arr.push({fn: fn, href: href, size: size.toString() + sizeArr[n], ctime: file.ctime});
	}
	return template({title: 'index', files: files, path: __dirname, menu: true, info: {message: 'msg'}});
}
function sejs() {
	const template = template4;
	let arr = [];
	let search = '?page=1';
	for(let i = 0, j = files.length;i !== j;i++) {
		let file = files[i];
		const sizeArr = ['B', 'KB', 'MB', 'GB', 'TB'];
		let size = file.size;
		let n = 0;
		while(size > 1024 && n !== 4) {
			size /= 1024;
			n++;
		}
		size = size.toFixed(2);
		let fn = file.fn + ((file.isDir)?'/':'');
		let href = encodeURI(file.fn + ((file.isDir)?'/' + search:''));
		arr.push({fn: fn, href: href, size: size.toString() + sizeArr[n], ctime: file.ctime});
	}
	return template({title: 'index', files: files, path: __dirname, menu: true, info: {message: 'msg'}});
}


let template7 = lib.htmlObj2('./views/index.html', true);
template7.n = 0;
template7.setF('vMenu0', function() {
	return (this.menu === true)?this.vMenu1:this.vMenu2;
});
template7.list = function() {
	let file = this.files[this.n];
	if(!file) {
		this.n = 0;
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
	this.href = encodeURI(file.fn + ((file.isDir)?'/' + this.search:''));
	this.size = size.toString() + sizeArr[n];
	this.ctime = file.ctime;
	this.fn = file.fn + ((file.isDir)?'/':'');
	// Object.assign(this, {href: ''});
	return true;
}

function sobj() {
	template7.title = 'title';
	template7.path = __dirname;
	template7.files = files;
	template7.menu = true;
	return template7.ret;
}
function benchmarkF(f, j = 10000) {
	let n1 = Date.now();
	for(let i = 0; i !== j;i++) {
		let r = f();
	}
	return Date.now() - n1;
}


let t1 = benchmarkF(shds);
let t2 = benchmarkF(sejs);
let t3 = benchmarkF(sobj);
console.log('t', t1, t2, t3); // t 468 1672 258 // t 528 1462 253









