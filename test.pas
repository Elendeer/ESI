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
    read(a);

    if (a = 1) then
        writeln('input 1')
    else if (a = 3) then
        writeln('input 3')
    else
        writeln('input else');


end.
