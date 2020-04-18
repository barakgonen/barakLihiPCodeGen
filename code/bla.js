var fs = require("fs");  // file system 

var MAXVARS = 512

var BINARY = {
    'add': function (a, b) { return a + b },
    'sub': function (a, b) { return a - b },
    'mul': function (a, b) { return a * b },
    'div': function (a, b) { return a / b },
    'equ': function (a, b) { return a == b },
    'neq': function (a, b) { return a != b },
    'les': function (a, b) { return a < b },
    'grt': function (a, b) { return a > b },
    'leq': function (a, b) { return a <= b },
    'geq': function (a, b) { return a >= b },
    'and': function (a, b) { return Boolean(a) && Boolean(b) },
    'or': function (a, b) { return Boolean(a) || Boolean(b) }
};

var UNARY = {
    'neg': function (a) { return -a; },
    'not': function (a) { return !Boolean(a); }
};

var JUMPS = {
    'fjp': function (stack, pc, addr) {
        return Boolean(stack.pop()) ? pc + 1 : addr;
    },
    'ujp': function (stack, pc, addr) { return addr; },
    'ixj': function (stack, pc, addr) { return stack.pop() + addr; }
};

var IGNORE = { 'chk': null, 'pass': null };

function split(s, sep) {
    return s.split(sep).map(function (e) { return e.trim(); });
}

function str2val(s) {
    if (s == 'true')
        return 1;
    else if (s == 'false')
        return 0;
    return s.indexOf('.') >= 0 ? parseFloat(s) : parseInt(s);
}

function run(lines) {
    var stack = new Array(MAXVARS);
    var pc = 0;
    var result = "";

    while (pc < lines.length) {
        if (lines[pc].trim() == '') {
            pc += 1;
            continue;
        }

        var words = split(lines[pc], ' ');
        var cmd = words[0];

        if (cmd in JUMPS) {
            var addr = parseInt(words[words.length - 1]);
            pc = JUMPS[cmd](stack, pc, addr);
            continue;
        }
        if (cmd in BINARY) {
            var b = stack.pop();
            var a = stack.pop();
            stack.push(BINARY[cmd](a, b));
        } else if (cmd in UNARY) {
            stack.push(UNARY[cmd](stack.pop()));
        } else if (cmd in IGNORE) {
        } else if (cmd == 'ldc') {
            stack.push(str2val(words[words.length - 1]));
        } else if (cmd == 'ind') {
            stack.push(stack[stack.pop()]);
        } else if (cmd == 'print' || cmd == 'out') {
            result += stack.pop() + '\n';
        } else if (cmd == 'sto') {
            var rval = stack.pop();
            var lval = stack.pop();
            stack[lval] = rval;
        } else if (cmd == 'ixa') {
            var a = stack.pop();
            stack[stack.length - 1] += a * parseInt(words[words.length - 1]);
        } else if (cmd == 'dec') {
            stack[stack.length - 1] -= parseInt(words[words.length - 1]);
        } else if (cmd == 'inc') {
            stack[stack.length - 1] += parseInt(words[words.length - 1]);
        } else if (cmd == 'dpl') {
            stack.push(stack[stack.length - 1]);
        } else {
            throw ("unknown command at line " + pc + ": " + lines[pc]);
        }
        pc += 1;
    }
    return result;
}

function unlabel(lines) {
    var labels = {};

    function removeLabelsLeft(element, index, array) {
        var s = split(element, ':');
        for (var i = 0; i < s.length - 1; i++)
            labels[s[i]] = index.toString();
        return s[s.length - 1];
    }

    function removeLabelsRight(element) {
        var s = split(element, ' ');
        if (s[s.length - 1] in labels)
            s[s.length - 1] = labels[s[s.length - 1]];
        return s.join(' ');
    }

    return lines.map(removeLabelsLeft).map(removeLabelsRight);
}

function parse(code) {
    try {
        splitted_lines = split(code, '\n').map(function (element) {
            return element.toLowerCase().trim();
        });
        splitted_lines = splitted_lines.slice(0, -1);
        lines = unlabel(splitted_lines);
        return run(lines);
    } catch (err) {
        console.log('Error occurred during execution: ' + err);
    }
}

function doit() {
    fs.readFile(".\\output\\sample_number.txt", 'utf8', function (err, data) {
        data = split(data, '\n').map(function (element) {
            return element.toLowerCase().trim();
        });
        data = data.slice(0, -1);
        console.log("Running Sanity for: " + data)
    })
    fs.readFile(".\\output\\generated_pcode.txt", 'utf8', function (err, data) {
        actual_result = parse(data);

        fs.readFile(".\\output\\test_program_output.txt", 'utf8', function (err, expected_result) {
            expected_lines = split(expected_result, '\n').map(function (element) {
                return element.toLowerCase().trim();
            });
            actual_lines = split(actual_result, '\n').map(function (element) {
                return element.toLowerCase().trim();
            });
            has_passed = true;
            expected_lines = expected_lines.slice(0, -1);
            actual_lines = actual_lines.slice(0, -1);
            actual_size = actual_lines.length;
            expected_size = expected_lines.length;
            if (actual_size === expected_size) {
                for (var i = 0; i < actual_lines.length; i++) {
                    actual_data = str2val(actual_lines[i])
                    expected_data = str2val(expected_lines[i])
                    if (Math.abs(actual_data - expected_data) > 0.001 ||
                        (isNaN(actual_data) && !isNaN(expected_data)) ||
                        (!isNaN(actual_data) && isNaN(expected_data))) {
                        console.log("FAILED actual: " + actual_data + " expected: " + expected_data);
                        has_passed = false;
                        break;
                    }
                }
            }
            else {
                has_passed = false;
                console.log("Failed because there is no match with outputs lines size");
            }

            fs.readFile(".\\output\\sample_number.txt", 'utf8', function (err, data) {
                data = split(data, '\n').map(function (element) {
                    return element.toLowerCase().trim();
                });
                data = data.slice(0, -1);
                outPutMessage = "Sanity for: " + data;
                if (!has_passed)
                    console.error("ERROR!!!!!! " + outPutMessage + " has failed");
                else
                    console.log(outPutMessage + " passed Successfully ;)");
            })
        });
    });
}

doit();