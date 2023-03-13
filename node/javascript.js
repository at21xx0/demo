"use strict";
// ??
/* ?? */

console.log('hello, world!');


var a = 1;
var b = 2;
var c = 1;
c = a + b; console.log(c);
console.log(c);
var str = '[str]';
const aa = 1;
// typeof str // str
// typeof a // number
// typeof false // typeof true // boolean
// typeof [0, 1, 2] // array
// typeof {code: 200} // object
// typeof 5
// typeof 5.5
var sArr = new Array();
sArr[0] = 'str';
sArr[1] = 's2';
sArr[2] = 's3';

// undefined null

var obj = {type: 'obj', code: 200, method: function(){console.log('method');}};
/*
var obj = {
	type: 'obj',
	code: 200,
	method: function() {
		console.log('method');
	}
};
*/
console.log(obj.type, obj.code, obj["code"]);
obj.method();
let obj_method = obj.method;
obj_method();

var var_g = 'func';

function func() {
	console.log(var_g);
}

function func2(var1, var2 = 'func2') {
	console.log(var1, var2);
}
function func3() {
	var s = '[str]';
	return s;
}

func();
func2('func');
console.log(func3);

var s2 = '[str2]';
var s3 = "[str3]";
var s4 = '"\'\'";+\\\t\b\f\r\n';
var s5 = new String('[str5]');
var s6 = 'str1|str2|str3|str4';
var s = 'str';
let i = 0;
let start = 0;
let len = 0;
let end = 0;
console.log(s2, s3, s4, s2[0], s2[1], s2[2], s2.length, s2[s2.length - 1]);
console.assert(s2.charCodeAt(2) === "t".charCodeAt(), 'charCodeAt');
console.assert(typeof s2 !== typeof s5, 'type'); // string object
console.assert(s2.charAt(0) === s2[0], 'charAt');
// console.log(String.fromCharCode(189, 43, 190, 61));

start = 1;
end = s2.length - 1;
len = end - start;
console.assert(s2.slice(start, end) === 'str2', 'string slice');
console.assert(s2.substring(start, end) === s2.substr(start, len), 'string substr');

len = s.length + 1;
start = s6.indexOf(s);
console.assert(start !== -1, 'indexOf');
console.assert(s6.substr(start, len) === 'str1', 'string indexOf');

start = s6.indexOf(s, start + 1);
console.assert(start !== -1, 'indexOf');
console.assert(s6.substr(start, len) === 'str2', 'string indexOf');

start = s6.lastIndexOf(s);
console.assert(s6.substr(start, len) === 'str4', 'string indexOf');

start = s6.lastIndexOf(s, start - 1);
console.assert(s6.substr(start, len) === 'str3', 'string indexOf');

console.assert(s.localeCompare('str') === 0, 'cmp');
console.assert(s.localeCompare('sts') < 0 && s.localeCompare('stq') > 0, 'cmp');
console.assert(s2.replace('str2', 'str') === str, 'replace');
console.log(s6.split('|'));
// match search replace
console.assert(s.toLocaleUpperCase() === 'STR', 'upper');
// toLocaleLowerCase()
// toLocaleCase()
// toString() valueOf()
s3 = ' ' + s + '\t';
console.assert(s.trim() === s, 'trim');
console.assert(s.concat('2') === 'str2', 'concat');


// + - * / % i++ i-- --i ++i
// a == b
// a === b // a == b && typeof a = typeof b
// != !== > < >= <=
// && || !

if(0)
	console.log(0);
if(1)
	console.log(1);
else if(s === 'str')
	console.log(s);
else
{
	console.log('else');
	s = null;
}
i = 1;
switch(i) {
	case 0:
		console.log(0);
		break;
	case 1:
		console.log(1);
	case 2:
		i = 3;
		break;
	default:
		i = 0;
		break;
}
console.assert(i === 3, 'switch');
i = 0;
for(let j = 0;j < 5;j++)
{
	i++;
}
console.assert(i === 5, 'for 1');

for(let x in obj) {
	console.log(x, obj[x]);
}

// for(;i < 5;i++) {}
while(i < 5)
{
	i++;
}
console.assert(i === 5, 'while 1');
i = 0;
do
{
	i++;
}while(i < 5);
console.assert(i === 5, 'while 2');

for(i = 0;i < 5;i++)
{
	if(i == 3)
		break;
}
console.assert(i === 3, 'for 2');
i = 0;
for(let j = 0;j < 5;j++)
{
	if(j == 3)
		continue;
	i++;
}
console.assert(i === 4, 'for 3');

