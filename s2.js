javascript:(function(){function f(a){a=a.replace(/\[/g,"{");return a=a.replace(/]/g,"}")}var a=$(".question-content").find(".question-description__3U1T");0===a.length&&(a=$(".question-content"));var c=a.text().trim().split("\n");console.assert(0<a.text().length);var d=[];a=[];for(var e=0;e<c.length;e++){var b=c[e],g=b.substr(0,6),h=b.substr(0,7);"Input:"==g?(d.push(b.substr(6)),a.push(f(b.substr(6)))):"Output:"==h&&(d.push(b.substr(7)),a.push(f(b.substr(7))))}console.assert(0==d.length%2);c=d.join("\n");a=a.join("\n"); console.log(c);console.log(a);(function(a){var b=$("<textarea>");$("body").append(b);b.val(a).select();document.execCommand("copy");b.remove()})(c+"\n\n"+a)})();