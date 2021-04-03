<!--
 * @Author       : Daniel_Elendeer
 * @Date         : 2020-10-25 15:22:22
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-04-03 11:19:08
 * @Description  :
-->

# Extremely Simple Interpreter | 及其简单的解释器

## 介绍

本项目简称ESI，是我在大一暑假时突发奇想开始着手编写的
简单的解释器项目。

我的朋友[Chipen](https://github.com/zsiothsu) 给我看了大佬
[Ruslan 的博客](https://ruslanspivak.com/lsbasi-part1/)，激发了我的学习兴趣，
非常感谢他，也感谢Ruslan大佬能写出如此优秀的博客，让编译原理生动起来。

本项目目前完全依照Ruslan博客中的内容，只是使用的编程语言并非Python，
而改用C/C++，尝试实现一个可以解释一部分Pascal语言的简单解释器。

项目龟速迭代中，目前依旧很粗糙。

我尝试在开发的过程中留下一些文档或文章，也许并不正规，但求能帮助理解源码。

## 已经实现的功能

> 一般来讲`./test.pas`文件是我最新的测试文件，你可以通过查看它来获知我目前已经
> 实现的所有功能。

现下不妨使用`./test.pas`文件举例：

```pascal
{ 支持注释 }
{ program name 即程序名为 test }
{ 关键字需要全大写 }
PROGRAM test;

{ 支持变量声明 }
VAR
{ 目前只有两个内置类型 }
a : INTEGER;
b : REAL;

{ 支持procedure（过程）声明 }
PROCEDURE P1;
VAR
    a : INTEGER;
BEGIN
    a := 666;
END;

{ 支持带参的procedure声明 }
PROCEDURE P2(a, b : REAL; c : INTEGER);
VAR
    a : INTEGER; {与参数表的a同名，重复声明，将会抛出一个语义错误 }
    {即，支持变量名称解析和嵌套作用域}
BEGIN
END;

BEGIN

{ 支持数学表达式和赋值语句 }
a := (1 + 2) * 3;
b := a + 0.25;

END.

{ 目前，语义分析的部分比解释的部分更完善，因此下文的输出主要是语义分析 }
```

如果你去除重复定义变量`a`的语句，并在shell中运行`./ESI ./test.pas`，
你将会得到如下输出：

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
Semantic analysis finished.

Interpreting ...
===== global scope =====
Variable        Value
a       9
b       9.25
===== ===== =====
```

## 如何构建

确保你安装了`git`。

在shell中打开一个文件夹，使用git命令
`git clone https://github.com/Elendeer/ESI`
将本仓库克隆到本地。
在Windows中，你可以按住shift并右键某个文件夹来在当前文件夹下打开PowerShell。

进入`ESI`文件夹，使用命令`make`来构建项目。在Windows下请使用`mingw32-make.exe`
来构建，当然，需要你安装*mingw*。

可执行文件是`./ESI`，在Windows中会有`exe`后缀。

## Licence

MIT.