console.assert(typeof i === 'number', 'type 1');
console.assert(typeof null === 'object', 'type 2');
console.assert(typeof undefined === 'undefined', 'type 2');
console.assert(typeof NaN === 'number', 'type NaN');
console.assert(typeof new Date() === 'object', 'type Date');
console.assert(typeof func2 === 'function', 'type function');
console.assert(s.constructor === String, 'constructor String'); // String Number Boolean Array Object Date Function
// console.assert(new String(i) === i.toString(), 'convert');
console.log(new String(new Date()));
console.assert(Number('5') === 5, 'number');
console.assert(parseInt('0xA') < parseFloat('10.5'), 'parseInt');


s2 = 'String1 string2';
console.assert(s2.search(/str\w+/i) === 0, 'search 1');

s2 = '[str2]';
console.assert(s2.replace(/str\d+/i, '0') === '[0]', 'replace 1');

console.assert(s6.replace(/str(\d+)/igm, '$1') === '1|2|3|4', 'replace 2');

console.assert(s2.replace(/\w+/ig, "_$`_$&_$'_") === '[_[_str2_]_]', 'replace 3');

console.assert(/str/ig.test(s2) === true, 'regex test');

var r = /str\d+/ig.exec(s2);
console.assert(r !== null && r[0] === 'str2', 'regex exec');

i = 0;
try{
	console.log(5 / i);
	// if(isNaN(i))throw Error('NaN');
	// if(isFinite(i))throw Error('0');
} catch(err) {
	console.log('err', err);
} finally {
	i = 5;
}
// i === 5;
// console.log(ggg); var ggg = 'ggg';
obj.testThis = function(arg1 = 'test this') {
	console.log(arg1, this.code); // 200
};
var testThis = function() {
	if(this === undefined)
		console.log('undefined');
	// global
}
obj.testThis();
testThis();
obj.testThis.call({code: 304}, 'test call');

const n = 5;
// n = 0;
// var a = 1;
{
	let a = 0;
}
console.assert(a === 1, 'let');

let jsonObj = {code: 200};
let jsonStr2 = JSON.stringify(jsonObj); // {"code":200}
let jsonObj2 = JSON.parse(jsonStr2);
console.assert(jsonObj.code === jsonObj2.code, 'json');
void(0);

i = 1;
new Promise(function(resolve, reject) {
	// i = k;
	// reject(new Error('err'));
	if(i == 0)
		reject('Error');
	else
		resolve(i);
}).then(function(success) {
	console.log(success);
	return new Promise(function(resolve, recect) {
		resolve(i * 10);
	});
}, function(err) {
	console.log('err', err);
	// throw err;
}).then(function(v) {
	console.log(v);
	// throw new Error('err');
}).catch(function(e) { // prev_then
	console.log('catch:', e);
}).finally(function() {
	console.log('promise_finally');
});
/*
setTimeout(function() {
	console.log('sync');
}, 0);
*/

function syncFunc(t) {
	return new Promise(function(resolve, reject) {
		setTimeout(function() {
			console.log('syncfunc', t);
			resolve(t);
		}, t);
	});
}
(async function(){
	// await syncFunc(50);
	let t = await syncFunc(20);
	console.log('await', t);
})();
// new Function('a', 'b', 'return a + b');
var ff = function() {
	return arguments;
}
console.log(ff('arg1', 'arg2'));
// console.log(ff.toString());
// ff = (arg1) => arg1;
ff = (a, b) => a * b;
ff = (a, b) => {return a + b};
i = ((a, b) => a + b)(1, 2); // i = 1 + 2;
ff = function(a, b = null) {
	let c = a || null; // undefined || null
	return c;
}
const max = function() {
	let i, max = arguments[0], len = arguments.length;
	for(i = 0;i < len;i++)
	{
		if(arguments[i] > max)
			max = arguments[i];
	}
	return max;
}
console.assert(max(1, 2, 3, 5, 2) === 5, 'max');
function consF(i, j) {
	if(!(this instanceof consF))
		return new consF(i, j);
	this.i = i;
	this.j = j;
	/*
	this.add = function() {
		return this.i + this.j;
	}
	*/
}
consF.prototype.add = function(k = 0) {
	return this.i + this.j + k;
}
consF.prototype.k = 0;
consF.prototype.getK = function() { return this.k;};
consF.get0 = () => 0; // static
consF.prototype.valueOf = function() {return 0;}
consF.prototype.toString = function() {return 0;}

