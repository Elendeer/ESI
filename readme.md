<!--
 * @Author       : Daniel_Elendeer
 * @Date         : 2020-10-25 15:22:22
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-03-11 16:47:56
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

You can cheack the `./test.pas` file to see my newest test, normally it
shows all features I have implement.

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
