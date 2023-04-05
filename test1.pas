{注释：程序名}
program test1;

var
    a : 'a';{由于lexer没有对类型标识符string和字符串stirng做出token类型的区别，此处会误报语义错误而不是语法错误}

begin
    a := 'abc';
    writeln(anUndefinedSymbol);
end.
