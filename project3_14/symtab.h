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

typedef struct SymbolInfoRec{
	NodeKind nodekind;
	DeclarationKind decKind;
	int expType;
	int isArray;
	int ArraySize;
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

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(FILE * listing);

/* TODO
 
 */
void st_scopeIn();
void st_scopeOut();
SymbolInfo getSymbolInfo(TreeNode * tree);

#endif
