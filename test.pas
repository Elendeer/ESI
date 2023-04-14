{注释：程序名}
program test;
var
    a : integer;

procedure proc(n : integer);
begin
    while(n < 10) do
        begin
            write(n);
            write(' ');
            n := n + 1;
        end;
    writeln('');
end;

begin
    { write('input a num less then 10: '); }
    { read(a);}
    a := 1;
    proc(a);
end.
