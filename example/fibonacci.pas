{ program for testing recursive function }
program fibonacci;

var
    input : integer;

function fibonacci(n : integer) : integer;
begin
    if (n = 0) then fibonacci := 0
    else if (n = 1) then fibonacci := 1
    else fibonacci := fibonacci(n - 1) + fibonacci(n - 2);
end;

begin
    write('please enter a integer: ');
    read(input);

    write('fibonacci(');
    write(input);
    write(') = ');
    writeln(fibonacci(input));
end.
