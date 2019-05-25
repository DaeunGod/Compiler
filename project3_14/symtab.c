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

/* the list of line numbers of the source 
 * code in which a variable is referenced
 */
typedef struct LineListRec
{
	int lineno;
	struct LineListRec *next;
} * LineList;

/* TODO

 */
//typedef struct SymbolInfoRec{
//	ExpType expType;
//} * SymbolInfo;

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
SymbolInfo getSymbolInfo(TreeNode *tree)
{
	SymbolInfo info = (SymbolInfo)malloc(sizeof(struct SymbolInfoRec));

	NodeKind nodekind = tree->nodekind;
	info->nodekind = nodekind;
	info->isArray = FALSE;
	if (nodekind == DeclarationK)
	{
		switch (tree->kind.dec)
		{
		case FunctionK:
			info->expType = tree->expType;
			break;
		case ParamK:
			info->expType = tree->expType;
			break;
		case ArrayK:
			info->expType = tree->expType;
			info->isArray = TRUE;
			break;
		case SimpleK:
			info->expType = tree->expType;
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
		cur = cur->before;
	}
	if (l == NULL)
	{
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
		l->next = cur->hashTable[h];
		cur->hashTable[h] = l;
	}
	else
	{
		LineList t = l->lines;
		while (t->next != NULL)
			t = t->next;
		t->next = (LineList)malloc(sizeof(struct LineListRec));
		t->next->lineno = lineno;
		t->next->next = NULL;
	}
	/*while ((l != NULL) && (strcmp(name,l->name) != 0))
    l = l->next;
  if (l == NULL) // variable not yet in table 
  { l = (BucketList) malloc(sizeof(struct BucketListRec));
    l->name = name;
    l->lines = (LineList) malloc(sizeof(struct LineListRec));
    l->lines->lineno = lineno;
    l->memloc = loc;
    l->lines->next = NULL;
    l->next = hashTable[h];
    hashTable[h] = l; }
  else // found in table, so just add line number 
  { LineList t = l->lines;
    while (t->next != NULL) t = t->next;
    t->next = (LineList) malloc(sizeof(struct LineListRec));
    t->next->lineno = lineno;
    t->next->next = NULL;
  }*/
} /* st_insert */

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
int st_lookup(char *name)
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
		return l->memloc;
	}
}

/* TODO
 */
void _printSymTab(BlockStructure t)
{
	while (t != NULL)
	{
		//fprintf(listing, "%s", "Here");
		int i = 0;
		for (i = 0; i < SIZE; i++)
		{
			BucketList symbol = t->hashTable[i];
			if (symbol != NULL)
			{
				LineList pLine = symbol->lines;
				fprintf(listing, "%d", t->depth);
				fprintf(listing, "%s", symbol->name);
				/* ... */
				while (pLine != NULL)
				{
					fprintf(listing, "%d", pLine->lineno);
					pLine = pLine->next;
				}
			}
		}

		_printSymTab(t->next);
		BlockStructure s = t->sibling;
		while (s != NULL)
		{
			_printSymTab(s);
			s = s->sibling;
		}
	}
}

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(FILE *listing)
{
	int i;
	fprintf(listing, "Depth Name  Scope  Loc  V/P/F  Array?  ArraySize Type LineNumbers\n");
	fprintf(listing, "----------------------------------\n");
	_printSymTab(hashTableTop);
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
	BlockStructure tmp = (BlockStructure)malloc(sizeof(struct BlockStructureRec));
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

void st_scopeOut()
{
	hashTableCurrent = hashTableCurrent->before;
}
