var fs = require('fs');

var LCHelper = require('./lc-helper');

LCHelper = new LCHelper();

var files, num_map, max_num;
var output = LCHelper.getFiles();
files = output[0];
num_map = output[1];
max_num = output[2];

var to_do = [];
for(var i = 1; i <= max_num; i++) {
	if(typeof num_map[i] === "undefined") {
		to_do.push(i);
	}
}

files = files.map(x => x.line);

var message = JSON.stringify(files, null, 4);
fs.writeFile('done.txt', message, function(err){
	if(err) throw err;
});

fs.readFile('diag.js', 'utf8', function(err, data) {
  if (err) throw err;
  var paste = 'var d = ' + message + '; \n' + data;
  fs.writeFile('paste.txt', paste, function(err){
    if(err) throw err;
  });
});

var to_do_message = JSON.stringify(to_do, null, 4);
fs.writeFile('to_do.txt', to_do_message, function(err){
	if(err) throw err;
});

console.log(files.length);
