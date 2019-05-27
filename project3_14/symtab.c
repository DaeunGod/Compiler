/****************************************************/
/* File: symtab.c                                   */
/* Symbol table implementation for the TINY compiler*/
/* (allows only one symbol table)                   */
/* Symbol table is implemented as a chained         */
/* hash table                                       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"
//#include "globals.h"

/* SIZE is the size of the hash table */
#define SIZE 211

/* SHIFT is the power of two used as multiplier
   in hash function  */
#define SHIFT 4

/* the hash function */
static int hash(char *key)
{
	int temp = 0;
	int i = 0;
	while (key[i] != '\0')
	{
		temp = ((temp << SHIFT) + key[i]) % SIZE;
		++i;
	}
	return temp;
}

/* TODO

 */
//typedef struct SymbolInfoRec{
//	ExpType expType;
//} * SymbolInfo;


/* TODO

 */
typedef struct BlockStructureRec
{
	BucketList hashTable[SIZE];
	struct BlockStructureRec *next;
	struct BlockStructureRec *sibling;
	struct BlockStructureRec *before;
	int depth;
} * BlockStructure;


/* the hash table */
//static BucketList hashTable[SIZE];
static BlockStructure hashTableTop = NULL;
static BlockStructure hashTableCurrent = NULL;

/* TODO
 */
SymbolInfo _createSymbolInfo(){
	SymbolInfo info = (SymbolInfo)malloc(sizeof(struct SymbolInfoRec));
	info->nodekind = StmtK;
	info->isArray = FALSE;
	info->ArraySize = -1;
	info->decKind = DummyK;
	info->expType = Void;
	info->params = NULL;
	return info;
}

/* TODO
 */
SymbolInfo getSymbolInfo(TreeNode *tree)
{
	SymbolInfo info = _createSymbolInfo();
	NodeKind nodekind = tree->nodekind;
	info->nodekind = nodekind;
	if( tree->expType == INT ){
		info->expType = Integer;
	} else if( tree->expType == VOID) {
		info->expType = Void;
	}

	if (nodekind == DeclarationK)
	{
		switch (tree->kind.dec)
		{
		case FunctionK:
			//info->expType = tree->expType;
			info->decKind = FunctionK;
			break;
		case ParamK:
			//info->expType = tree->expType;
			info->decKind = ParamK;
			info->isArray = tree->isArray;
			break;
		case ArrayK:
			//info->expType = tree->expType;
			info->isArray = TRUE;
			info->ArraySize = tree->val;
			info->decKind = ArrayK;
			break;
		case SimpleK:
			//info->expType = tree->expType;
			info->decKind = SimpleK;
			break;
		}
	}
	else if (nodekind == StmtK)
	{
		switch (tree->kind.stmt)
		{
		case IfK:
			break;
		case WhileK:
			break;
		case ReturnK:
			break;
		case AssignK:
			break;
		case CompoundK:
			break;
		}
	}
	else if (nodekind == ExpK)
	{
		switch (tree->kind.exp)
		{
		case OpK:
			break;
		case ConstK:
			break;
		case IdK:
			break;
		case FuncCallK:
			break;
		}
	}

	return info;
}

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert(char *name, int lineno, int loc, SymbolInfo info)
{
	int h = hash(name);
	//BucketList l =  hashTableCurrent->hashTable[h];
	BlockStructure cur = hashTableCurrent;
	BucketList l = NULL;
	int symbolFind = 0;
	while (cur != NULL)
	{
		l = cur->hashTable[h];
		while ((l != NULL))
		{
			if (strcmp(name, l->name) == 0)
			{
				symbolFind = 1;
				break;
			}
			l = l->next;
		}

		if (symbolFind == 1)
		{
			break;
		}
		if( info != NULL && info->nodekind == DeclarationK)
			break;
		else
			cur = cur->before;
	}
	if (l == NULL) {
		if( info == NULL ){
			fprintf(listing, "Hash insert Error\n");
		}
		l = (BucketList)malloc(sizeof(struct BucketListRec));
		l->name = name;
		l->lines = (LineList)malloc(sizeof(struct LineListRec));
		l->lines->lineno = lineno;
		l->lines->next = NULL;
		l->memloc = loc;
		l->info = info;
		l->next = hashTableCurrent->hashTable[h];
		
		hashTableCurrent->hashTable[h] = l;
		
	} else {
		int flag = 0;
		LineList t = l->lines;
		while (t->next != NULL){
			if( t->lineno == lineno ){
				flag = 1;
				break;
			}
			t = t->next;
		}
		if( t->lineno == lineno )
			flag = 1;

		if( flag == 0 ){
			t->next = (LineList)malloc(sizeof(struct LineListRec));
			t->next->lineno = lineno;
			t->next->next = NULL;
		}
	}
} /* st_insert */

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
int st_lookup(char *name, SearchFlag searchFlag)
{
	int h = hash(name);
	BlockStructure cur = hashTableCurrent;
	BucketList l = NULL;
	int symbolFind = 0;
	
	while (cur != NULL)
	{
		l = cur->hashTable[h];
		while ((l != NULL))
		{
			if (strcmp(name, l->name) == 0)
			{
				symbolFind = 1;
				if( hashTableCurrent != cur && searchFlag == LocalNFunc ){		
					if( l->info->decKind != FunctionK ){
						symbolFind = 0;
					}
				}
				break;
			}
			l = l->next;
		}

		if (symbolFind == 1)
		{
			break;
		}
		if( searchFlag == Full || searchFlag == LocalNFunc)
			cur = cur->before;
		else
			break;
	}

	if (l == NULL)
	{
		return -1;
	}
	else
	{
		return l->memloc;
	}
}

