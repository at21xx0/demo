var sqlite3 = require('sqlite3');
var fs = require('fs');
var path = require('path');
var crypto = require('crypto');


// https://github.com/TryGhost/node-sqlite3/wiki/API


const db_file = './test.db';
let db_exists = fs.existsSync(db_file);
let db = new sqlite3.Database(db_file); // ':memory:';

if(db_exists === false) {
	// run(sql [, param, ...] [, callback])
	// db.run('PRAGMA synchronous = OFF;'); // BEGIN COMMIT require('TransactionDatabase');
	db.run('CREATE TABLE user (name VARCHAR(127) UNIQUE NOT NULL, passwd VARCHAR(63) NOT NULL);');
	db.run("INSERT INTO user (name, passwd) VALUES (?, ?);", ['root', 'root']);
	db.run("INSERT INTO user (name, passwd) VALUES ($name, $passwd);", {name: 'custom', passwd: '123'});
}

let token = 'QKRqwJ9eAxqU';
let buf = Buffer.alloc(9); 
crypto.randomFillSync(buf);
let passwd = buf.toString('base64');
let user = buf.toString('hex');

db.run(`INSERT INTO user (name, passwd) VALUES ('${user}', '${passwd}');`, function(e) {
	if(e) console.log(e);
	// get(sql [, param, ...] [, callback]);
	// db.get('SELECT name, passwd FROM user WHERE name=\'custom\';', (err, row) => console.log(err, ret));
	db.get('SELECT COUNT(*) AS len FROM user;', function(err, row) {console.log('count:', (row && row.len));});
	// all(sql [, param, ...] [, callback])
	db.all('SELECT name FROM user ORDER BY name;', function(err, rows) {
		let arr = [];
		if(rows) {
			rows.forEach(function(row) {this.push(row.name);}, arr);
			console.log('user: %s', arr.join(', '));
		}
	});
});
/*
db.serialize(() => {
    db.run("CREATE TABLE lorem (info TEXT)");

    const stmt = db.prepare("INSERT INTO lorem VALUES (?)");
    for (let i = 0; i < 10; i++) {
        stmt.run("Ipsum " + i);
    }
    // finalize([callback]);
    stmt.finalize();

    db.each("SELECT rowid AS id, info FROM lorem", (err, row) => {
        console.log(row.id + ": " + row.info);
    });
});
*/


db.close(() => void(0));

