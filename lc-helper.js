var fs = require('fs');
var path = require('path');

var LCHelper = function(){};

function getDirectories(srcpath) {
  return fs.readdirSync(srcpath).filter(function(file) {
    return fs.statSync(path.join(srcpath, file)).isDirectory();
  });
}

function getFiles() {
    var directories = this.getDirectories('.');
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
                console.assert(lower == 1 || higher - lower == 9);
                console.assert(lower <= filenum && filenum <= higher);
            }
            memo.push({line: firstline, number: filenum, path: './' + folder + '/' + file});
        });
        return memo;
    }, []);

    files.sort(function(a,b){
        return a.number - b.number;
    });

    return [files, num_map, max_num];
}

LCHelper.prototype.getDirectories = getDirectories;
LCHelper.prototype.getFiles = getFiles;

module.exports = LCHelper;