var fs = require('fs');

var LCHelper = require('./lc-helper');

LCHelper = new LCHelper();

var files, num_map, max_num;
var output = LCHelper.getFiles();
files = output[0];

var paths = files.map(x => x.path);

var separator = '\n' + '/'.repeat(100) + '\n';
var lines = 0;
var limit = 1000;
var memo = "";
var file = 0;

for(var i = 0, len = paths.length; i < len; i++) {
    var path = paths[i];
    var file_content = fs.readFileSync(path, 'utf8');
    var num_lines = file_content.split('\n').length;

    if(i == len - 1) {
        memo += separator + file_content;
    }
    if(i == len - 1 || lines + num_lines > limit) {
        fs.writeFile('./concat/' + file + '.cpp', memo, function(err){
            if(err) throw err;
        });
        file++;
        memo = "";
        lines = 0;
    }

    lines += num_lines;
    memo += separator + file_content;
}

