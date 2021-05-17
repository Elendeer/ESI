{注释：程序名}
program test;

var
    a : integer;

function fibonacci(n : integer) : integer;
begin
    if (n = 0) then fibonacci := 0
    else if (n = 1) then fibonacci := 1
    else fibonacci := fibonacci(n - 1) + fibonacci(n - 2);
end;

procedure p1(n : integer);
begin
    writeln(n);

    if (n > 0) then
        p1(n - 1);
end;

begin
    writeln(fibonacci(6));
end.
