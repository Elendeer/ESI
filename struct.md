<!--
 * @Author       : Daniel_Elendeer
 * @Date         : 2020-09-28 21:33:18
 * @LastEditors  : Daniel_Elendeer
 * @LastEditTime : 2020-10-25 11:11:25
 * @Description  :
-->

# 结构

## 主要结构类

### Token符号类

> 注：此处借用语言学翻译把Token翻译为符号，个人觉得差强人意，因此下文不译。

**描述**：把输入的每一个字符视为一个Token，创建一个Token对象以描述其特点。

**成员变量**：Token类型；Token值；Token名字符串（方便输出）。

```cpp
class Token {
private:
    TokenType m_type;
    int m_value;
    string m_strVal;

public:
    Token();
    Token(TokenType type, int value);
    Token(TokenType type, string value);
    Token(const Token &obj) = default;

    string str_repr();

    TokenType getType() const;
    int getVal() const;
    string getStrVal() const;
};
```

### Lexer词法分析器类

**描述**：将输入分析成Token。

**成员变量**：输入文本；当前分析位置；当前字符。

```cpp
class Lexer {
private:
    string m_text;
    int m_pos; // index of m_text
    // Token m_current_token;
    char m_current_char;

    Token id();

public:
    Lexer(string text);
    Lexer(const Lexer &) = default;

    void error();

    char peek();
    void advance();
    void skip_whitespace();
    int interger();

    Token get_next_token();
    // void eat(TokenType token_type);
    // int term();
    // int expr();
};
```

### Parser语法分析器类

**描述**：将词法分析的结果依照设计好的上下文无关语法分析成抽象语法树。

**成员变量**：一个词法分析器；当前分析到的Token。


```cpp
class Parser {
    private:
        Lexer m_lexer;
        Token m_current_token;

    public:
        Parser(Lexer lexer);
        Parser(const Parser&) = default;

        void error();

        void eat(TokenType token_type);

        // non-terminals

        AST* factor();
        AST* term();
        AST* expr();

        AST* program();
        AST* compound_statement();
        std::vector<AST*> statement_list();
        AST* statement();
        AST* assignment_statement();
        AST* variable();
        AST* empty();


        AST* parse();
};
```

### interpreter解释器类

> 注：采用了访问者设计模式，解释器是一个节点访问器。

**描述**：访问语法解析器生成的抽象语法树，将抽象语法树解释成可运行的cpp代码。

**成员变量**：一个语法解析器；一个全局变量列表。

```cpp
// As a abstract base class
class NodeVisitor {
protected:
    virtual void generic_visit(AST *node) = 0;

public:
    virtual int visit(AST *node) = 0;
};

// interpreter is a node-visitor
class Interpreter : public NodeVisitor {
private:
    Parser m_parser;
    std::map<std::string, int> m_GLOBAL_SCOPE;

    int visit_UnaryOp(AST *node);
    int visit_BinOp(AST *node);
    int visit_Num(AST *node);

    void visit_Compound(AST *node);
    void visit_NoOp(AST *node);
    void visit_Assign(AST *node);
    int visit_Var(AST *node);

    virtual void generic_visit(AST *node);

public:
    Interpreter(Parser parser);

    virtual int visit(AST *node);

    int interpret();
};

```

---

## 过程相关

### AST抽象语法树类

描述：抽象语法树的节点类
