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
				   						savedLineNo = lineno; }
					SEMI
                 	{ $$ = newDecNode(SimpleK);
                   		$$->attr.name = savedName;
						$$->lineno = savedLineNo;
						if( $1 == INT )
							$$->expType = Integer;
						else if( $1 == VOID )
							$$->expType = Void;
                 	}
            	 | type_specifier ID { savedName = copyString(tokenString);
				 						savedLineNo = lineno; }
					LSQBRACKET NUM { savedValue = copyString(tokenString); } 
					RSQBRACKET SEMI
                 	{ $$ = newDecNode(ArrayK);
                   		$$->attr.name = savedName;
						$$->lineno = savedLineNo;
						$$->attr.val = atoi(savedValue);
						$$->expType = $1;
                 	}
            	 ;
type_specifier	 : INT { $$ = $1; }
				 | VOID { $$ = $1; }
				 ;
fun_declaration	 : type_specifier ID { savedName = copyString(tokenString);
					   					savedLineNo = lineno; }
					LPAREN params RPAREN compound_stmt
					{ $$ = newDecNode(FunctionK);
						$$->attr.name = savedName;
						$$->lineno = savedLineNo;
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
							while( t->sibling != NULL )
								t = t->sibling;
							t->sibling = $3;
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
				 						savedLineNo = lineno; }
				 	LSQBRACKET RSQBRACKET
				 	{ $$ = newDecNode(ParamK);
						$$->attr.name = savedName;
						$$->lineno = savedLineNo;
						$$->expType = $1;
					}
				 ;
compound_stmt	 : LBRACE local_declarations statement_list RBRACE
					{ YYSTYPE t = $2;
						if( t != NULL ){
							while( t->sibling != NULL )
								t = t->sibling;
							t->sibling = $3;
							$$ = $2; }
						else $$ = $3;
					}
				 ;
local_declarations 	 : local_declarations var_declaration
						{ YYSTYPE t = $1;
							if( t != NULL ){
								while( t->sibling != NULL )
									t = t->sibling;
								t->sibling = $2;
								$$ = $1; }
							else $$ = $2;
						}
					 |
					 ;
statement_list		 : statement_list statement
						{ YYSTYPE t = $1;
							if( t != NULL ){
								while( t->sibling != NULL )
									t = t->sibling;
								t->sibling = $2;
								$$ = $1; }
							else $$ = $2;
						}
					 |
					 ;
statement 			 : expression_stmt { $$ = $1; }
					 | compound_stmt { $$ = $1; }
					 | selection_stmt { $$ = $1; }
					 | iteration_stmt { $$ = $1; }
					 | return_stmt { $$ = $1; }
					 | error { $$ = NULL; }
					 ;
expression_stmt		 : expression SEMI { $$ = $1; }
					 | SEMI { $$ = NULL; }
					 ;
selection_stmt		 : IF LPAREN expression RPAREN statement
						{ $$ = newStmtNode(IfK);
							$$->child[0] = $3;
							$$->child[1] = $5;
						}
					 | IF LPAREN expression RPAREN statement ELSE statement
					 	{ $$ = newStmtNode(IfK);
							$$->child[0] = $3;
							$$->child[1] = $5;
							$$->child[2] = $7;
						}
					 ;
iteration_stmt		 : WHILE LPAREN expression RPAREN statement
						{ $$ = newStmtNode(WhileK);
							$$->child[0] = $3;
							$$->child[1] = $5;
						}
					 ;
return_stmt			 : RETURN SEMI
						{ $$ = newStmtNode(ReturnK);
						}
					 | RETURN expression SEMI
					 	{ $$ = newStmtNode(ReturnK);
							$$->child[0] = $2;
						}
					 ;
expression			 : var ASSIGN expression
						{ $$ = newStmtNode(AssignK);
							$$->child[0] = $1;
							$$->child[1] = $3;
						}
					 | simple_expression { $$ = $1; }
					 ;
var					 : ID 
						{ $$ = newExpNode(IdK);
							$$->attr.name = copyString(tokenString);
							$$->lineno = lineno; 
						}
					 | ID { savedName = copyString(tokenString);
						 	savedLineNo = lineno; }
						LSQBRACKET expression RSQBRACKET
					 	{ $$ = newExpNode(IdK);
							$$->attr.name = savedName;
							$$->lineno = savedLineNo;
							$$->child[0] = $4;
						}
					 ;
simple_expression	 : additive_expression relop additive_expression
						{ $$ = newExpNode(OpK);
							$$->child[0] = $1;
							$$->child[1] = $3;
							$$->attr.op = $2;
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
						{ $$ = newExpNode(OpK);
							$$->child[0] = $1;
							$$->child[1] = $3;
							$$->attr.op = $2;
						}
					 | term { $$ = $1; }
					 ;
addop				 : PLUS { $$ = $1; }
					 | MINUS { $$ = $1; }
					 ;
term				 : term mulop factor
						{ $$ = newExpNode(OpK);
							$$->child[0] = $1;
							$$->child[1] = $3;
							$$->attr.op = $2;
						}
					 | factor { $$ = $1; }
					 ;
mulop				 : TIMES { $$ = $1; }
					 | OVER { $$ = $1; }
					 ;
factor				 : LPAREN expression RPAREN { $$ = $2; }
					 | var { $$ = $1; }
					 | call { $$ = $1; }
					 | NUM
                 		{ $$ = newExpNode(ConstK);
							$$->attr.val = atoi(tokenString);
						}
					 ;
call				 : ID { savedName = copyString(tokenString); 
						    savedLineNo = lineno; }
						LPAREN args RPAREN
						{ $$ = newExpNode(FuncCallK);
							$$->attr.name = savedName;
							$$->lineno = savedLineNo;
							$$->child[0] = $4;
						}
					 ;
args				 : arg_list { $$ = $1; }
					 |
					 ;
arg_list			 : arg_list COMMA expression
						{ YYSTYPE t = $1;
							if( t != NULL ){
								while( t->sibling != NULL )
									t = t->sibling;
								t->sibling = $3;
								$$ = $1;}
							else $$ = $3;
						}
					 | expression { $$ = $1; }
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

