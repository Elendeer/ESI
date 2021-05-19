<!--
 * @Author       : Daniel_Elendeer
 * @Date         : 2020-10-25 15:22:22
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-05-19 16:29:34
 * @Description  :
-->

# Extremely Simple Interpreter | 及其简单的解释器

## 介绍

本项目简称ESI，是我在大一暑假时突发奇想开始着手编写的
简单的解释器项目。

我的朋友[Chipen](https://github.com/zsiothsu) 给我看了大佬
[Ruslan 的博客](https://ruslanspivak.com/lsbasi-part1/)，激发了我的学习兴趣，
非常感谢他，也感谢Ruslan大佬能写出如此优秀的博客，让编译原理生动起来。

项目龟速迭代中，目前依旧很粗糙。

我尝试在开发的过程中留下一些文档或文章，也许并不正规，但求能帮助理解源码。

## 已经实现的功能

> 一般你可以在根目录的`./test.pas`里找到我最新的测试。
> 下述的功能，大多数对应的语法检查和语义分析已经实现。

### 程序

一个ESI程序一般长这样：

```note
program <program name>;
[variable declarations]
[procedure declarations] || [function declarations]
begin
    [statement list]
end.
```

### 变量

变量定义以一个关键字`var`开始。

```note
var
    <variable name> : <variable type>;
```

这些类型已经支持:

| Build-in Type |
| --- |
| integer |
| real |
| boolean |
| string |

变量的赋值使用`:=`符号：

```pascal
a := 1;
```

变量的使用和pascal或其他语言并无不同。

### 过程

一个ESI过程和pascal过程相似。

```note
procedure <procedure name>[(parameter list)];
[variable declarations]
[procedure declarations] || [function declarations]
begin
    [statement list]
end;
```

过程没有返回值。支持嵌套定义。

支持递归调用过程。当你运行下面的代码：

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

你将得到下列输出：

```note
3
2
1
```

### 函数

一个ESI函数和pascal函数类似。

```note
function <function name>[(parameter list)];
[variable declarations]
[procedure declarations] || [function declarations]
begin
    [statement list]
end;
```

函数将返回一个值，这个返回值在函数内的变量名默认是函数名。
支持嵌套定义。

支持递归函数调用。当你运行下面运算斐波那契数列的代码，你将得到输出：`8`。

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

你可以使用`read`，`write`和`writeln`来输入输出变量和值。
例如：

```pascal
write('input a: ');     {print string 'input a :'}
read(a);                {input variable 'a'}
writeln(a);             {print the value of 'a' and open a new line}
write(a + 5);           {print the value of 'a' + 5}
```

注意，`write` 默认输出后不换行，如果你希望输出后换行，请使用`writeln()`。

### If 语句

If语句用于流程控制。
你可以这样使用：

```pascal
if (a = 1) then
    writeln('input 1')
```

对于上述代码，如果`a`等于1为真，程序将打印字符串`input 1`。

你也可以使用`if-else if-else`。

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

对于上述代码，如果`a`等于1为真，程序将打印字符串`input 1`。
如果`a <= 3`且`a >= 0`为真，程序将打印字符串`input num belong [0, 3]`
和`compound`。你可以看到，你可以使用`begin`和`end`在if语句
的一个分支中包含多条语句。
如果都为假，程序将打印字符串`input else`。

### While 语句

While语句用于循环。你可以按如下使用它：

```pascal
while (a >= 0) do writeln(a);
```

若`a >= 0`成立，上述程序将持续打印变量`a`的值。
这样的循环无法跳出，因此一般循环内有更多的语句。

```pascal
a := 2;
while (a >= 0) do
begin
    writeln(a);
    a := a - 1;
end;
```

若运行上述代码，将得到如下输出：

```note
2
1
0
```

### 其他

可用的算术运算符：

| sign name | operator |
| --- | --- |
| 正号 | `+` |
| 负号 | `-` |
| 乘号 | `*` |
| 整型除号 | `div` |
| 实型除号 | `/` |
| 加号 | `+` |
| 减号 | `-` |

可用的关系运算符：

| sign name | operator |
| --- | --- |
| 等号 | `=` |
| 不等号 | `<>` |
| 小于号 | `<` |
| 小于等于号 | `<=` |
| 大于号 | `>` |
| 大于等于号 | `>=` |

可用的逻辑运算符：

| sign name | operator |
| --- | --- |
| 非 | `not` |
| 与 | `and` |
| 或 | `or` |
| 异或 | `xor` |

以上运算符的优先级基本按照提及的顺序递减，部分平级。

## 如何使用

将代码写入到ASCII文本文件中。

在ESI目录下打开shell并运行：

```shell
./ESI <file path> [--scope] [--stack]
```

若激活`scope`项，语义分析器将在进行语义分析的时候输出符号表。
若激活`stack`项，解释器将在解释代码时输出调用栈。

例:

```shell
./ESI ./test.pas
```

你将会在shell中看到执行结果。

在Windows下，请使用`\`作为地址分隔符。

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
