<!--
 * @Author       : Daniel_Elendeer
 * @Date         : 2020-10-25 15:22:22
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2021-05-14 22:51:49
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

### 其他

可用的算术运算符：

| sign name | operator |
| --- | --- |
| 正号 | + |
| 负号 | - |
| 乘号 | * |
| 整型除号 | div |
| 实型除号 | / |
| 加号 | + |
| 减号 | - |

可用的关系运算符：

| sign name | operator |
| --- | --- |
| 等号 | = |
| 不等号 | <> |
| 小于号 | < |
| 小于等于号 | <= |
| 大于号 | > |
| 大于等于号 | >= |

以上运算符的优先级基本按照提及的顺序递减，部分平级。

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
