var f1 = function(d) {
function httpGet(theUrl) {
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open( "GET", theUrl, false ); // false for synchronous request
    xmlHttp.send( null );
    return JSON.parse(xmlHttp.responseText);
}

var url = 'https://leetcode.com/api/problems/algorithms/';
var a = httpGet(url);

var b = a.stat_status_pairs;
var main_url = 'https://leetcode.com/problems/'
var parse = function(arr) {
    var res = arr.reduce((memo, x) => {
        var row = {
            id: x.stat.frontend_question_id, 
            name: x.stat.question__title,
            url: main_url + x.stat.question__title_slug + '/'
        };
        memo.push(row);
        return memo;
    }, []);
    res.sort((a,b) => a.id - b.id);
    return res;
};
 
var include_money = false;
var not_completed = [];
var completed = [];
var not_attempted = [];
 
b.forEach(x => {
    var should_continue = x.paid_only && !include_money;
    switch(x.status) {
        case "ac":
            completed.push(x);
            break;
        case "notac":
            if(should_continue) return;
            not_completed.push(x);
            break;
        case null:
            if(should_continue) return;
            not_attempted.push(x);
            break;
       default:
            console.log(x);
            console.assert(false);
            break;
   }
});
 
window.not_completed_p = parse(not_completed);
window.completed_p = parse(completed);
window.not_attempted_p = parse(not_attempted);
 
var diag = `not_completed = ${window.not_completed_p.length},\ncompleted = ${window.completed_p.length},\nnot_attempted = ${window.not_attempted_p.length}`;
console.log(diag);

var c_dict = {};
for(var i = 0; i < window.completed_p.length; i++) c_dict[window.completed_p[i].id] = true;

// var d = [];
var d_dict = {};
d = d.map(x => parseInt(x.slice(0, x.indexOf('.'))));
for(var i = 0; i < d.length; i++) d_dict[d[i]] = true;

console.log("not in website");
for(var k in d_dict) {
    if(typeof c_dict[k] === 'undefined') console.log(k);
}

console.log("not saved");
for(var k in c_dict) {
    if(typeof d_dict[k] === 'undefined') console.log(k);
}
};

f1(d)