/* TODO
 */
int st_lookupLineNo(char *name)
{
	int h = hash(name);
	BlockStructure cur = hashTableCurrent;
	BucketList l = NULL;
	int symbolFind = 0;
	while (cur != NULL)
	{
		l = cur->hashTable[h];
		while ((l != NULL))
		{
			if (strcmp(name, l->name) == 0)
			{
				symbolFind = 1;
				break;
			}
			l = l->next;
		}

		if (symbolFind == 1)
		{
			break;
		}
		cur = cur->before;
	}

	if (l == NULL)
	{
		return -1;
	}
	else
	{
		return l->lines->lineno;
	}
}

/* TODO
 */
SymbolInfo st_lookupInfo(char *name)
{
	int h = hash(name);
	BlockStructure cur = hashTableCurrent;
	BucketList l = NULL;
	int symbolFind = 0;
	while (cur != NULL)
	{
		l = cur->hashTable[h];
		while ((l != NULL))
		{
			if (strcmp(name, l->name) == 0)
			{
				symbolFind = 1;
				break;
			}
			l = l->next;
		}

		if (symbolFind == 1)
		{
			break;
		}
		cur = cur->before;
	}

	if( l == NULL ){
		return NULL;
	} else {
		return l->info;
	}
}

/* TODO
 */
char* _symkindToStr(DeclarationKind DecKind){
	//{SimpleK, ArrayK, FunctionK, ParamK, DummyK} DeclarationKind;
	if(DecKind == SimpleK || DecKind == ArrayK){
		return "Variable";
	} else if(DecKind == FunctionK){
		return "Function";
	} else if(DecKind == ParamK){
		return "Parameter";
	} else {
		return "DecKind Error";
	}
}

/* TODO
 */
char* _expTypeToStr(int expType){
	//{SimpleK, ArrayK, FunctionK, ParamK, DummyK} DeclarationKind;
	if(expType == Integer ){
		return "int";
	} else if(expType == Void){
		return "void";
	} else {
		return "ExpType Error";
	}
}

/* TODO
 */
void _printSymTab(FILE *listing, BlockStructure t)
{
	int showInfoFlag = 0;
	//while (t != NULL)
	if( t != NULL )
	{
		int i = 0;
		for (i = 0; i < SIZE; i++)
		{
			BucketList symbol = t->hashTable[i];
			if( showInfoFlag == 0 ){
					showInfoFlag = 1;
					fprintf(listing, "Scope\tName\tLoc\tV/P/F\t\tArray?\tArraySize\tType\tLineNumbers\n");
					fprintf(listing, "----------------------------------\n");
			}
			if (symbol != NULL)
			{	
				LineList pLine = symbol->lines;
				fprintf(listing, "%d\t", t->depth);
				fprintf(listing, "%s\t", symbol->name);
				fprintf(listing, "%d\t", symbol->memloc);
				fprintf(listing, "%s\t", _symkindToStr(symbol->info->decKind));
				if( symbol->info->isArray ){
					fprintf(listing, "YES\t%d\t\t", symbol->info->ArraySize);
				} else {
					fprintf(listing, "NO\t%s\t\t", "-");
				}
				//fprintf(listing, "%d\t", (symbol->info->expType));
				fprintf(listing, "%s\t", _expTypeToStr(symbol->info->expType));
				
				/* ... */
				while (pLine->next != NULL)
				{
					fprintf(listing, "%d, ", pLine->lineno);
					pLine = pLine->next;
				}
				fprintf(listing, "%d", pLine->lineno);
				printf("\n");
			}
		}
		fprintf(listing, "\n");
		
		_printSymTab(listing, t->next);
		BlockStructure s = t->sibling;
		//while (s != NULL)
		if( s != NULL )
		{
			_printSymTab(listing, s);
			s = s->sibling;
		}
		//t = t->sibling;
	}
}

