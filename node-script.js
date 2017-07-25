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

var num_map = {};
var max_num = 0;

var files = numericFolders.reduce(function(memo, folder){
	var files = fs.readdirSync(folder);
	files.forEach(function(file){
		if(file.indexOf('.exe') !== -1) return;
		var data = fs.readFileSync(folder + '/' + file, 'utf8');
		var firstline = data.split('\r\n')[1];

		var filenum = firstline.match(/[\d]+/);
		console.assert(filenum !== null);

		filenum = parseInt(filenum[0]);
		console.assert(!isNaN(filenum));

		num_map[filenum] = true;
		max_num = Math.max(max_num, filenum);

		var foldermatch = folder.match(/([\d]+)-([\d]+)/);
		if(foldermatch !== null) {
			console.assert(foldermatch.length === 3);
			var lower = parseInt(foldermatch[1]);
			var higher = parseInt(foldermatch[2]);
			console.assert(!isNaN(lower) && !isNaN(higher));
			console.assert(lower <= filenum && filenum <= higher);
		}

		memo.push({line: firstline, number: filenum});
	});
	return memo;
}, []);


files.sort(function(a,b){
	return a.number - b.number;
});

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

message = JSON.stringify(to_do, null, 4);
fs.writeFile('to_do.txt', message, function(err){
	if(err) throw err;
});

console.log(files.length);
