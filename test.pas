{注释：程序名}
PROGRAM test;

{注释：声明变量}
VAR
a : INTEGER;
b : REAL;
{ b : REAL;}

{注释：声明程序}
PROCEDURE P1;
VAR
    a : INTEGER;
BEGIN
    a := 666;
END;

PROCEDURE P2(a, b : REAL; c : INTEGER);
VAR
    {a : INTEGER; duplicat declaration here, will throw a sementic error.}
BEGIN
END;

BEGIN

a := (1 + 2) * 3;
b := a + 0.25;

END.
