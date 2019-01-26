javascript:(function(){

// https://closure-compiler.appspot.com/home
var LINE_LENGTH = 80;
var can_build = true;
var JASSERT = function(bool){ console.assert(bool); can_build &= bool; }

var get = function(name) {
    var e = document.getElementsByClassName(name);
    JASSERT(e.length === 1);
    return e[0]
};

var q_name = get('css-1ponsav').textContent;

var file_name = "";
var should_capital = false;
for(var i = 0; i < q_name.length; i++) {
    var code = q_name.charCodeAt(i);

    // not 0-9, A-Z or a-z
    if(!(code > 47 && code < 58) && !(code > 64 && code < 91) && !(code > 96 && code < 123)) {
        should_capital = true;
        continue;
    }

    if(should_capital) {
        file_name += q_name[i].toUpperCase();
        should_capital = false;
    } else {
        file_name += q_name[i];
    }
}

file_name += ".cpp";

var message = "";
var build = function(s) { 
    if(can_build) message += (s === undefined ? "" : s) + "\n"; 
};

var pad = function(n) { return (n < 10 ? "0" : "") + n.toString(); };
var getDate = function() {
    var d = new Date();
    return d.getFullYear() + "-" + pad(d.getMonth() + 1) + "-" + pad(d.getDate());
}

var difficulty = get('css-dcmtd5').textContent.toUpperCase();
JASSERT(difficulty.length > 0);

build(file_name);
build("/*");
build(q_name);

var question_description = get('content__eAC7').textContent.trim().split("\n");
JASSERT(question_description.length > 0);

for(var i = 0; i < question_description.length; i++) {
    // if(question_description[i].trim().length === 0) continue;
    if(question_description[i].length <= LINE_LENGTH) {
        build(question_description[i]);
    } else {
        var words = question_description[i].split(" ");
        var line = "";
        for(var j = 0; j < words.length; j++) {
            if(line.length + words[j].length > LINE_LENGTH) {
                // output previous line
                if(line.length > 0) build(line);
                line = "";
            }
            line += words[j] + " ";
        }

        if(line.length > 0) build(line);
    }
}

build("/*");
build("\tSubmission Date: " + getDate());

var curr_url = window.location.href;
var base = "https://leetcode.com/problems/";
var ind = curr_url.indexOf("/", base.length);
var name = curr_url.substr(base.length, ind - base.length);

var url = "https://leetcode.com/api/submissions/" + name + "/?offset=0&limit=10&lastkey=";

var success = function(x) {
    var submissions = x.submissions_dump;
    JASSERT(submissions.length > 0);
    JASSERT(submissions[0].status_display === "Accepted");

    var run_time = submissions[0].runtime;

    build("\tRuntime: " + run_time);
    build("\tDifficulty: " + difficulty);
    build("*/");

    build("#include <iostream>");
    build("\nusing namespace std;");
    build();

    var soln = get('react-codemirror2').firstChild.CodeMirror.getValue();
    build(soln);

    build();
    build("int main() {");
    build("\treturn 0;");
    build("}");

    function copy(text) {
      console.log(text)
      var temp = document.createElement("textarea");
      document.body.appendChild(temp);
      temp.value = text;
      temp.select();
      document.execCommand("copy");
      temp.remove();
    }

    copy(message);
};

var request = new XMLHttpRequest();
request.open('GET', url, false);

request.onload = function() {
  if (this.status >= 200 && this.status < 400) {
    var data = JSON.parse(this.response);
    success(data);
  } else {
    JASSERT(false);
  }
};

request.onerror = function() { JASSERT(false); };

request.send();
}())
