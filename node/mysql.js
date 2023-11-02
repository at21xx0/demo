"use strict";

// var fs = require('fs');
var mysql = require('mysql');
var process = require('process');
var path = require("path");

var config = {
	host: "localhost",
	user: "root",
	password: "123",
	port: 3306,
	database: "db1",
	charset: "utf8mb4",
	/*
	ssl: {
		ca : fs.readFileSync(__dirname + '/mysql-ca.crt')
		// rejectUnauthorized: false
	},
	*/
	multipleStatements: true,
	connectLimit: 10
};
// var db = mysql.createConnection(config); db.connect(function(err) { if(err) throw err; });
var pool = mysql.createPool(config); // pool.getConnection(function(err, connection) {connection.release()})


function newPM() {
	let promise = false;
	let b = false;
	let cb = (t) => t;
	let ret = null;
	return function(r = newPM) {
		if(r === newPM) {
			return new Promise(function(resolve, reject) {
				promise = true;
				cb = resolve;
				if(b) {
					cb(ret);
					ret = null;
					b = promise = false;
				}
			});
		} else if(promise) {
			promise = false;
			cb(r);
		} else {
			ret = r;
			b = true;
		}
	};
}



function qcb(cb) {
	cb();
}

(async function(r) {
	if(r)
		return;
	let pm = newPM();
	let ret = null;
	setTimeout(function() {
		pm(1);
	}, 500);
	ret = await pm();
	console.log(ret);
	setTimeout(function() {
		pm(2);
	}, 500);
	ret = await pm();
	console.log(ret);
	setTimeout(function() {
		pm(3);
	}, 500);
	ret = await pm();
	console.log(ret);
	qcb(function() {
		pm(4);
	});
	ret = await pm();
	console.log(ret);
	qcb(function() {
		pm(5);
	});
	ret = await pm();
	console.log(ret);
	setTimeout(function() {
		pm(6);
	}, 500);
	ret = await pm();
	console.log(ret);
})(true);


function transaction(pool, arrayOrCallback) {
	var obj = {err: null, commit: null, rollback: null, getCallback: null, n_arg: 0, result: [], cb: null};
	return new Promise(function(resolve, reject) {
		if(arrayOrCallback.constructor === Function)
			reject = function(err) { arrayOrCallback(err, null, null, null);reject(err);};
		else if(arrayOrCallback && arrayOrCallback.constructor !== Array)
			return reject(new TypeError("arrayOrCallback"));
		pool.getConnection(function(err, connection) {
			if(err) return reject(err);
			connection.beginTransaction(function(err) {
				if(err) {
					connection.release();
					return reject(err);
				}
				obj.commit = function() {
					connection.commit(function(err) {
						connection.release();
						obj.cb = null;
						if(err) return reject(err);
						resolve(obj);
					});
				};
				obj.rollback = function(e = null) {
					connection.rollback(function(err) {
						connection.release();
						obj.cb = null;
						if(err) return reject(e || err);
						resolve(e);
					});
				};
				if(arrayOrCallback.constructor === Function)
					return arrayOrCallback.call(obj, err, connection, commit, reject);
				let arr = [];
				let next = function(err = null) {
					if(err) return obj.rollback(err);
					if(arrayOrCallback.length === obj.n_arg) {
						obj.commit();
						return null;
					}
					let arg = arrayOrCallback[obj.n_arg++];
					let sql = arg[0];
					let value = arg[1] || false;
					let cb = arg[2] || null;
					if(value && value.constructor === Function) {
						cb = value;
						value = false;
					}
					connection.query(sql, value, function(err, result, fields) {
						if(err) return obj.rollback(err);
						obj.result.push(result);
						obj.cb = next;
						if(cb !== null)
							cb.call(obj, err, result, fields);
						if(obj.cb !== null)
							obj.cb(null);
					});
				};
				obj.getCallback = function() {
					if(err) return this.rollback(err);
					let cb = this.cb;
					this.cb = null;
					return cb;
				};
				next();
				/*
				for(let arg of arrayOrCallback) {
					arr.push(new Promise(function(resolve, reject) {
						let sql = arg[0];
						let value = arg[1] || null;
						let cb = arg[2] || null;
						if(value && value.constructor === Function) {
							cb = value;
							value = false;
						}
						connection.query(sql, value, function(err, result, fields) {
							if(err) return reject(err);
							if(cb != null)
								cb.call(obj, err, result,fields);
							resolve(result);
						});
					}));
				}
				Promise.all(arr).then(function(result) {
					obj.result = result;
					console.log(result);
					obj.commit();
				}).catch(function(err) {
					console.log(err);
					obj.rollback(err);
				});
				*/
			});
		});
	});
}



