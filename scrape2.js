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

var can_build = true;
var JASSERT = function(bool){ console.assert(bool); can_build &= bool; }

var el = $('.question-content').find('.question-description__3U1T');
if(el.length === 0) el = $('.question-content');
var question_description = el.text().trim().split("\n");
JASSERT(el.text().length > 0);

var input = "Input:";
var output = "Output:";
var explaination = "Explanation:";
var example = "Example";

var input_arr = [];
var output_arr = [];
for(var i = 0; i < question_description.length; i++) {
    var s = question_description[i];
    if(s.substr(0, input.length) === input) {
      // check the first line: Input: xxxx to see if xxxx is empty
      var first_ln = s.substr(input.length);
      if(first_ln.length > 0) input_arr.push(first_ln);

      // keep goint until Output: yyyy
      while(++i < question_description.length && question_description[i].substr(0, output.length) != output) {
        if(question_description[i].length === 0) continue;
        input_arr.push(question_description[i]);
      }

      // see if yyyy is empty and go until empty string, example or explaination
      var first_ln_output = question_description[i].substr(output.length);
      if(first_ln_output.length > 0) output_arr.push(first_ln_output);
      while(++i < question_description.length && 
        question_description[i].length > 0 &&
        question_description[i].substr(0, explaination.length) != explaination &&
        question_description[i].substr(0, example.length) != example
        ) {
        output_arr.push(question_description[i]);
      }
    }
}

JASSERT(input_arr.length > 0 && input_arr.length === output_arr.length);

var re = /(\w+) = ((?:(?!(, (\w+) = )).)*)/g;

// split "x=3,y=4" into ["x=3", "y=4"]
var splitIntoParameters = function(my_arr) {
  var uses_equal = my_arr[0].indexOf("=") !== -1;
  if(uses_equal) {
    var res = [];
    for(var i = 0; i < my_arr.length; i++) {
      var match;
      var s = my_arr[i];
      while (match = re.exec(s)) {
        res.push(match[0]);
      }
    }
    return res;
  } else {
    return my_arr;
  }
};

var input_print = "";
var output_print = "";

var split_input = splitIntoParameters(input_arr);
var split_output = splitIntoParameters(output_arr);

var SUBLIME = prompt("sublime (y/n)");

if(SUBLIME === "y") {
  input_print = split_input.map(x => fix(x) + ";").join("\n");
  output_print = split_output.map(x => fix(x) + ";").join("\n"); 
} else {
  input_print = split_input.map(x => (x.indexOf('=') !== -1 ? x.split('=')[1] : x).trim()).join("\n");
}

console.log(input_print);
console.log(output_print);

if(can_build) {
  var message = input_print;
  if(output_print.length > 0)  message += '\n\n' + output_print;
  copy(message);
}
}())