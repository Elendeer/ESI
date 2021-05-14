<!--
 * @Author       : Daniel_Elendeer
 * @Date         : 2020-10-25 15:22:22
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-04-23 13:05:13
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
