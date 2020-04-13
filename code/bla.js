var fs = require("fs");  // file system 



var MAXVARS = 512

function divide(a, b) {
    if (a % 1 === 0 && b % 1 === 0) {
        var c = Math.floor(a / b);
        return c;
    }
    return a / b;
}

var BINARY = {
    'add': function (a, b) { return a + b },
    'sub': function (a, b) { return a - b },
    'mul': function (a, b) { return a * b },
    'div': function (a, b) { return divide(a, b) },
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

function val2str(v) {
    if (typeof (v) == 'number')
        return Math.round(v * 10000) / 10000
    return v;
}

function ret(stack, mp) {
    var frame = stack.slice(mp);
    stack.splice(mp, frame.length);
    return frame
}

function run(lines) {
    var stack = new Array();
    var pc = 0;
    var mp = 0;
    var result="";

    base = function (depth, mp) {
        return depth > 0 ? base(depth - 1, stack[mp + 1]) : mp;
    }

    while (pc < lines.length) {
        if (lines[pc].trim() == '') {
            pc += 1;
            continue;
        }

        var words = split(lines[pc], ' ');
        var cmd = words[0];
        var depth = NaN;
        var relativeAddress = NaN;

        if (cmd == 'cupi' || cmd == 'mstf' || cmd == 'lda'
            || cmd == 'lod' || cmd == 'str') {
            depth = parseInt(words[words.length - 2]);
            reladdr = parseInt(words[words.length - 1]);
        }

        if (cmd in JUMPS) {
            var addr = parseInt(words[words.length - 1]);
            pc = JUMPS[cmd](stack, pc, addr);
            continue;
        }
        if (cmd == 'cup') {
            nparams = parseInt(words[words.length - 2]);
            addr = parseInt(words[words.length - 1]);
            mp = stack.length - nparams - 5;
            stack[mp + 4] = pc;
            pc = addr;
            continue;
        }
        if (cmd == 'cupi') {
            dynamic = stack[mp + 2];
            desc = base(depth, dynamic) + reladdr;
            stack[mp + 4] = pc;
            pc = stack[desc];
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
            result+=val2str(stack.pop())+"\n";
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
        } else if (cmd == 'mst') {
            depth = parseInt(words[words.length - 1]);
            stack.push(NaN, base(depth, mp), mp, NaN, NaN);
        } else if (cmd == 'mstf') {
            desc = base(depth, mp) + reladdr;
            stack.push(NaN, stack[desc + 1], mp, NaN, NaN);
        } else if (cmd == 'lda') {
            addr = base(depth, mp) + reladdr;
            stack.push(addr);
        } else if (cmd == 'lod') {
            addr = base(depth, mp) + reladdr;
            stack.push(stack[addr]);
        } else if (cmd == 'movs') {
            src = stack.pop();
            size = parseInt(words[words.length - 1]);
            while (size--)
                stack.push(stack[src++]);
        } else if (cmd == 'ssp') {
            spsize = mp + parseInt(words[words.length - 1]);
            while (stack.length < spsize)
                stack.push(NaN);
        } else if (cmd == 'smp') {
            nparams = parseInt(words[words.length - 1]);
            mp = stack.length - nparams - 5;
        } else if (cmd == 'retp') {
            frame = ret(stack, mp);
            mp = frame[2];
            pc = frame[4];
        } else if (cmd == 'retf') {
            frame = ret(stack, mp);
            stack.push(frame[0]);
            mp = frame[2];
            pc = frame[4];
        } else if (cmd == 'stp') {
            break;
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
                        (!isNaN(actual_data) && isNaN(expected_data)))  {
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
                outPutMessage = "Sanity for sample: " + data;
                if (!has_passed)
                    console.log("ERROR!!!!!! " + outPutMessage + " has failed");
                else
                    console.log(outPutMessage + " passed Successfully ;)");
            })
        });
    });
}

doit();