/****************************************************/
/* File: symtab.h                                   */
/* Symbol table interface for the TINY compiler     */
/* (allows only one symbol table)                   */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include "globals.h"
#include "tiny.tab.h"

/* the list of line numbers of the source 
 * code in which a variable is referenced
 */
typedef struct LineListRec
{
	int lineno;
	struct LineListRec *next;
} * LineList;

/* The record in the bucket lists for
 * each variable, including name, 
 * assigned memory location, and
 * the list of line numbers in which
 * it appears in the source code
 */
typedef struct BucketListRec
{
	char *name;
	LineList lines;
	int memloc; /* memory location for variable */
	struct BucketListRec *next;
	struct SymbolInfoRec *info;
} * BucketList;

typedef struct ParamInfoRec
{
	ExpType expType;
	char *name;
	struct ParamInfoRec * next;
} * ParamInfo;

typedef struct SymbolInfoRec{
	NodeKind nodekind;
	DeclarationKind decKind;
	int expType;
	int isArray;
	int ArraySize;
	ParamInfo p;
	int retExpType;
} * SymbolInfo;

typedef enum {Full, Local, LocalNFunc} SearchFlag;

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert( char * name, int lineno, int loc, SymbolInfo info );

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
int st_lookup ( char * name, SearchFlag searchFlag );

/* TOOD
 */
int st_lookupLineNo(char *name);

/* TOOD
 */
SymbolInfo st_lookupInfo(char *name);

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(FILE * listing);

void testing();

/* TODO
 
 */
void st_scopeIn();
void st_scopeMove(int flag);
void st_scopeOut();
SymbolInfo getSymbolInfo(TreeNode * tree);
void inssertParamlInfo(SymbolInfo info, char* name, ExpType expType);

#endif
