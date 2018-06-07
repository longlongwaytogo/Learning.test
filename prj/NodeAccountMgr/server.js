var http = require('http');
http.createServer(function(request,response) {
    // send http header
    // http status:200:ok
    // content type: text/plain
    response.writeHead(200,{'Content-type':'text/plain'});

    // send info "hello world"
    response.end('Hello World\n');

}).listen(8888);

// print info
console.log('Server runnint a http://127.0.0.1:8888/');

// new sqlite3.Database(filename, [mode], [callback])
var sqlite3 = require('sqlite3');
// var sql3 = new sqlite3.Database('mysqlite3.db', function(e) {
//     if(err) throw err;
// });
//sqlite3.close();

var db = new sqlite3.Database('myinfo.db');                         
db.run("CREATE TABLE IF NOT EXISTS  Users (" +
	"UserID INTEGER PRIMARY KEY," +
	"UserName TEXT,				" +
	"PassWord VARCHAR,			" +
	"Description TEXT,			" +
	"UserEmail TEXT,		    " +
	"UserPhoneNumber NUMERIC,	" +
    "other	 TEXT   			" +
    ")"
);   

db.run("CREATE TABLE IF NOT EXISTS Accounts (" +
    "AccountID NUMERIC PRIMARY KEY,  	                " +			
    "UserID INTEGER	  REFERENCES Users ( UserID ), 	    " +
    "AccountName VARCHAR,  				" +			
    "AccountPwd   VARCHAR,  				" +			
    "AccountEmail TEXT,  				" +			
    "AccountPhoneNumber NUMERIC, 		" +			
    "other TEXT                          " +
    ")"
);
db.close();   
