var fs = require('fs');
var path = require('path');

function getDirectories(srcpath) {
  return fs.readdirSync(srcpath).filter(function(file) {
    return fs.statSync(path.join(srcpath, file)).isDirectory();
  });
}

var directories = getDirectories('.');
var numericFolders = directories.reduce(function(memo, dir) {
	if(dir.match(/[0-9]/g)) memo.push(dir);
	return memo;
}, []);

var files = numericFolders.reduce(function(memo, folder){
	var files = fs.readdirSync(folder);
	files.forEach(function(file){
		if(file.indexOf('.exe') !== -1) return;
		var data = fs.readFileSync(folder + '/' + file, 'utf8');
		var firstline = data.split('\r\n')[1];
		console.assert(firstline.match(/\d/) !== null);
		memo.push(firstline);
	});
	return memo;
}, []);

var num_map = {};
var max_num = 0;
files.sort(function(a,b){
	var num_a = a.match(/[\d]+/);
	var num_b = b.match(/[\d]+/);
	console.assert(num_a !== null && num_b !== null);

	num_a = parseInt(num_a[0]);
	num_b = parseInt(num_b[0]);

	console.assert(!isNaN(num_a) && !isNaN(num_b));
	num_map[num_a] = num_map[num_b] = true;
	max_num = Math.max(Math.max(max_num, num_a), num_b);
	return num_a - num_b;
});

var to_do = [];
for(var i = 1; i <= max_num; i++) {
	if(typeof num_map[i] === "undefined") {
		to_do.push(i);
	}
}

var message = JSON.stringify(files, null, 4);
fs.writeFile('done.txt', message, function(err){
	if(err) throw err;
});

message = JSON.stringify(to_do, null, 4);
fs.writeFile('to_do.txt', message, function(err){
	if(err) throw err;
});

console.log(files.length);
