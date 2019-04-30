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
//#include "parse.h"

#define YYSTYPE TreeNode *
static char * savedName; /* for use in assignments */
static int savedLineNo;  /* ditto */
static char * savedValue; /* for use declaration ADD PRJ2 */
static TreeNode * savedTree; /* stores syntax tree for later return */

int yyerror(char * message);
static int yylex(void);
%}

%token IF ELSE INT VOID WHILE RETURN
%token ID NUM 
%token ASSIGN EQ NOTEQ LTET GTET LT GT PLUS MINUS TIMES OVER LPAREN RPAREN
%token LSQBRACKET RSQBRACKET LBRACE RBRACE STARTCOMMENT SEMI COMMA
%token ERROR ENDFILE 

%% /* Grammar for TINY */

program     	 : declaration_list
                 	 { savedTree = $1;} 
            	 ;
declaration_list : declaration_list declaration
                 	 { YYSTYPE t = $1;
                   	 	if (t != NULL)
                   	 		{ while (t->sibling != NULL)
                        		t = t->sibling;
                     		t->sibling = $2;
                     		$$ = $1; }
                     	else $$ = $2;
                 	}
            	 | declaration  { $$ = $1; }
            	 ;
declaration      : var_declaration { $$ = $1; }
            	 | fun_declaration { $$ = $1; }
            	 | error  { $$ = NULL; }
            	 ;
var_declaration  : type_specifier ID { savedName = copyString(tokenString);
				   						savedLineno = lineno; }
					SEMI
                 	{ $$ = newDecNode(SimpleK);
                   		$$->attr.name = savedName;
						$$->lineno = savedLineno;
						$$->expType = $1;
                 	}
            	 | type_specifier ID { savedName = copyString(tokenString);
				 						savedLineno = lineno; }
					LSQBRACKET NUM { savedValue = copyString(tokenString); } 
					RSQBRACKET SEMI
                 	{ $$ = newDecNode(ArrayK);
                   		$$->attr.name = savedName;
						$$->lineno = savedLineno;
						$$->attr.val = atoi(savedValue);
						$$->expType = $1;
                 	}
            	 ;
type_specifier	 : INT { $$ = Integer; }
				 | VOID { $$ = Void; }
				 ;
fun_declaration	 : type_specifier ID { savedName = copyString(tokenString);
					   					savedLineno = lineno; }
					LPAREN params RPAREN compound_stmt
					{ $$ = newDecNode(FunctionK);
						$$->attr.name = savedName;
						$$->lineno = savedLineno;
						$$->child[0] = $5;
						$$->child[1] = $7;
					}
				 ;
params			 : param_list { $$ = $1; }
				 | VOID { $$ = NULL; }
				 ;
param_list		 : param_list COMMA param
					{ YYSTYPE t = $1;
						if( t != NULL ){
							while( t->sibiling != NULL )
								t = t->sibiling;
							t->sibiling = $3;
							$$ = $1;}
						else $$ = $3;
					}
				 | param { $$ = $1; }
				 ;
param			 : type_specifier ID
					{ $$ = newDecNode(ParamK);
						$$->attr.name = copyString(tokenString);
						$$->lineno = lineno;
						$$->expType = $1;
					}
				 | type_specifier ID { savedName = copyString(tokenString);
				 						savedLineno = lineno; }
				 	LSQBRACKET RSQBRACKET
				 	{ $$ = newDecNode(ParamK);
						$$->attr.name = savedName;
						$$->lineno = savedLineno;
						$$->expType = $1;
					}
				 ;
compound_stmt	 : LBRACE local_declarations statement_list RBRACE
					{ $$ = $1;
						
					}
				 ;
local_declarations 	 : local_declarations var_declaration
						{ YYSTYPE t = $1;
							if( t != NULL ){
								while( t->sibiling != NULL )
									t = t-sibiling;
								t->sibiling = $2;
								$$ = $1; }
							else $$ = $2;
						}
					 %empty
					 ;
statement_list		 : statemet_list statement
						{
						}
					 %empty 
					 ;
statement 			 : expression_stmt
						{
						}
					 | compound_stmt
					 	{
						}
					 | selection_stmt
					 	{
						}
					 | iteration_stmt
					 	{
						}
					 | return_stmt
					 	{
						}
					 ;
expression_stmt		 : expression SEMI
						{
						}
					 | SEMI { $$ = $1; }
					 ;
selection_stmt		 : IF LPAREN expression RPAREN statement
						{
						}
					 | IF LPAREN expression RPAREN statement ELSE statement
					 	{
						}
					 ;
iteration_stmt		 : WHILE LPAREN expression RPAREN statement
						{
						}
					 ;
return_stmt			 : RETURN SEMI
						{
						}
					 | RETURN expression SEMI
					 	{
						}
					 ;
expression			 : var ASSIGN expression
						{
						}
					 | simple_expression
					 	{
						}
					 ;
var					 : ID { $$ = $1; }
					 | ID LSQBRACKET expression RSQBRACKET
					 	{
						}
					 ;
simple_expression	 : additive_expression relop additive_expression
						{
						}
					 | additive_expression { $$ = $1; }
					 ;
relop				 : LTET { $$ = $1; }
					 | LT { $$ = $1; }
					 | GT { $$ = $1; }
					 | GTET { $$ = $1; }
					 | EQ { $$ = $1; }
					 | NOTEQ { $$ = $1; }
					 ;
additive_expression	 : additive_expression addop term
						{
						}
					 | term
					 	{
						}
					 ;
addop				 : PLUS 
						{
						}
					 | MINUS
					 	{
						}
					 ;
term				 : term mulop factor
						{
						}
					 | factor
					 	{
						}
					 ;
mulop				 : TIMES
						{
						}
					 | OVER
					 	{
						}
					 ;
factor				 : LPAREN expression RPAREN
						{
						}
					 | var
					 	{
						}
					 | call
					 	{
						}
					 | NUM
					 	{
						}
					 ;
call				 : ID { savedName = copyString(tokenString); 
						    savedLineNo = lineno; }
						LPAREN args RPAREN
						{
						}
					 ;
args				 : arg_list
						{
						}
					 %empty
					 ;
arg_list			 : arg_list COMMA expression
						{
						}
					 | expression
					 	{
						}
					 ;

assign_stmt : ID { savedName = copyString(tokenString);
                   savedLineNo = lineno; }
              ASSIGN exp
                 { $$ = newStmtNode(AssignK);
                   $$->child[0] = $4;
                   $$->attr.name = savedName;
                   $$->lineno = savedLineNo;
                 }
            ;
exp         : simple_exp LT simple_exp 
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = LT;
                 }
            | simple_exp EQ simple_exp
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = EQ;
                 }
            | simple_exp { $$ = $1; }
            ;
simple_exp  : simple_exp PLUS term 
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = PLUS;
                 }
            | simple_exp MINUS term
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = MINUS;
                 } 
            | term { $$ = $1; }
            ;
term        : term TIMES factor 
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = TIMES;
                 }
            | term OVER factor
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = OVER;
                 }
            | factor { $$ = $1; }
            ;
factor      : LPAREN exp RPAREN
                 { $$ = $2; }
            | NUM
                 { $$ = newExpNode(ConstK);
                   $$->attr.val = atoi(tokenString);
                 }
            | ID { $$ = newExpNode(IdK);
                   $$->attr.name =
                         copyString(tokenString);
                 }
            | error { $$ = NULL; }
            ;

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
{ return getToken(); }

TreeNode * parse(void)
{ yyparse();
  return savedTree;
}

