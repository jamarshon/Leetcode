javascript:(function(){function h(d){d=d.replace(/\[/g,"{");return d=d.replace(/]/g,"}")}function l(d){var a=$("<textarea>");$("body").append(a);a.val(d).select();document.execCommand("copy");a.remove()}var k=!0,g=function(a){console.assert(a);k&=a},c=$(".question-content").find(".question-description__3U1T");0===c.length&&(c=$(".question-content"));var b=c.text().trim().split("\n");g(0<c.text().length);var e=[];c=[];for(var a=0;a<b.length;a++){var f=b[a];if("Input:"===f.substr(0,6)){f=f.substr(6);for(0<f.length&& e.push(f);++a<b.length&&"Output:"!=b[a].substr(0,7);)0!==b[a].length&&e.push(b[a]);f=b[a].substr(7);for(0<f.length&&c.push(f);++a<b.length&&0<b[a].length&&"Explanation:"!=b[a].substr(0,12)&&"Example"!=b[a].substr(0,7);)c.push(b[a])}}g(0<e.length&&e.length===c.length);var m=/(\w+) = ((?:(?!(, (\w+) = )).)*)/g;b=function(a){if(-1!==a[0].indexOf("=")){for(var b=[],d=0;d<a.length;d++)for(var c,e=a[d];c=m.exec(e);)b.push(c[0]);return b}return a};g=a="";e=b(e);c=b(c);"y"===prompt("sublime (y/n)")?(a=e.map(function(a){return h(a)+ ";"}).join("\n"),g=c.map(function(a){return h(a)+";"}).join("\n")):a=e.map(function(a){return(-1!==a.indexOf("=")?a.split("=")[1]:a).trim()}).join("\n");console.log(a);console.log(g);k&&(c=a,0<g.length&&(c+="\n\n"+g),l(c))})();