(async function() {
	let pm = newPM();
	let e = null;
	let rows = null;
	let err = null;
	let query = async function(sql, value, cb) {
		if(value && value.constructor === Function) {
			cb = value;
			value = false;
		}
		pool.query(sql, value, function(err, result, fields) {
			cb(err, result, fields);
			pm(null);
		});
		await pm();
	};
	let save = function(e, v) {
		if(e) console.log(e);
		err = e;
		rows = v;
	};
	let qu = function(sql, value = false) {
		return new Promise(function(resolve, reject) {
			pool.query(sql, value, function(err, result, fields) {
				if(err !== null)
					reject(err);
				else
					resolve(result);
			});
		});
	};
	/*
	await query('SELECT * FROM information_schema.SCHEMATA WHERE SCHEMA_NAME="db1"', save);
	if(err !== null || rows.length === 0)
		await query('CREATE DATABASE db1;', save); //CREATE DATABASE IF NOT EXISTS db1 DEFAULT CHARACTER SET utf8mb4 DEFAULT COLLATE utf8mb4_0900_ai_ci 
	// use db1;
	*/
	await query('SELECT * FROM information_schema.TABLES WHERE TABLE_NAME="table1";', save);
	if(err !== null || rows.length === 0)
		await query('CREATE TABLE table1(i INT NOT NULL DEFAULT 0, b BIGINT NOT NULL DEFAULT 0, f FLOAT NOT NULL DEFAULT 0.0, d DECIMAL(12, 2) NOT NULL DEFAULT 0.0, p BIGINT AS (i + b), CONSTRAINT check1 CHECK(i > 0 OR b > 0)) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;', save); // d 00000000000.00
	// size: TINYINT 1 SMALLINT 2 MEDIUMINT 3 INT 4 INTEGER 4 BIGINT 8 FLOAT 4 DOUBLE 8 DECIMAL(M, D)
	// BIT CHARACTER(n) VARCHAR(n) BINARY(n) BOOLEAN VARBINARY(n) INTEGER(p) SMALLINT INTEGER BIGINT DECIMAL(p,s) NUMERIC(p,s) FLOAT(p) REAL FLOAT DOUBLE PRECISION DATE TIME TIMESTAMP ARRAY MULTISET XML
	// if(err !== null) console.log(err);
	await query('SELECT * FROM information_schema.TABLES WHERE TABLE_NAME="table2";', save);
	if(err !== null || rows.length === 0)
		await query('CREATE TABLE table2(name VARCHAR(30) NOT NULL PRIMARY KEY, id INT NOT NULL UNIQUE CHECK(id > 0)) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;', save); // CREATE TABLE table2(name VARCHAR(30) NOT NULL, id INT NOT NULL CHECK(id > 0), PRIMARY KEY (name), UNIQUE (id)) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
	await query('SELECT * FROM information_schema.TABLES WHERE TABLE_NAME="table4";', save);
	if(err !== null || rows.length === 0)
		await query('CREATE TABLE table4(n INT NOT NULL AUTO_INCREMENT, name VARCHAR(30), d DATE NOT NULL DEFAULT CURRENT_DATE(), PRIMARY KEY (n), FOREIGN KEY (name) REFERENCES table2(name)) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;', save); // CREATE TABLE table4(n INT NOT NULL AUTO_INCREMENT=1000, name VARCHAR(30) FOREIGN KEY REFERENCES table2(name));
	// ALTER TABLE table1 DROP CHECK check1 // SQL Server | Oracle | MS Access: DROP CONSTRAINT check1
	// CREATE INDEX index_name ON table_name (column_name); // (column_name1, column_name2) // UNIQUE INDEX
	// ALTER TABLE table_name DROP INDEX index_name // MS Access: DROP INDEX index_name ON table_name // MS SQL Server: DROP INDEX table_name.indeX_name // DB2/Oracle: DROP INDEX index_name

	// CREATE DATABASE db_name;
	// DROP DATABASE db_name;
	// TRUNCATE TABLE table_name;
	// DROP TABLE table_name;

	// ALTER TABLE table2 MODIFY i INT NULL DEFAULT 0;
	// ALTER TABLE table2 ADD UNIQUE (id) // ADD CONSTRAINT fk_name_table2 UNIQUE (name, id) // foreignkeyname
	// ALTER TABLE table4  DROP FOREIGN KEY fk_name_table4 // SQL Server | Oracle | MS Access: ALTER TABLE table4 DROP CONSTRAINT fk_name_table4
	// ALTER TABLE table4 ADD FOREIGN KEY (name)  REFERENCES table2(name)

	// ALTER TABLE table_name ADD column_name datatype
	// ALTER TABLE table_name DROP COLUMN column_name
	// ALTER TABLE table_name MODIFY COLUMN column_name datatype // SQL Server | MS Access: ALTER TABLE table_name ALTER COLUMN column_name datatype

	// AUTO_INCREMENT // d INT AUTO_INCREMENT=100 // Access: ID Integer AUTOINCREMENT // Orcale

	await query('DELETE FROM table1 WHERE i != 1002;', save);
	await query('DELETE FROM table4;', save); // name foreign key table2(name)
	await query('DELETE FROM table2;', save);
	await query('INSERT INTO table1 (i, b, f, d) VALUES (?, ?, ?, ?);', [5, 4, 3.2, 1.0], save); // INSERT INTO table1 (i, b, f, d) VALUES (5, 4, 3.2, 1.0), (0, 1, 2.3, 4,56);
	await query('INSERT INTO table1 (i, b, f, d) VALUES ?;', [[[0, 1, 2.34, 5.67], [1, 2, 9.9, 77.77], [1, 1, 1.1, 1.11]]], save);
	await query('INSERT INTO table2 (name, id) VALUES ?;', [[["[str]", 1], ["none", 2], ["name", 3]]], save);
	await query('SELECT * FROM table1', save);
	console.log(rows);
	await query('SELECT DISTINCT i FROM table1;', save); // SELECT DISTINCT i, b, f, d FROM table1;
	console.log(rows);
	console.log(await qu('SELECT i, b, f, d FROM table1 WHERE i > 0 AND i <> 1 OR (i BETWEEN 0 AND 9 OR i IN (10, 17, 47));')); // <> != // = > < >= <= // () not and or // NOT BETWEEN // d BETWEEN '2023-10-1' AND '2023-10-7'
	console.log(await qu('SELECT name, id FROM table2 WHERE name LIKE "n%" AND name LIKE "n%e" AND name LIKE "n__e" AND name LIKE "%no%" AND name NOT LIKE "n[^o]%" AND NOT id IS NULL AND EXISTS (SELECT id FROM table1, table2 WHERE table2.id = table1.i);')); // NOT (id IS NULL) // id IS NOT NULL // EXISTS select_statement | NOT EXISTS
	console.log(await qu('SELECT i, b, f, d, p FROM table1 WHERE b = (SELECT max(b) FROM table1);'));
	console.log(await qu('SELECT i, b, f, d, p FROM table1 WHERE b IN (SELECT b FROM table1 WHERE b > 2);'));
	// name = b // name REGEXP '^[abc]' // name REGEX '^[^def]' // name REGEX '^[0-9A-Fa-f]'
	console.log("<hr>\n");
	console.log(await qu('SELECT i, b, f, d FROM table1 ORDER BY i;')); // default ASC
	console.log(await qu('SELECT i, b, f, d FROM table1 WHERE i != 5 ORDER BY i, b DESC;'));
	await query('INSERT INTO table2 (name, id) VALUES (?, ?);', ['test', 16], save);
	await qu('UPDATE table2 SET id = 17 WHERE name = "test";');
	await qu('DELETE FROM table2 WHERE name = "test";');
	// SQL Server | MS Access : SELECT TOP number|percent column_name(s) FROM table_name // SELECT TOP 20 PRECENT * FROM table_name
	// Orcale SELECT column_name(s) FROM table_name WHERE ROWNUM <= number
	console.log(await qu('SELECT name, id FROM table2 LIMIT 2')); // LIMIT offset, n // LIMIT n : LIMIT 0, n //  LIMIT 0, -1 : nolimit
	console.log(await qu('SELECT i AS a, b, (i + b) AS c, ROUND(IFNULL(f, 0)) AS d FROM table1;'));
	// IFNULL(v, 0) IFNULL(NULL, 0):0 // COALESCE(v, 0) // Oracle: NVL(v, 0) // SQL Server | MS Access: ISNULL(v, 0)
	// IF(statement, TRUE_VALUE, FALSE_VALUE) // IF(v = NULL, v, 0)

	// A B // A.key AS a B.key AS b
	// LEFT JOIN ON a = b: A
	// LEFT JOIN ON a = b WHERE b IS NULL: A - B
	// INNER JOIN ON a = b: A & B
	// FULL OUTER JOIN ON a = b: A + B - (A & B)
	// FULL OUTER JOIN ON a = b WHERE a IS NULL OR b IS NULL: A + B - (A & B) - (A & B)
	// RIGHT JOIN ON a = b: B
	// RIGHT JOIN ON a = b WHERE a IS NULL: B - A

	console.log('JOIN');
	console.log(await qu('SELECT a.b, name, i FROM table1 AS a, table2 AS b WHERE a.b = b.id;')); // SELECT table1.b, name, i FROM table1, table2 WHERE table1.b = table2.id; // CROSS JOIN
	console.log(await qu('SELECT b, name, i FROM table1 JOIN table2 ON b = id;')); // INNER JOIN

	console.log(await qu('SELECT b FROM table1 UNION SELECT id FROM table2;')); // UINON ALL : DISTINCT b

	// SQL Server : SELECT column_name(s) INTO newtable_name FROM table_name
	await qu('CREATE TABLE table3 AS SELECT i, b, f FROM table1 WHERE b = 2;'); // create
	await qu('INSERT INTO table3 (i, b, f) SELECT i, b, f FROM table1 WHERE b <> 2;');
	console.log(await qu('SELECT i, b, f FROM table3')); // slow
	await qu('DROP TABLE table3');
	console.log(await qu('SELECT i FROM (SELECT i, b, f FROM table1 WHERE i > 0) AS table3  WHERE b > 0')); // temporary

	console.log('VIEW');
	// CREATE [OR REPLACE] [ALGORITHM = {UNDEFINED | MERGE | TEMPTABLE}] VIEW view_name[(column_list)] AS select_statement [WITH [CASCADED | LOCAL] CHECK OPTION]
	// CREATE OR REPLACE VIEW view_name AS select_statement // SQL Server: 
	await qu('CREATE VIEW view1 AS SELECT i, b FROM table1 LIMIT 2'); // LIMIT count // LIMIT offset, count
	console.log(await qu('SELECT * FROM view1;'));
	await qu('DROP VIEW view1');
	await qu('INSERT INTO table4 (name) SELECT name FROM table2;');
	console.log(await qu('SELECT * FROM table4;'));
	// SELECT ... INTO OUTFILE

	console.log(await qu('SELECT NOW() AS now, CURDATE() AS curdate, CURTIME() AS curtime, DATE(NOW()) AS date, EXTRACT(DAY FROM NOW()) AS EXTRACT, DATE_ADD(now(), INTERVAL 1 DAY) AS date_add1, DATE_SUB(NOW(), INTERVAL 1 DAY) AS date_sub, DATEDIFF(CURDATE(), CURDATE()) AS datediff;')); // EXTRACT(uint FROM date) // MICROSECOND SECOND MINUTE HOUR DAY WEEK MONTH QUARTER YEAR SECOND_MICROSECOND MINUTE_MICROSECOND MINTUE_SECOND HOUR_MICROSWCOND HOUR_SECOND HOUR_MINUTE DAY_MICROSECOND DAY_SECOND DAY_HOUR DAY_MONTH
	// DATE_FORMAT(NOW(), "%Y-%m-%d")
	// SQL Server: GETDATE() | DATEPART(datepart, date) datepart: yy, yyyy qq, q mm, m dy, d wk, ww dw w hh mi, n ss, s ms mcs ns | DATEADD(datepart, number, date) dateadd(day, 5, date) // DATEDIFF(datepart, startdate, enddate) | CONVERT(data_type(length),expression,style) CONVERT(VARCHAR(11),GETDATE(),106)
	// DATE: YYYY-MM-DD DATETIME: YYYY-MM-DD HH:MM:SS TIMESTAMP: YYYY-MM-DD HH:MM:SS YEAR: YYYY|YY
	// SQL Server: SMALLDATETIME: YYY-MM-DD HH:MM:SS TIMESTAMP: number
	
	console.log(await qu('SELECT AVG(i) AS avg, COUNT(i) AS count, MAX(i) AS max, MIN(i) AS min, SUM(i) AS sum FROM table1;')); // FIRST():  LIMT 1
	console.log(await qu('SELECT UCASE(name) AS ucase, LCASE(name) AS lcase, LENGTH(name) AS length, MID(name, 1, 1) AS mid11, SUBSTRING(name, 1, 1) AS substring01 FROM table4')); // MID(column_name[,start,length]) start > 0 // SubString(column_name，1，end)  // LENGTH(column_name)  LEN(column_name)
	// ROUND FORMAT
	console.log(await qu('SELECT i, SUM(b) AS sumb, COUNT(i) AS count FROM table1 GROUP BY i HAVING SUM(b) > 2;')); 
	// SELECT xx FROM A JOIN B ON xx GROUP 
	
	console.log(await qu('SET @v = 0;SELECT @v AS v, @i := 5 AS ie, @i AS i;'));  // select column_name into v
	// SET @b = b'1100001' // SET @v = CAST(b'1100001' AS UNSIGNED)
	
	// CREATE USER 'username'@'localhost' IDENTIFIED BY 'password';
	// GRANT priv_type ON database.table TO user [IDENTIFIED BY [PASSWORD] 'password'];
	// priv_type: SELECT|INSERT|DELETE|UPDATE|PEFERENCES|CREATE|ALTER|SHOW VIEW|CREATETOUTIME|ALTER ROUTIME|INDEX|DROP|CREATE TEMPORARY TABLES|CREATE VIEW|EXECUTE ROUTINE|LOCK TABLES | SHOW USER | SHOW DATABASES | ALL| ALL PRIVILEGES | SUPER 
	// database.table db.* *.*
	// flush privileges;
	// RENAME USER 'user'@'localhost' TO 'test'@'localhost';
	// DROP|DELETE USER user_name;
	// SELECT * FROM mysql.user; // priv
	// REVOK prvi_type [(column_list)]... ON database.table FROM user [, user]...
	// REVOKE ALL PRIVILEGES, GRANT OPTION FROM user [, user]...
	// SET PASSWORD FOR 'user'@'localhost' = PASSWORD("123");
	// GRANT USAGE ON *.* TO 'user'@'localhost' IDENTIFIED BY '123';
	// shell:
	// mysqldump -uroot -p123 --host=localhost --port=3306 --all-databases > all.sql
	// --datavases db1
	// --no-data
	// --no-create-info
	// --tables db1 table1
	// mysql -uroot -p123 [db_name] < all.sql // mysql -uroot -p123 db1 > db1.sql
	// mysql> source all.sql

	// IF a=0 \nELSE\n END
	// DML: INSERT DELETE UPDATE, DDL: CREATE INSERT UPDATE 
	// After (FOR) | INSTEAD OF (LIMIT 1)
	// virtual table: new(insert | update) old(update | delete) // non mysql : inserted deleted
	// CREATE TRIGGER trigger_name {AFTER | BEFORE | INSTEAD OF} {[INSERT] | [UPDATE] | [DELETE]} FOR EACH ROW sql_statement // old.column_name | new.column_name
	// DML non mysql: CREATE TRIGGER trigger_name ON {table_name | view_name} {FOR | AFTER | INSTEAD OF} {[INSERT] | [UPDATE] | [DELETE]} AS sql_statement
	// DDL non mysql: CREATE TRIGGER trigger_name ON {ALL SERVER | DATABASE} {FOR | AFTER} {event_type|event_group} AS sql_statement
	// CREATE TRIGGER tirgger_create_database ON ALL SERVER AFTER CREATE_DATABASE AS PRINT "CREATE DATABASE"
	// await query('SELECT * FROM information_schema.triggers WHERE TRIGGER_NAME="trigger_table4_delete";', save);
	await query(`
		CREATE OR REPLACE TRIGGER trigger_table4_delete
		AFTER DELETE
		ON table4
		FOR EACH ROW
		BEGIN
			DELETE FROM table2 WHERE table2.name=old.name;
		END`, save); // BEGIN sql_statement; end
	// await query('CREATE OR REPLACE TRIGGER trigger_table10_delete INSTEAD OF DELETE ON table10 FOR EACH ROW UPDATE SET status = "DELETE" table10 WHERE table10.name = old.name;', save);
	// await query('DELETE FROM table4 WHERE name="name";', save); // && DELETE FROM table2
	await query('DROP TRIGGER trigger_table4_delete;', save);
	// process

	await query('DROP TABLE IF EXISTS table5;', save);
	await query('CREATE TABLE table5(i INT AUTO_INCREMENT, e ENUM ("A", "B", "C", "D") NOT NULL DEFAULT "A", s SET ("A", "B", "C", "D") NOT NULL DEFAULT "A", b BLOB NOT NULL, INDEX table5_index_name (i) ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;', save); // CHAR VARCHAR TINYBLOB TINYTEXT BLOB TEXT MEDIUMBLOB MEDIUMTEXT LONGBLOB LONGTEXT
	// INDEX index_name (column_name [ASC|DESC])
	console.log(await qu('SELECT i, SUM(b) AS sumb, COUNT(i) AS count FROM table1 GROUP BY i WITH ROLLUP;')); // MySQL 
	await qu('INSERT INTO table5 (e, s, b) VALUES (?, ?, ?);', ["A", "A,B", Buffer.from("abc").toString("binary")]);
	// SELECT MD5(b) AS md5 FROM table5;
	console.log(await qu('SELECT i, e, s, b FROM table5;'));
	// +-*/% // &|^!<<>>
	// WHERE name REGEXPR "^nonee$" // . [A-Z] [^A-Z] p1|p2 * + {n} {n, m}

	pool.getConnection(function(err, connection) {
		if(err) return pm(err);
		connection.beginTransaction(function(err) {
			if(err) {
				connection.release();
				return pm(err);
			}
			let rollback = function(e) {
				connection.rollback(function(err) {
					connection.release();
					if(err) return pm([e, err]);
					pm(e);
				});
			};
			let commit = function() {
				connection.commit(function(err) {
					connection.release();
					if(err) return pm(err);
					pm(null);
				});
			}
			let cb2 = function(err, result, fields) {
				if(err) return rollback(err);
				commit();
			};
			let cb1 = function(err, result, fields) {
				if(err) return rollback(err);
				connection.query('DELTE FROM table2 WHERE column_name = "name";', cb2); // error
			};
			connection.query('DELETE FROM table4 WHERE name = "name";', cb1);
		});
	});
	console.log(await pm() instanceof Error, await qu('SELECT * FROM table4 WHERE name = "name";'));

	console.log(await qu('SELECT name, CONCAT(name, "-") AS concat_, MID(name, 1, LENGTH(name)) AS mid_, REPLACE("abc name none [str]", name, "str") AS replace_ FROM table2 LIMIT 1;')); // ltrim(name) rtrim(name) trim(name) // CHAR_LENGTH(name) CHARACTER_LENGTH // CONCAT_WS("_delimiter_", s1, s2) s1_delimiter_s2 // FILED(s, s1, s2, s3): 2 (s = s2) FIND_IN_SET(s, set) // FORMAT(x, n): xxx,xxx.nn INSERT(s, x, len, s2) :[delete(x, len) insert(x, s2)] // LOCATE(s1, s) LOCATE("str", "[str]"): 2  // LCASE(s) // LEFT(s, n) MID(s, 1, n) RIGHT(s, n) // LOWER(s) UPPER(s) // REPEAT(s, n) // REPALCE(s, s1, s2) // REVERSE(s)

	let result = await transaction(pool, [
		[`
			CREATE OR REPLACE PROCEDURE procedure1 (IN in_arg INT, OUT out_arg VARCHAR(30), INOUT inout_arg INT)
			BEGIN
				DECLARE a INT DEFAULT 1;
				IF a < 1 THEN
					SET a = a + 1;
				ELSEIF a = 2 THEN
					SET a = 1;
				ELSE
					SET a = 1;
				END IF;
				set inout_arg=inout_arg+a;
				SELECT name INTO out_arg FROM table2 WHERE id=in_arg;
			END
		`],
		/*
CASE i
	WITH 20 THEN SET a = 10;
	WITH 10 THEN SET a = 5;
	ELSE SET a = 0;
END CASE;
CASE 
	WITH i = 20 THEN SET a = 10;
	ELSE SET a = 0;
END CASE;
DECLARE g INT DEFAULT 0;
loop_label:LOOP
	LEAVE loop_label; -- -- break;
	ITERATE loop_label; -- -- continue;
END LOOP loop_label;
		 */
		/*
		 // my.cnf: [mysqld] event_scheduler = 0
DELIMITER ;;
CREATE EVENT [IF NOT EXISTS] event_name
ON SCHEDULE schedule
[ON COMPLETION [NOT] PRESERVE]
[ENABLE | DISABLE]
[COMMENT 'comment']
DO sql_statement -- DO BEGIN sql_statement; END ;;
DELIMITER ;
schedule: AT TIMESTAMP [EVERY n [SECOND | MINUTE | HOUR ...] [STARTS DATE] [ENDS DATE] -- TIMESTAMP: ONCE
DROP EVENT [IF EXISTS] event_name;
ALTER EVENT event_name DISABLE; // ENABLE
schedule: EVERY 1 SECOND | EVERY 1 MONTH STRATS CURDATE() 
		 */
		[`
			CREATE FUNCTION function1 ()
			RETURNS VARCHAR(30)
			COMMENT 'FUNCTION1'
			BEGIN
				DECLARE done INT DEFAULT 0;
				DECLARE i INT DEFAULT 0;
				DECLARE sum INT DEFAULT 0;
				DECLARE str VARCHAR(30);
				DECLARE cur CURSOR FOR SELECT name, id FROM table2;
				DECLARE continue handler FOR SQLSTATE '02000' SET done = 1;
				OPEN cur;
				WHILE done = 0 DO
					SET sum = sum+i;
					FETCH cur INTO str, i;
				END WHILE;
				CLOSE cur;
				REPEAT
					SET str = FORMAT(sum, 0);
				UNTIL done
				END REPEAT;
				RETURN (str);
			END
		`],
		[`
			SET @numpp=1;
			CALL procedure1(1, @out1, @numpp);
			SELECT @out1 AS result, @numpp AS pp, function1() AS n;
		`],
		['DROP FUNCTION IF EXISTS function1;']
		,['SELECT SUM(id) FROM table2']
		// ['DROP PROCEDURE IF EXISTS procedure1;'] // DROP PROCEDURE [ IF EXISTS ] procedure_name
	]);
	// const _sql = sql.toString().replace(/DELIMITER ;?;/gm, '').replace(/;;/gm, ';')
	if(result instanceof Error)
		console.log(result);
	else
		console.dir(JSON.stringify(result));
	// LOCK TABLE table_name AS alias_name READ;
	// LOCK TABLE table_name [AS alias_name] [LOW_PRIORITY] READ|WRITE;
	// UNLOCK TABLES;
	// SELECT * FROM table1 WHERE i = 1 LOCK IN SHARE MODE;
	// MODE: S X IS IX // wait: W RW (S REQUIRE IS) ...
	// UNCLOCK : COMMIT
	// SELECT * FROM table1 WHERE i = 1 FOR UPADTE;
	// BEGIN; SQL_STATEMENT ( failed: ROLLBACK); COMMIT; // BEGIN; SQL_STATEMENT; ROLLBACK
	// START TRANSACTION;
	/*
SAVEPOINT identifier
ROLLBACK [WORK] TO [SAVEPOINT] identifier
RELEASE SAVEPOINT identifier
	*/
	// SET AUTOCOMMIT = 0|1|ON|OFF;
	// SET @session.tx_isolation="READ_COMMITED"; // @global.tx_isolation // Serializable // Reapeatable Read // Read Uncommited
	// SET [SESSION | GLOBAL] TRANSACTION ISOLATION LEVEL {READ UNCOMMITTED | READ COMMITTED | REPEATABLE READ | SERIALIZABLE}
	// CREATE INDEX index_name ON table_name (column_name1 [ASC|DESC], column_name2 [ASC|DESC]);
	// explain sql_statement // select_type SIMPLE | PRIMARY | SUBQUERY | DERIVED | UNION | UNION RESULT // table // type ALL | INDEX - range | ref | eq_ref | const, system | NULL | index_merge // extra
	// SHOW INDEX FROM table_name;
	// CREATE TEMPORARY TABLE table_name(statement)
	// SHOW CREATE TABLE table_name \G;
	// process.exit(0);

	/*
[client_server]
[mysqld]
character-set-server = utf8mb4
init_connect='SET NAMES utf8mb4'
collation-server=utf8mb4_unicode_ci
character-set-client-handshake=FALSE

[client]
default-character-set=utf8mb4

[mysql]
default-character-set=utf8mb4
	 */



	// await query('DROP TABLE table1;', save);
	// await query('DROP TABLE table2;', save);
	//  natural JOIN
	process.exit(0);
})();





