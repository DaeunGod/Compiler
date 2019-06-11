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

// /* SIZE is the size of the hash table */
// #define SIZE 211

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
// typedef struct BlockStructureRec
// {
// 	BucketList hashTable[SIZE];
// 	struct BlockStructureRec *next;
// 	int depth;
//     int memhigh;
//     int memlow;
// } * BlockStructure;




/* the hash table */
//static BucketList hashTable[SIZE];
BlockStructure hashTableTop = NULL;
BlockStructure getHashTableTop(){
    return hashTableTop;
}


/* TODO
 */
SymbolInfo _createSymbolInfo(){
	SymbolInfo info = (SymbolInfo)malloc(sizeof(struct SymbolInfoRec));
	info->nodekind = StmtK;
	info->isArray = FALSE;
	info->ArraySize = -1;
	info->decKind = DummyK;
	info->expType = Void;
	info->p = NULL;
	info->retExpType = -1;
	info->memloc = -1;
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
    tree->expType = info->expType;

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
			if(info->isArray)
				info->ArraySize = 0;
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
		case InputCallK:
			info->decKind = FunctionK;
			break;
		case OutputCallK:
			info->decKind = FunctionK;
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
	BlockStructure cur = hashTableTop;
	BucketList l = NULL;
	int symbolFind = 0;
	while (cur != NULL)
	{
		l = cur->hashTable[h];
		while (l != NULL)
		{
			if (strcmp(name, l->name) == 0)
			{
				symbolFind = 1;
				break;
			}
			l = l->next;
		}

		if (symbolFind == 1)
			break;
		
        /*
         * If nodekind is Declaration Kind then search hashTableTop else Full search.
         */ 
        if( info != NULL && info->nodekind == DeclarationK)
			break;
        else
		    cur = cur->next;
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
		l->info->memloc = loc;
		l->next = hashTableTop->hashTable[h];

		hashTableTop->hashTable[h] = l;		
	} else {
		int flag = 0;
		LineList t = l->lines;
        /*
         * The reason why use the "t->next" is to make a new node when flag is 0. 
         */
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
int st_lookup(char *name, SearchFlag flag)
{
	int h = hash(name);
	BlockStructure cur = hashTableTop;
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
                if( hashTableTop != cur && flag == LocalNFunc ){		
					if( l->info->decKind != FunctionK ){
						symbolFind = 0;
					}
				}
				break;
			}
			l = l->next;
		}

		if (symbolFind == 1)
			break;
		
        if( flag != Local )
		    cur = cur->next;
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
	BlockStructure cur = hashTableTop;
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
			break;
		
		cur = cur->next;
	}

	if( l == NULL ){
		return -1;
	} else {
		return l->lines->lineno;
	}
}

/* TODO
 */
SymbolInfo st_lookupInfo(char *name)
{
	int h = hash(name);
	BlockStructure cur = hashTableTop;
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
			break;
		
		cur = cur->next;
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

void testing(){
	int i;
	BlockStructure t = hashTableTop;
	fprintf(listing, "Scope\tName\tLoc\tV/P/F\t\tArray?\tArraySize\tType\tLineNumbers\n");
	fprintf(listing, "----------------------------------\n");
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
	BlockStructure t = hashTableTop;
	fprintf(listing, "Scope\tName\tLoc\tV/P/F\t\tArray?\tArraySize\tType\tLineNumbers\n");
	fprintf(listing, "----------------------------------\n");
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
			if( symbol->info != NULL ){
				if( symbol->info->isArray ){
					fprintf(listing, "YES\t%d\t\t", symbol->info->ArraySize);
				} else {
					fprintf(listing, "NO\t%s\t\t", "-");
				}
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
} /* printSymTab */

BlockStructure makeHashNode()
{
	int i=0;
	BlockStructure tmp = (BlockStructure)malloc(sizeof(struct BlockStructureRec));
	for(i=0; i<SIZE; i++){
		tmp->hashTable[i] = NULL;
	}
	tmp->depth = -1;
    tmp->memhigh = -4;
    tmp->memlow = 0;
	return tmp;
}

void deleteHashNode(BlockStructure node){
    int i=0;
    for(i=0; i<SIZE; i++){
        while( node->hashTable[i] != NULL ){
            BucketList tmp = node->hashTable[i];
            node->hashTable[i] = node->hashTable[i]->next;
            free(tmp);
        }
    }
    free(node);
}

void st_scopeIn(int withFunc)
{
	// if (hashTableTop == NULL)
	// {
	// 	hashTableTop = makeHashNode();
	// 	hashTableTop->depth = 0;
	// 	hashTableCurrent = hashTableTop;
	// }
	// else
	// {
	// 	if (hashTableCurrent->next == NULL)
	// 	{
	// 		BlockStructure tmp = makeHashNode();
	// 		hashTableCurrent->next = tmp;
	// 		tmp->before = hashTableCurrent;
	// 		tmp->depth = hashTableCurrent->depth + 1;
	// 		hashTableCurrent = tmp;
	// 	}
	// 	else
	// 	{
	// 		if (hashTableCurrent->next->sibling == NULL)
	// 		{
	// 			BlockStructure tmp = makeHashNode();
	// 			hashTableCurrent->next->sibling = tmp;
	// 			tmp->before = hashTableCurrent;
	// 			tmp->depth = hashTableCurrent->depth + 1;
	// 			hashTableCurrent = tmp;
	// 		}
	// 		else
	// 		{
	// 			BlockStructure tmp = hashTableCurrent->next->sibling;
	// 			while (tmp->sibling != NULL)
	// 				tmp = tmp->sibling;
	// 			tmp->sibling = makeHashNode();
	// 			tmp->sibling->before = hashTableCurrent;
	// 			tmp->sibling->depth = hashTableCurrent->depth + 1;
	// 			hashTableCurrent = tmp->sibling;
	// 		}
	// 	}
	// }
    if (hashTableTop == NULL){
        hashTableTop = makeHashNode();
		hashTableTop->depth = 0;
    } else {
        BlockStructure tmp = makeHashNode();
        tmp->next = hashTableTop;
        tmp->depth = hashTableTop->depth + 1;
        if( withFunc == 0 ){
            tmp->memlow = hashTableTop->memlow;
            tmp->memhigh = hashTableTop->memhigh;
        }
        hashTableTop = tmp;
    }
}

void st_scopeOut()
{
	// hashTableCurrent = hashTableCurrent->before;
    if( !Error && TraceAnalyze ){
        printSymTab(listing);
    }
    BlockStructure tmp = hashTableTop;
    hashTableTop = hashTableTop->next;
    deleteHashNode(tmp);
}

ParamInfo _createParamInfo(){
	ParamInfo paInfo = (ParamInfo)malloc(sizeof(struct ParamInfoRec));
	paInfo->expType = Dummy;
	paInfo->name = NULL;
	paInfo->next = NULL;
}

void inssertParamlInfo(SymbolInfo info, char* name, ExpType expType){
	if( info->p == NULL ){
		ParamInfo tmp = _createParamInfo();
		tmp->expType = expType;
		tmp->name = name;
		info->p = tmp;
	} else {
		ParamInfo tmp = info->p;
		while(tmp->next != NULL){
			tmp = tmp->next;
		}
		tmp->next = _createParamInfo();
		tmp->next->expType = expType;
		tmp->next->name = name;
	}
}

void hashTableTopMemdiff(int high, int low){
    hashTableTop->memhigh += high;
    hashTableTop->memlow += low;
}