let objF = new consF(2, 5);
console.assert(objF.i === 2, 'objF i');
console.assert(objF.add() === 7, 'objF add');
// console.assert(consF(2, 5) === 7, 'constF');
console.assert(max.call(this, 2, 5) === max.apply(this, [2, 5]), 'max call');
console.assert(objF.add.call(objF) === objF.add(), 'objF add call');
console.assert(objF.getK() === 0, 'prototype k');
console.assert(consF.get0() === 0, 'static get0');
console.assert(objF instanceof consF && Object.getPrototypeOf(objF).constructor === consF, 'instanceof');
console.assert(objF == 0 && objF == '0', 'objF equal');
// function.bind(thisArg[, arg1[, arg2[, ...]]])
objF = consF.prototype.add.bind(objF, 7);
console.assert(objF() === 14, 'f bind');

function consFF(i, j, t = 0) {
	if(this === undefined)
		return i + j + t;
	Object.defineProperty(this, '_t', {
		writable: true,
		value: t
	});
	Object.defineProperty(this, 't', {
		// configure: true, // Object.defineProperty
		get: function() {
			return this._t;
		}, 
		set: function(t) {
			this._t = t;
		}
	});
	// Object.defineProperties(this, {'val': {value: 1}, 'get0': {get:() =>0, set:()=>void(0)}});
	consF.call(this, i, j);
}
consFF.prototype = Object.create(consF.prototype, {
	'add': {
		value: function(e = 0){
			return consF.prototype.add.call(this, e) + this._t;
		}
	}
});
consFF.prototype.constructor = consFF;
consFF.get0 = consF.get0;

let objFF = new consFF(2, 5, 7);
console.assert(objFF.i === 2, 'objFF i');
console.assert(objFF.add(9) === 23, 'objFF add');
console.assert(consFF.get0() === 0, 'objFF get0');
objFF.t = 0; // get t()
console.assert(objFF.t === 0, 'objFF t');
console.assert(objFF instanceof consFF && objFF instanceof consF, 'instanceof consFF');


ff = (function() {
	var c = 1;
	return function() {return c++;};
})();
/*
console.log(ff());
console.log(ff());
console.log(ff());
*/
class ClassA{
	constructor(i = 0, j = 0) {
		this.i = i;
		this.j = j;
	}
	add(e) {
		e = e || 0;
		return this.i + this.j + e;
	}
};
/*
let ClassB = class{
	constructor(i, j) {
		this.i = i;
		this.j = j;
	}
};
*/

class ClassB extends ClassA{
	constructor(i, j, t){
		super(i, j);
		this._t = t || 0;
	}
	add(k = 0) {
		return super.add(k) + this._t;
	}
	static get0() {
		return 0;
	}
	get t() {
		return this._t;
	}
	set t(tt) {
		this._t = tt;
	}
}

let objA = new ClassA(2, 5);
console.assert(objA.i === 2, 'objA i');
console.assert(objA.add() === 7, 'objA add');

objA = new ClassB(2, 5, 7);
console.assert(objA.i === 2, 'objB i');
console.assert(objA.add(9) === 23, 'objB add');
console.assert(ClassB.get0() === 0, 'ClassB get0');
objA.t = 0; // get t()
console.assert(objA.t === 0, 'ClassB t');
console.assert(objA instanceof ClassA && objA instanceof ClassB, 'instanceof ClassB');

obj = new Object(); // obj = {i: 5, code: 200, message: 'ok'};
obj.i = 5;
obj.code = 200;
obj.message = 'ok';
// let obj2 = Object.create(obj, {getCode: {value:function() {return this.code;}}}); 
let obj2 = Object.assign({}, obj);
// let obj2 = Object.assign({}, obj, {j: 2});
Object.assign(obj2, {j: 2, getCode: function(){return this.code}});
console.assert(obj2.getCode() === obj.code && !obj.getCode && obj2.j === 2, 'create assign');
// {i: 2, j: 5}; // new consF(2, 5);
/*
for(let x in obj)
{
	console.log(x, obj[x]);
}
*/
let obj3 = obj;
obj3.message = 'OK';
console.assert(obj.message == obj3.message, 'obj message');

i = 10000000000000000;
i = 0xFF;
console.assert(i.toString(16).toLocaleUpperCase() === 'FF', 'hex');
// i = Infinity;
// isNaN('str'); // false
// typeof(i) === 'number'
console.assert(isFinite(Infinity) === false, 'inf');
// isInteger(5) // true // Number.isInteger
// i.toFIxed(2) // 255.00
// i.toExponential() // 2.55e+2
// i.toPrecision(2) // 2.6e+2

