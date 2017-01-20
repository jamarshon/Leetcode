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
		var data = fs.readFileSync(folder + '/' + file, 'utf8')
		memo.push(data.split('\r\n')[1]);
	});
	return memo;
}, []);

 var base = '# leetcode \r\n' +
						'Ongoing solutions to leetcode in C++ \r\n \r\n' +
						'Completed questions: \r\n \r\n';

var message = base + files.join('\r\n \r\n');
fs.writeFile('README.md', message, function(err){
	if(err) throw err;
})