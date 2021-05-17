{注释：程序名}
program test;

var
    a : integer;
    b : boolean;

procedure p1;

begin
    writeln('p1: Hello word!');
end;

begin
    writeln('Hello word!');

    a := 2;

    if (a = 1) then
        writeln('input 1')
    else if (a <= 3 and a >= 0) then
        begin
            writeln('input num belong [0, 3]');
            writeln('compound');
        end
    else
        writeln('input else');

    while (a >= 0) do
        begin
            writeln(a);
            a := a - 1;
        end;


end.
