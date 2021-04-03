<!--
 * @Author       : Daniel_Elendeer
 * @Date         : 2020-10-25 15:22:22
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-04-03 10:40:07
 * @Description  :
-->

# Extremely Simple Interpreter

## Introduce

ESI is a project that I started for learning complier theory.

My friend [Chipen](https://github.com/zsiothsu) and
[Ruslan's Blog](https://ruslanspivak.com/lsbasi-part1/) inspire me.

It is still an extremely crude work-in-progress, so I will keep working on it
until the project is more complete before writing more details.

## What's been implement

> You can cheack the `./test.pas` file to see my newest test, normally it
> shows all features I have implement.

An Example (form `./test.pas`):

```pascal
{ comment supported. }
{ program name : test }
{ key words should be all uppercase. }
PROGRAM test;

{ variable declaration supported. }
VAR
{ have only tow build-in types so far. }
a : INTEGER;
b : REAL;

{ procedure declaration supported. }
PROCEDURE P1;
VAR
    a : INTEGER;
BEGIN
    a := 666;
END;

{ procedure declaration with parameters supported. }
PROCEDURE P2(a, b : REAL; c : INTEGER);
VAR
    a : INTEGER; {duplicat declaration here, will throw a sementic error.}
    {that is, name solution and nested scope supported. }
BEGIN
END;

BEGIN

{ arithmetic expression & assign statement supported. }
a := (1 + 2) * 3;
b := a + 0.25;

END.

{ sementic analyzing is more complete then interpreting so far. }
```

If you remove the duplicate declaration of variable `a` in procedure `P2`
then run `./ESI ./test.pas` in your shell, you will get output like:

```shell
Semantic analyzing ...
ENTER global scope
ENTER scope: P1
scope name: P1
level: 2
enclosing scope: global
===== ===== ===== =====
[a] : Symbol<type : INTEGER, name : a>
----- ----- ----- -----
LEAVE scope: P1
ENTER scope: P2
scope name: P2
level: 2
enclosing scope: global
===== ===== ===== =====
[c] : variable-symbol<type : INTEGER, name : c>
[a] : variable-symbol<type : REAL, name : a>
[b] : variable-symbol<type : REAL, name : b>
----- ----- ----- -----
LEAVE scope: P2
scope name: global
level: 1
enclosing scope: NONE
===== ===== ===== =====
[b] : Symbol<type : REAL, name : b>
[a] : Symbol<type : INTEGER, name : a>
----- ----- ----- -----
LEAVE global scope
scope name: build-in tyep
level: -1
enclosing scope: NONE
===== ===== ===== =====
[REAL] : Symbol<type : REAL, name : REAL>
[INTEGER] : Symbol<type : INTEGER, name : INTEGER>
----- ----- ----- -----
Semantic analyze finish.

Interpreting ...
===== global scope =====
Variable        Value
a       9
b       9.25
===== ===== =====
```

## Build

Make sure you get *git* installed.

Open a new folder in a shell you like. In windows, you can right click in
any folder with *shift* pressed to get PowerShell opened in current folder.

Use `git clone https://github.com/Elendeer/ESI` to clone this repository.

Enter *ESI* folder, run `make`. In windows, you can run `mingw32-make.exe` if
*mingw* is installed in your machine.

Executable file is *./ESI*. In windows, it will have a `exe` postfix.

## Usage

Write down your code in a file.

Open a shell in diretory of ESI, run

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
