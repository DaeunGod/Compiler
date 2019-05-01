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
static char * savedFuncName;
static int savedLineNo;  /* ditto */
static char * savedValue; /* for use declaration ADD PRJ2 */
static ExpType savedType; /* for use DataType ADd PRJ2 */
static TokenType savedRelOp;
static TokenType savedAddOp;
static TokenType savedMulOp;
static TreeNode * savedTree; /* stores syntax tree for later return */

int yyerror(char * message);
static int yylex(void);

/*int yyerror(char * message)
{ fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
  fprintf(listing,"Current token: ");
  //printToken(yychar,tokenString);
  Error = TRUE;
  return 0;
}

static int yylex(void)
{ return getToken(); }

TreeNode * parse(void)
{ yyparse();
  return savedTree;
}*/
%}

%token IF ELSE INT VOID WHILE RETURN
%token NUM ID 
%token ASSIGN EQ NOTEQ LTET GTET LT GT PLUS MINUS TIMES OVER LPAREN RPAREN
%token LSQBRACKET RSQBRACKET LBRACE RBRACE STARTCOMMENT SEMI COMMA
%token ERROR 

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
            	 ;
var_declaration  : type_specifier ID { savedName = copyString(tokenStringNew);
				   						savedLineNo = lineno;} 
					SEMI
                 	{ $$ = newDecNode(SimpleK);
                   		$$->attr.name = savedName;
						$$->lineno = savedLineNo;
						$$->expType = $1->expType;
                 	}
            	 | type_specifier ID { savedName = copyString(tokenStringNew);
				 						savedLineNo = lineno; }
					LSQBRACKET NUM { savedValue = copyString(tokenString); }
					RSQBRACKET SEMI
                 	{ $$ = newDecNode(ArrayK);
                   		$$->attr.name = savedName;
						$$->lineno = savedLineNo;
						$$->val = atoi(savedValue);
						$$->expType = $1->expType;
                 	}
            	 ;
type_specifier	 : INT { savedType = INT;  $$ = newDecNode(DummyK); $$->expType = INT;}
				 | VOID { savedType = VOID; $$ = newDecNode(DummyK); $$->expType = VOID;}
				 ;
fun_declaration	 : type_specifier ID { savedFuncName = copyString(tokenStringNew);
				   						savedLineNo = lineno; }
					LPAREN params RPAREN compound_stmt
					{ $$ = newDecNode(FunctionK);
						$$->attr.name = savedFuncName;
						$$->lineno = savedLineNo;
						$$->child[0] = $5;
						$$->child[1] = $7;
						$$->expType = $1->expType;
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
						$$->attr.name = copyString(tokenStringNew);
						$$->lineno = lineno;
						$$->expType = savedType;
					}
				 | type_specifier ID { savedName = copyString(tokenStringNew);
				 						savedLineNo = lineno; }
				 	LSQBRACKET RSQBRACKET
				 	{ $$ = newDecNode(ParamK);
						$$->attr.name = savedName;
						$$->lineno = savedLineNo;
						$$->expType = savedType;
					}
				 ;
compound_stmt	 : LBRACE local_declarations statement_list RBRACE
					{ $$ = newStmtNode(CompoundK);
						$$->child[0] = $2;
						$$->child[1] = $3;
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
					 | %empty { $$ = NULL; }
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
					 | %empty { $$ = NULL; }
					 ;
statement 			 : expression_stmt { $$ = $1; }
					 | compound_stmt { $$ = $1; }
					 | selection_stmt { $$ = $1; }
					 | iteration_stmt { $$ = $1; }
					 | return_stmt { $$ = $1; }
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
							$$->attr.op = ASSIGN;
						}
					 | simple_expression { $$ = $1; }
					 ;
var					 : ID 
						{ $$ = newExpNode(IdK);
							$$->attr.name = copyString(tokenStringNew);
							$$->lineno = lineno; 
						}
					 | ID { savedName = copyString(tokenStringNew);
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
							$$->attr.op = savedRelOp;
						}
					 | additive_expression { $$ = $1; }
					 ;
relop				 : LTET { savedRelOp = LTET; }
					 | LT { savedRelOp = LT; }
					 | GT { savedRelOp = GT; }
					 | GTET { savedRelOp = GTET; }
					 | EQ { savedRelOp = EQ; }
					 | NOTEQ { savedRelOp = NOTEQ; }
					 ;
additive_expression	 : additive_expression addop term
						{ $$ = newExpNode(OpK);
							$$->child[0] = $1;
							$$->child[1] = $3;
							$$->attr.op = savedAddOp;
						}
					 | term { $$ = $1; }
					 ;
addop				 : PLUS { savedAddOp = PLUS; }
					 | MINUS { savedAddOp = MINUS; }
					 ;
term				 : term mulop factor
						{ $$ = newExpNode(OpK);
							$$->child[0] = $1;
							$$->child[1] = $3;
							$$->attr.op = savedMulOp;
						}
					 | factor { $$ = $1; }
					 ;
mulop				 : TIMES { savedMulOp = TIMES; }
					 | OVER { savedMulOp = OVER; }
					 ;
factor				 : LPAREN expression RPAREN { $$ = $2; }
					 | var { $$ = $1; }
					 | call { $$ = $1; }
					 | NUM
                 		{ $$ = newExpNode(ConstK);
							$$->val = atoi(tokenString);
						}
					 ;
call				 : ID { savedName = copyString(tokenStringNew); 
						    savedLineNo = lineno; }
						LPAREN args RPAREN
						{ $$ = newExpNode(FuncCallK);
							$$->attr.name = savedName;
							$$->lineno = savedLineNo;
							$$->child[0] = $4;
						}
					 ;
args				 : arg_list { $$ = $1; }
					 | %empty { $$ = NULL; }
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

