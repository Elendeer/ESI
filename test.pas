{注释：程序名}
program test;

var
    a : integer;
    b : boolean;

function func : integer;
begin
    func := 1;
end;

procedure p1(n : integer);
begin
    writeln(n);

    if (n > 0) then
        p1(n - 1);
end;

begin

    p1(3);
end.
