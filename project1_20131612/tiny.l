/****************************************************/
/* File: tiny.l                                     */
/* Lex specification for TINY                       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

%{
#include "globals.h"
#include "util.h"
//#include "scan.h"
/* lexeme of identifier or reserved word */
#define MAXTOKENLEN 40
char tokenString[MAXTOKENLEN+1];
%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+

%%

"if"            {return IF;}
"else"          {return ELSE;}
"int"			{return INT;}
"void"			{return VOID;}
"while"			{return WHILE;}
"return"		{return RETURN;}
"=="             {return EQ;}
"!="			{return NOTEQ;}
"<="			{return LTET;}
">="			{return GTET;}
"/*"			{ register int c;
					for(;;){
						while( (c=input()) != '*' && c != EOF){
							if( c == '\n' ){
								lineno++;
							}
						}
						if( c == '*' ){
							while( (c=input()) == '*' );
							if( c == '/' )
								break;
						}

						if( c == '\n' ){
							lineno++;
						}
						if( c == EOF ){
							//error("EOF in comment");
							return ERROR;
							break;
						}
					}
				}
"="            {return ASSIGN;}
"<"             {return LT;}
">"				{return GT;}
"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/"             {return OVER;}
"("             {return LPAREN;}
")"             {return RPAREN;}
"["				{return LSQBRACKET;}
"]"				{return RSQBRACKET;}
"{"				{return LBRACE;}
"}"				{return RBRACE;}
";"             {return SEMI;}
","				{return COMMA;}
{number}        {return NUM;}
{identifier}    {return ID;}
{newline}       {lineno++;}
{whitespace}    {/* skip whitespace */}

%%

TokenType getToken(void)
{ static int firstTime = TRUE;
  TokenType currentToken;
  if (firstTime)
  { firstTime = FALSE;
    lineno++;
    yyin = source;
    yyout = listing;
  }
  currentToken = yylex();
  strncpy(tokenString,yytext,MAXTOKENLEN);
  if (TraceScan) {
    fprintf(listing,"      %d",lineno);
    printToken(currentToken,tokenString);
  }
  return currentToken;
}

int yywrap(){ /* actions for reaching EOF */ }
