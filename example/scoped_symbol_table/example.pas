{this example and the picture under this folder shows}
{how scoped symbol tables are formed.}
program example;
var
    a : integer;

procedure proc(c : bool; d : string);
    begin
    end;

function func(a : bool) : real;
    var
        b : real;
    begin
        proc(true, 'test');
        func := b;
    end;

begin
    func(false);
end.