   

/****************************************************/

/* File: tiny.y                                     */

/* The TINY Yacc/Bison specification file           */

/* Compiler Construction: Principles and Practice   */

/* Kenneth C. Louden                                */

/****************************************************/

%{

#define YYPARSER /* distinguishes Yacc output from other code files */



#include "globals.h"

#include "util.h"

#include "scan.h"

#include "parse.h"



#define YYSTYPE TreeNode *

static char * savedName; /* for use in assignments */

static int savedLineNo;  /* ditto */

static TreeNode * savedTree; /* stores syntax tree for later return */

static int yylex(void);

%}



%token ENDFILE IF ELSE PLUS MINUS TIMES OVER LT LTEQ GT GTEQ EQ NEQ ASSIGN SEMI COMMA LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE

%token ID NUM INT RETURN VOID WHILE

%token ERROR Comment_Error

%nonassoc RPAREN

%nonassoc ELSE

%% /* Grammar for TINY */



program         : declaration-list
                { savedTree = $1;} 
                ;
saved           : ID 
                {savedName=copyString(tokenString);}
                ;  
declaration-list: declaration-list declaration
                {
                    YYSTYPE t = $1;

                    if(t !=NULL)
                    {
                        while(t-> sibling != NULL) t=t->sibling;
                        t->sibling = $2;
                        $$ = $1;
                    }
                    else $$ = $2;
                }
                | declaration {$$=$1;}
                ;
declaration     : var-declaration 
                {$$=$1;}
                | fun-declaration 
                {$$=$1;}
                ;
var-declaration : type-specifier saved
                {
                    $$=$1;
                    $$->attr.name=savedName;
                    $$->kind.decl=VarK;
                } SEMI
                {
                    $$=$1;
                }
                | type-specifier saved 
                {
                    $$=$1;
                    $$->attr.name=savedName;
                    $$->kind.decl=VarK;
                }
                LBRACK NUM
                {
                    $$=$1;
                    $$->arrnum=atoi(tokenString);
                } RBRACK SEMI
                {
                    $$=$1;
                }   
                ;
type-specifier  : INT
                {
                    $$=newDeclNode();
                    $$->type=Integer;
                }
                | VOID
                {
                    $$=newDeclNode();
                    $$->type=Void;
                }
                ;
fun-declaration : type-specifier saved
                {
                    $$=$1;
                    $$->attr.name=savedName;
                    $$->kind.decl=FuncK;
                }
                LPAREN params RPAREN compound-stmt
                {
                    $$=$1;
                    $$->child[0]=$5;
                    $$->child[1]=$7;
                }
                ;
params          : param-list
                {
                    $$=$1;
                }
                | VOID
                {
                    $$=newDeclNode();
                    $$->kind.decl=ParamK;
                    $$->attr.name=NULL;
                }
                ;
param-list      : param-list COMMA param
                {
                    YYSTYPE t=$1;
                    if(t !=NULL)
                    {
                        while(t-> sibling != NULL) t=t->sibling;
                        t->sibling = $3;
                        $$ = $1;
                    }
                    else
                    {
                        $$=$3;
                    }
                }
                | param
                {
                    $$=$1;
                }
                ;
param           : type-specifier saved
                {
                    $$=$1;
                    $$->attr.name=savedName;
                    $$->kind.decl=ParamK;
                }
                | type-specifier saved
                {
                    $$=$1;
                    $$->attr.name=savedName;
                    $$->kind.decl=ParamK;
                }
                LBRACK RBRACK
                {
                    $$=$1;
                }
                ;
compound-stmt   : LBRACE local-declar stmt-list RBRACE
                {
                    $$=newStmtNode(CompK);
                    $$->child[0]=$2;
                    $$->child[1]=$3;
                }
                ;
local-declar    : local-declar var-declaration
                {
                    YYSTYPE t=$1;
                    if(t!=NULL)
                    {
                        while(t->sibling!=NULL) t=t->sibling;
                        t->sibling =$2;
                        $$=$1;
                    }
                    else
                    {
                        $$=$2;
                    }
                }
                | empty
                {
                    $$=$1;
                }
                ;
stmt-list       : stmt-list statement
                {
                    YYSTYPE t=$1;
                    if(t!=NULL)
                    {
                        while(t->sibling!=NULL) t=t->sibling;
                        t->sibling =$2;
                        $$=$1;
                    }
                    else
                    {
                        $$=$2;
                    }
                }
                | empty
                {
                    $$=$1;
                }
                ;
statement       : expression-stmt
                {
                    $$=$1;
                }
                | compound-stmt
                {
                    $$=$1;
                }
                | selection-stmt
                {
                    $$=$1;
                }
                | iteration-stmt
                {
                    $$=$1;
                }
                | return-stmt
                {
                    $$=$1;
                }
                ;
expression-stmt : expression SEMI
                {
                    $$=$1;
                }
                | SEMI
                {
                    $$=NULL;
                }
                ;
