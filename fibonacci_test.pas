{注释：经典斐波那契数列递归函数测试}
program fibonacciTest;

function fibonacci(n : integer) : integer;
begin
    if (n = 0) then fibonacci := 0
    else if (n = 1) then fibonacci := 1
    else fibonacci := fibonacci(n - 1) + fibonacci(n - 2);
end;

begin
    writeln(fibonacci(6));
end.
