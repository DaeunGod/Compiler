# Project #1
###### code reference: http://www.cs.sjsu.edu/~louden/cmptext
###### 20131612 최대운

### Obejct
Build a lexical analysis phase for the C- language, defined in Appendix A of the textbook.

### Platform and Tools
- Unix or Linux system.
- C and Flex to implement a lexical analyzer.

### RegularExpressions
- digit &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;[0-9]
- number &nbsp; &nbsp; &nbsp;{digit}+
- letter &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; [a-zA-Z]
- identifier &nbsp; &nbsp; {letter}+
- newline &nbsp; &nbsp; &nbsp; \n
- whitespace [ \t]+

### Rules
| rule | token |
|------|-------|
| "if" | IF |
| "else" | ELSE |
| "int" | INT |
| "void" | VOID |
| "while" | WHILE |
| "return | RETURN |
| "==" | EQ |
| "!=" | NOTEQ |
| "<=" | LTET |
| ">=" | GTET |
| "/*" | Start of comments.<br> Consume the text until meet "\*/"|
| "=" | ASSIGN |
| "<" | LT |
| ">" | GT |
| "+" | PLUS |
| "-" | MINUS |
| "*" | TIMES |
| "/" | OVER |
| "(" | LPAREN |
| ")" | RPAREN |
| "{" | LBRACE |
| "}" | RBRACE |
| "[" | LSQBRACKET |
| "]" | RSQBRACKET |
| ";" | SEMI |
| "," | COMMA |
| {number} | NUM |
| {identifier} | ID |
| {newline} | increse line number | 
| {whitespace} | do nothing |

#### TODO
1. Add <strong>yywrap</strong> function in tiny.l file.(It does not exist in skeleton file.)
2. Modify the globals.h, tiny.l, util.c file to add new rule and update print statement.
3. Call <strong>getToken</strong> function in main function while it returns EOF.
