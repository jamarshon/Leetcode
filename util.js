function fix(arr) {
    var str = JSON.stringify(arr);
    str = str.replace(/\[/g, "{");
    str = str.replace(/]/g, "}");
    return str;
}