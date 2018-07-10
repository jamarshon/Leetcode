javascript:(function(){
function fix(str) {
    str = str.replace(/\[/g, "{");
    str = str.replace(/]/g, "}");
    return str;
}

function copy(text) {
  var $temp = $("<textarea>");
  $("body").append($temp);
  $temp.val(text).select();
  document.execCommand("copy");
  $temp.remove();
}

var JASSERT = function(bool){ console.assert(bool); }

var el = $('.question-content').find('.question-description__3U1T');
if(el.length === 0) el = $('.question-content');
var question_description = el.text().trim().split("\n");
JASSERT(el.text().length > 0);

var input = "Input:";
var output = "Output:";
var arr = [];
var arr2 = [];
for(var i = 0; i < question_description.length; i++) {
    var s = question_description[i];
    var s1 = s.substr(0, input.length);
    var s2 = s.substr(0, output.length);
    if(s1 == input) {
        arr.push(s.substr(input.length));
        arr2.push(fix(s.substr(input.length)));
    } else if(s2 == output) {
        arr.push(s.substr(output.length));
        arr2.push(fix(s.substr(output.length)));
    }
}

JASSERT(arr.length % 2 == 0);

var str1 = arr.join('\n');
var str2 = arr2.join('\n');
console.log(str1);
console.log(str2);

var message = str1 + '\n\n' + str2;
copy(message);
}())