void testing(){
	int i;
	BlockStructure t = hashTableCurrent;
	printf("testing\n");
	for (i = 0; i < SIZE; i++)
		{
			BucketList symbol = t->hashTable[i];
			if (symbol != NULL)
			{	
				LineList pLine = symbol->lines;
				fprintf(listing, "%d\t", t->depth);
				fprintf(listing, "%s\t", symbol->name);
				fprintf(listing, "%d\t", symbol->memloc);
				fprintf(listing, "%s\t", _symkindToStr(symbol->info->decKind));
				if( symbol->info->isArray ){
					fprintf(listing, "YES\t%d\t\t", symbol->info->ArraySize);
				} else {
					fprintf(listing, "NO\t%s\t\t", "-");
				}
				//fprintf(listing, "%d\t", (symbol->info->expType));
				fprintf(listing, "%s\t", _expTypeToStr(symbol->info->expType));
				
				/* ... */
				while (pLine->next != NULL)
				{
					fprintf(listing, "%d, ", pLine->lineno);
					pLine = pLine->next;
				}
				fprintf(listing, "%d", pLine->lineno);
				printf("\n");
			}
		}
		fprintf(listing, "\n");
}

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(FILE *listing)
{
	int i;
	//fprintf(listing, "Scope Name Loc  V/P/F  Array?  ArraySize Type LineNumbers\n");
	//fprintf(listing, "Scope\tName\tLoc\tV/P/F\t\tArray?\tArraySize\tType\tLineNumbers\n");
	//fprintf(listing, "----------------------------------\n");
	_printSymTab(listing, hashTableTop);
	//while(
	/*for (i=0;i<SIZE;++i)
  { if (hashTable[i] != NULL)
    { BucketList l = hashTable[i];
      while (l != NULL)
      { LineList t = l->lines;
        fprintf(listing,"%-14s ",l->name);
        fprintf(listing,"%-8d  ",l->memloc);
        while (t != NULL)
        { fprintf(listing,"%4d ",t->lineno);
          t = t->next;
        }
        fprintf(listing,"\n");
        l = l->next;
      }
    }
  }*/
} /* printSymTab */

BlockStructure makeHashNode()
{
	int i=0;
	BlockStructure tmp = (BlockStructure)malloc(sizeof(struct BlockStructureRec));
	for(i=0; i<SIZE; i++){
		tmp->hashTable[i] = NULL;
	}
	tmp->next = tmp->before = NULL;
	tmp->sibling = NULL;
	tmp->depth = -1;
	return tmp;
}

void st_scopeIn()
{
	if (hashTableTop == NULL)
	{
		hashTableTop = makeHashNode();
		hashTableTop->depth = 0;
		hashTableCurrent = hashTableTop;
	}
	else
	{
		if (hashTableCurrent->next == NULL)
		{
			BlockStructure tmp = makeHashNode();
			hashTableCurrent->next = tmp;
			tmp->before = hashTableCurrent;
			tmp->depth = hashTableCurrent->depth + 1;
			hashTableCurrent = tmp;
		}
		else
		{
			if (hashTableCurrent->next->sibling == NULL)
			{
				BlockStructure tmp = makeHashNode();
				hashTableCurrent->next->sibling = tmp;
				tmp->before = hashTableCurrent;
				tmp->depth = hashTableCurrent->depth + 1;
				hashTableCurrent = tmp;
			}
			else
			{
				BlockStructure tmp = hashTableCurrent->next->sibling;
				while (tmp->sibling != NULL)
					tmp = tmp->sibling;
				tmp->sibling = makeHashNode();
				tmp->sibling->before = hashTableCurrent;
				tmp->sibling->depth = hashTableCurrent->depth + 1;
				hashTableCurrent = tmp->sibling;
			}
		}
	}
}

/* 0 - next
	1 - sibling
 */
void st_scopeMove(int flag){
	int i=0;
	if( flag == 0 ){
		if(hashTableCurrent->next != NULL){
			hashTableCurrent = hashTableCurrent->next;
		} else {
			printf("move scope next error\n");	
		}
	} else {
		hashTableCurrent = hashTableCurrent->next;
		for(i=0; i<flag; i++){
			if(hashTableCurrent->sibling != NULL ){
				hashTableCurrent = hashTableCurrent->sibling;
			} else {
				printf("move scope sibling error\n");	
				break;
			}
		}
	}
	
}

void st_scopeOut()
{
	hashTableCurrent = hashTableCurrent->before;
}
