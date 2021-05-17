<!--
 * @Author       : Daniel_Elendeer
 * @Date         : 2020-10-25 15:22:22
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-05-18 00:08:33
 * @Description  :
-->

# Extremely Simple Interpreter

[中文版reademe文档](./readme_cn.md)

## Introduce

ESI is a project that I started for learning compiler theory.

My friend [Chipen](https://github.com/zsiothsu) and
[Ruslan's Blog](https://ruslanspivak.com/lsbasi-part1/) inspire me.

It is still an extremely crude work-in-progress, so I will keep working on it
until the project is more complete before writing more details.

## What's been implement

> Normally you can cheack the `./test.pas` file to see my newest test.
> For all the features mentioned below, most of the corresponding
> grammar checking and semantic analyzing have been implemented.

### Program

A ESI program looks like this:

```note
program <program name>;
[variable declarations]
[procedure declarations] || [function declarations]
begin
    [statement list]
end.
```

### Variable

Variable declarations start with a key word `var`.

```note
var
    <variable name> : <variable type>;
```

These types are supported now:

| Build-in Type |
| --- |
| integer |
| real |
| boolean |
| string |

To use `:=` to assign a variable:

```pascal
a := 1;
```

To use a variable, just do it in a pascal's (or any language's) way.

### Procedure

A ESI procedure is just like a pascal procedure.

```note
procedure <procedure name>[(parameter list)];
[variable declarations]
[procedure declarations] || [function declarations]
begin
    [statement list]
end;
```

A procedure don't have a return value.
Nested declarations are supported too.

Recuresive call of procedrue is available too. When you run
the code below:

```pascal
program test;

procedure p1(n : integer);
begin
    writeln(n);

    if (n > 0) then
        p1(n - 1);
end;

begin
    writeln(p1(3));
end.
```

you will get output:

```note
3
2
1
```

### Function

A ESI funciton is just like a pascal one.

```note
function <function name>[(parameter list)];
[variable declarations]
[procedure declarations] || [function declarations]
begin
    [statement list]
end;
```

A funciton will return a variable, the name of this variable is
the same with funciton name.
Nested declarations are supported too.

Recuresive call of function is available too. When you run
the code below, you will get output `8`.

```pascal
program test;

function fibonacci(n : integer) : integer;
begin
    if (n = 0) then fibonacci := 0
    else if (n = 1) then fibonacci := 1
    else fibonacci := fibonacci(n - 1) + fibonacci(n - 2);
end;

begin
    writeln(fibonacci(6));
end.
```

### I/O

You can use `read`, `write` and `writeln` to input/output values.
For example:

```pascal
write('input a: ');     {print string 'input a :'}
read(a);                {input variable 'a'}
writeln(a);             {print the value of 'a' and open a new line}
write(a + 5);           {print the value of 'a' + 5}
```

Notice, `write` will not print a newline char by default, if you want to
do that, please use `writeln()`.

### If Statement

If statement is used to for flow control.
You can use it like this:

```pascal
if (a = 1) then
    writeln('input 1')
```

For the code above, if `a` equal 1 is true, string `input 1` will be printed
onto the screen.

`if-else if-else` is available too:

```pascal
if (a = 1) then
    writeln('input 1')
else if (a <= 3 and a >= 0) then
    begin
        writeln('input num belong [0, 3]');
        writeln('compound');
    end
else
    writeln('input else');
```

For the code above, if `a` equal 1 is true, string `input 1` will be printed
onto the screen.
If `a <= 3 and a >= 0` is true, string `input num belong [0, 3]` and
`compound` will be printed onto the screen. As you can see, a compound
statement between `begin` and `end` can be nested in if statement.
If they are not true, string `input else` will be printed
onto the screen.

### While Statement

While statement is used to do a loop.
You can use it like this:

```pascal
while (a >= 0) do writeln(a);
```

The program will keep print the value of a if `a >= 0` is true.
You can't stop the while loop above, so we'd better not to write
a program like that.

```pascal
a := 2;
while (a >= 0) do
begin
    writeln(a);
    a := a - 1;
end;
```

If you run the code above, you will get output like:

```note
2
1
0
```

### Others

Those arithmetical operators are available:

| sign name | operator |
| --- | --- |
| positive | `+` |
| negative | `-` |
| multiple | `*` |
| integer division | `div` |
| real division | `/` |
| plus | `+` |
| minus | `-` |

Those relational operators are available:

| sign name | operator |
| --- | --- |
| equal | `=` |
| not equal | `<>` |
| less than | `<` |
| less than or equal to | `<=` |
| greater than | `>` |
| greater than or equal to | `>=` |

Those logical operators are available:

| sign name | operator |
| --- | --- |
| not | `not` |
| and | `and` |
| or | `or` |
| xor | `xor` |

Basically the priority of these operators mentioned above
are decrease progressively. Some of those have the same priority.

## Build

Make sure you get *git* installed.

Open a new folder in a shell you like. In Windows, you can right click in
any folder with *shift* pressed to get PowerShell opened in current folder.

Use `git clone https://github.com/Elendeer/ESI` to clone this repository.

Enter *ESI* folder, run `make`. In windows, you can run `mingw32-make.exe` if
*mingw* is installed in your machine.

Executable file is *./ESI*. In windows, it will have a `exe` postfix.

## Usage

Write down your code in a file.

Open a shell in directory of ESI, run

```shell
./ESI [absolute path of your code file] | [relative path of your code file]
```

Example:

```shell
./ESI ./test.pas
```

You will see output in your shell.

Please use `\` as path separator in windows.

## Licence

MIT.