let d = new Date();
// console.log(new Date().toString());
// console.log(new Date().toUTCString());
console.assert(new Date().getTime() === Date.now(), 'getTime');
// Date.now() // Fast
// d = new Date(milliseconds);
let d2 = new Date('Fri, 02 Dec 2022 03:33:39 GMT');
// var d = new Date(year, month, day, hours, minutes, seconds, milliseconds);
let d3 = new Date(d.getFullYear(), d.getMonth(), d.getDate(), d.getHours(), d.getMinutes(), d.getSeconds(), d.getMilliseconds());
// d.getDay() // 0-6
// d.getMonth() // 0-11
// getUTCDay getUTCMonth
// d.setDate(1); // 1 - 31
// console.log(d.toString(), d3.toString());
console.assert(d > d2, 'date cmpare');
// console.log(d.toUTCString(), d.toString(), d.toLocaleDateString(), d.toLocaleTimeString(), d.toTimeString(), d.toISOString(), d.toJSON(), d.valueOf());


let arr = new Array();
// arr = [];
arr[0] = 0;
arr[1] = 1;
arr[2] = 2;
// arr = [0, 1, 2];
console.assert(arr[0] === 0, 'arr[0]');
console.assert(arr.length === 3, 'arr.length');
let a2 = [3, 4];
let a3 = arr.concat(a2); // arr.concat(arr1, arr2, ...);
console.assert(a3.length !== arr.length, 'concat');
// arr = a3;
let a4 = ['target', '1', '2', '3', 'start', '5', 'end'];
len = 0;
start = 4;
end = a4.length; // default a4.length
let target = 0;
a4.copyWithin(target, start, end);
//  ['start', '5', 'end', '3', 'start', '5', 'end']
let iter = a3.entries();
while(1) {
	let t = iter.next();
	// console.log(t.value);
	if(t.done === true)
		break;
}
// for(const [key, value] of Object.entries(a3)) {console.log(key, value);}
// for(const value of a3) {console.log(value);}
// a3.forEach((x) => console.log(x));

console.assert(a3.every((x) => (x < 10)), 'every'); // array.every(function(currentValue,index,arr), thisValue)
a2.fill(0); // array.fill(value, start, end)
console.log(a3.filter((x) => (x < 2))); //  array.filter(function(currentValue,index,arr), thisValue)
console.assert(a3.find((x) => (x < 2)) === 0, 'find'); //  array.filter(function(currentValue,index,arr), thisValue)
// array.findIndex(function(currentValue, index, arr), thisValue) // -1
// array.forEach(callbackFn(currentValue, index, arr), thisValue)

// Object.assign(target, source)
a2 = Array.from('str'); // Array.from(object, mapFunction, thisValue)
// Array.from(new Set('a', 'b', 'c')) Array.from([a3], (x) => x * 2);
console.assert(a3.includes(0) === true, 'include'); // arr.includes(searchElement, fromIndex)
// indexOf
console.assert(Array.isArray(arr) === true, 'isArray');
console.assert(arr.join('|') === '0|1|2', 'join');
a2 = arr.keys();
// lastIndexOf
a3.map((x) => x * 2);
len = arr.length + 1;
console.assert(arr.push(3) === len, 'push');
i = arr[0];
console.assert(arr.shift() === i, 'shift');
console.assert(arr[0] !== i, 'shift 2');
i = 0;
arr.forEach((x) => i += x);
console.assert(arr.reduce((a, b) => (a + b)) === i, 'reduce');
// array.reduce(function(total, currentValue, currentIndex, arr), initialValue)
// array.reduce(function(total, currentValue, currentIndex, arr), initialValue)
arr.reverse();
arr.sort(); // array.sort(sortfunction) // (a, b) => (a - b); // (a, b) => a.localeCompare(b)
// [1, 2, 3];
a2 = arr.slice(1, arr.length - 1);
console.assert(a2.length === 1 && a2[0] === 2, 'slice'); 
console.assert(arr.some((x) => (x > 2)) === true, 'some'); 

a4 = ['start', '1', '2', 'delete_1', 'delete_2', '5', 'end'];
a4.splice(3, 2, '3', '4');
// [ 'start', '1', '2', '3', '4', '5', 'end' ]
// console.log(a4.toString());
// array.splice(index,howmany,item1,.....,itemX)
// len = arr.unshift(0);
// array.valueOf();

// console.log(true.toString());
console.assert(true.valueOf() === true, 'Boolean valueOf()');
// new Boolean(0).valueOf() // 0 -0 null '' false undefined NaN
// console.log(Math.random());
i = Math.round(Math.random() * 10);
console.log(i);
// setTimeout(() => console.log(1), 1000);
let interval;
interval = setInterval(() => {
	if(i == 10)
	{
		clearInterval(interval);
		return;
	}
	i++;
	// console.log('i', i);
}, 1);
// setTimeout clearTimeout 
// let str = `${i}kk`;





