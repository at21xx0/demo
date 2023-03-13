var process = require('process');
var path = require('path');
var fs = require('fs');
var test;

try{
	test = require('./build/Release/test');
} catch(e) {
	test = null;
}


test = (function(test){
	if(test !== null)
		return test;
	let test1 = function(){return '[str]';}
	let testType = function(arg0, arg1, arg2, arg3, arg4, arg5) {
		if(typeof arg0 !== 'number' || typeof arg1 !== 'number' || typeof arg2 !== 'boolean' || typeof arg3 !== 'function' || typeof arg4 !== 'string' || !Array.isArray(arg5))
			throw new TypeError('number number boolelan function string array');
		let value = arg0 + arg1;
		let result = arg3.call(global, value);
		let bool = (arg2)?false:true;
		let obj = {arg0: arg0, arg0_add_arg1: value, callback_result: result, fn: test1
		, bool: bool, str: '[' + arg4 + ']'};
		obj[value] = result;
		console.log.apply(console, arg5);
		let arr = [];
		for(let i = 0;i != 5;i++)
			arr[i] = i;
		obj.arr = arr;
		return obj;
	}
	function PObj(a = 0) {
		if(!(this instanceof PObj))
			return new PObj(a);
		if(typeof a === 'number')
			this._v = a;
		else if(a instanceof PObj) {
			this._v = a.v;
		}
		Object.defineProperty(this, 'v', {
			// configure: true,
			get: function() {
				return this._v;
			}, 
			set: function(v) {
				this._v = v;
			}
		});
	}
	PObj.prototype.plusOne = function() { return this.v += 1;}
	function msleep(m) {
		return new Promise(function(resolve, reject) {
			setTimeout(resolve.call(this), m);
		});
	}
	function testAsync(a1, a2) {
		let promise = new Promise(async function(resolve, reject) {
			// thread // async_execute
			await msleep(1000);
			if(typeof a1 == 'function')
				resolve(a1(true));
			if(a1 !== false)
				resolve(true);
			else
				reject(new Error("testAsync_error"));
		});
		if(typeof a1 === 'boolean') {
			if(typeof a2 === 'function')
				promise.then((value) => a2(value), (error) => a2(undefined, error));
			else
				return promise;
		} else
			promise.then(() => void(0));

	}
	function copyBuffer(buffer) {
		return Buffer.from(buffer);
	}
	function loadFile(fn, data, end, e) {
		file = fs.createReadStream(fn);
		file.on('data', data);
		file.on('end', end);
		return {
			pause: file.pause.bind(file),
			resume: file.resume.bind(file)
		};
	}
	return {test: test1, testType: testType, PObj: PObj, testAsync, testAsync, copyBuffer: copyBuffer, loadFile: loadFile};
})(test);
console.log(test.test());
obj = test.testType(1, 2, true, function(n){console.log('n', n);return n * n;},
	'str', 
	['console_log:', 1, 2, 45]
);
console.assert(obj.arg0 === 1, "err_1");
console.assert(obj.arg0_add_arg1 === 3, "err_2");
console.assert(obj.callback_result === 9, "err_3");
console.assert(obj.fn() === "[str]", "err_4");
console.log(obj);
console.log(test.PObj);
var ob = new test.PObj(5); // PObj_new
// var ob = test.PObj(5);
console.log(ob.plusOne());
console.log(ob.plusOne());
console.log(ob.plusOne());
console.log(ob.plusOne());
ob.v = 1; // PObj_setv
console.log(ob.v); // PObj_getv

var o2 = test.PObj(ob);
console.log(o2.v);
var successCount = 0;
var errorCount = 0;
let callbackSuccess = function(){successCount++;};
let callbackError = function(){errorCount++;};
let callback = function(value, error) {
	if(error)
		callbackError();
	else
		callbackSuccess();

};
test.testAsync(true).then(callbackSuccess, callbackError); // resolve(true);
test.testAsync(false).then(callbackSuccess, callbackError); // reject(err);
test.testAsync(false, callback); 
test.testAsync(callback); // threadsafe_function
test.testAsync(true, callback);
test.testAsync(callback);
setTimeout(function() {
	console.log(successCount + errorCount , '/', 6, 'done');
}, 1200);
process.addListener('exit', function(code) {
	// 
	console.assert(successCount == 4 && errorCount == 2, 'async count');
	console.log('6 / 6 done');
});
// console.log(test.nVersion());

console.assert(test.copyBuffer(Buffer.from('[str]')).toString() === '[str]', 'buffer');
let stream = fs.createWriteStream('main_backup.js');
let tobj = test.loadFile(path.normalize(__dirname + '/' + 'main.js'), function(data) {
	// tobj.pause();
	// setTimeout(tobj.resume.bind(tobj.resume), 50);
	if(stream.write(data) === false) {
		tobj.pause();
	}
	if(tobj.setResume === undefined) {
		tobj.setResume = true;
		stream.on('drain', function() {
			tobj.resume();

		});
	}
}, () => function() {
	stream.close();
}, true);


