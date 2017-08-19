// https://leetcode.com/api/problems/algorithms/
var a = {};
var b = a.stat_status_pairs;
 
var parse = function(arr) {
    var res = arr.reduce((memo, x) => {
        var row = {id: x.stat.question_id, name: x.stat.question__title};
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
 
var not_completed_p = parse(not_completed);
var completed_p = parse(completed);
var not_attempted_p = parse(not_attempted);
 
var diag = `not_completed = ${not_completed_p.length},\ncompleted = ${completed_p.length},\nnot_attempted = ${not_attempted_p.length}`;
console.log(diag);