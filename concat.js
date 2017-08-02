var fs = require('fs');

var LCHelper = require('./lc-helper');

LCHelper = new LCHelper();

var files, num_map, max_num;
var output = LCHelper.getFiles();
files = output[0];

var paths = files.map(x => x.path);

var separator = '\n' + '/'.repeat(100) + '\n';
var content = paths.reduce((memo, path) => {
    var file_content = fs.readFileSync(path, 'utf8');
    return memo + separator + file_content;
}, '');

fs.writeFile('concat.cpp', content, function(err){
    if(err) throw err;
});