{注释：程序名}
program test;

{注释：声明变量}
VAR
a : INTEGER;
b : REAL;
{ b : REAL;}


PROCEDURE P2(a, b : REAL; c : INTEGER);
VAR
    {注释：声明程序}
    PROCEDURE P1;
    VAR
        a : INTEGER;
    BEGIN
        a := 666;
    END;
BEGIN
    P1();
END;

BEGIN

a := (1 + 2) * 3;
b := a div 5;
P2(3.5, 4.5, 5);
{P1(2, 4 + 2);}

END.