selection-stmt  : IF LPAREN expression RPAREN statement
                {
                    $$=newStmtNode(IfK);
                    $$->child[0]=$3;
                    $$->child[1]=$5;
                }
                | IF LPAREN expression RPAREN statement else-stmt
                {
                    $$=newStmtNode(IfK);
                    $$->child[0]=$3;
                    $$->child[1]=$5;
                    $$->child[2]=$6;
                }
                ;
else-stmt       : ELSE statement
                {
                    $$=newStmtNode(ElseK);
                    $$->child[0]=$2;
                }
iteration-stmt  : WHILE LPAREN expression RPAREN statement
                {
                    $$=newStmtNode(IterK);
                    $$->child[0]=$3;
                    $$->child[1]=$5;
                }
                ;
return-stmt     : RETURN SEMI
                {
                    $$=newStmtNode(RetuK);
                }
                | RETURN expression SEMI
                {
                    $$=newStmtNode(RetuK);
                    $$->child[0]=$2;
                }        
                ;
expression      : var ASSIGN expression
                {
                    $$=newExpNode(OpK);
                    $$->attr.op=ASSIGN;
                    $$->child[0]=$1;
                    $$->child[1]=$3;
                }
                | simple-expression
                {
                    $$=$1;
                }
                ;
var             : saved
                {
                    $$=newExpNode(IdK);
                    $$->attr.name=savedName;
                }
                | saved 
                {
                    $$=newExpNode(IdK);
                    $$->attr.name=savedName;
                    $$->arrnum = 1;
                } LBRACK expression RBRACK
                {
                    $$=$2;
                    $$->child[0]=$4;
                }        
                ;
simple-expression: add-expression relop add-expression
                {
                    $$=$2;
                    $$->child[0]=$1;
                    $$->child[1]=$3;
                }
                | add-expression
                {
                    $$=$1;
                }
                ;
relop           : LTEQ
                {
                    $$=newExpNode(OpK);
                    $$->attr.op=LTEQ;
                }
                | LT
                {
                    $$=newExpNode(OpK);
                    $$->attr.op=LT;
                }
                | GT
                {
                    $$=newExpNode(OpK);
                    $$->attr.op=GT;
                }
                | GTEQ
                {
                    $$=newExpNode(OpK);
                    $$->attr.op=GTEQ;
                }
                | EQ
                {
                    $$=newExpNode(OpK);
                    $$->attr.op=EQ;
                }
                | NEQ
                {
                    $$=newExpNode(OpK);
                    $$->attr.op=NEQ;
                }
                ;
add-expression  : add-expression addop term
                {
                    $$=$2;
                    $$->child[0]=$1;
                    $$->child[1]=$3;
                }
                | term
                {
                    $$=$1;
                }
                ;
addop           : PLUS
                {
                    $$=newExpNode(OpK);
                    $$->attr.op=PLUS;
                }
                | MINUS
                {
                    $$=newExpNode(OpK);
                    $$->attr.op= MINUS;
                }
                ;
term            : term mulop factor
                {
                    $$=$2;
                    $$->child[0]=$1;
                    $$->child[1]=$3;
                }
                | factor
                {
                    $$=$1;
                }
                ;
mulop           : TIMES
                {
                    $$=newExpNode(OpK);
                    $$->attr.op=TIMES;
                }
                | OVER
                {
                    $$=newExpNode(OpK);
                    $$->attr.op=OVER;
                }
                ;
factor          : LPAREN expression RPAREN
                {
                    $$=$2;
                }
                | var
                {
                    $$=$1;
                }
                | call
                {
                    $$=$1;
                }
                | NUM
                {
                    $$=newExpNode(ConstK);
                    $$->attr.val = atoi(tokenString);
                }
                ;
call            : saved
                {
                    $$=newExpNode(CaK);
                    $$->attr.name =savedName;
                }
                LPAREN args RPAREN
                {
                    $$=$2;
                    $$->child[0]=$4;
                }
                ;
args            : arg-list
                {
                    $$=$1;
                }
                | empty
                {
                    $$=$1;
                }
                ;
arg-list        : arg-list COMMA expression
                {
                    YYSTYPE t=$1;
                    if(t!=NULL)
                    {
                        while(t->sibling!=NULL) t=t->sibling;
                        t->sibling =$3;
                        $$=$1;
                    }
                    else
                    {
                        $$=$3;
                    }
                }
                | expression
                {
                    $$=$1;
                }
                ;
empty           : {$$=NULL;}            


%%



int yyerror(char * message)

{ fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);

  fprintf(listing,"Current token: ");

  printToken(yychar,tokenString);

  Error = TRUE;

  return 0;

}



/* yylex calls getToken to make Yacc/Bison output

 * compatible with ealier versions of the TINY scanner

 */

static int yylex(void)
{
    int t = getToken();
    if(t == ENDFILE) return 0;
    else return t; 
}

TreeNode * parse(void)

{ yyparse();

  return savedTree;

}