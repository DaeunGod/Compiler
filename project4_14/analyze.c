/****************************************************/
/* File: analyze.c                                  */
/* Semantic analyzer implementation                 */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "analyze.h"

/* counter for variable memory locations */
static int location = 0;

/* TODO
 */
//int isErrorOccurred = FALSE;

void debugLog(char * str){
  printf("DEBUG: %s\n", str);
}

/* Procedure traverse is a generic recursive 
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc 
 * in postorder to tree pointed to by t
 */
static void traverse(TreeNode *t,
                     void (*preProc)(TreeNode *),
                     void (*postProc)(TreeNode *))
{
  if( Error )
    return ;

  if (t != NULL)
  {
    preProc(t);
    {
      int i;
      for (i = 0; i < MAXCHILDREN; i++)
      {
        traverse(t->child[i], preProc, postProc);
      }
      postProc(t);
      traverse(t->sibling, preProc, postProc);
    }
  }
}

/* nullProc is a do-nothing procedure to 
 * generate preorder-only or postorder-only
 * traversals from traverse
 */
static void nullProc(TreeNode *t)
{
  if (t == NULL)
    return;
  else
    return;
}

/*
 */
static void compoundStatProc(TreeNode *t)
{
  if (t->nodekind == StmtK){
    if( t->kind.stmt == CompoundK ){
      st_scopeOut();
    }
  }
}

/* TODO
 */
int _checkDuplicatedSymbol(TreeNode *t, SearchFlag searchFlag){
  if (st_lookup(t->attr.name, searchFlag) != -1)
  {
    fprintf(listing, "ERROR in line %d, declaration of a duplicated '%s'. first declared at line %d\n", 
            t->lineno, t->attr.name, st_lookupLineNo(t->attr.name));
    Error = TRUE;
    return 0;
  }
  return 1;
}

/* TODO
 */
int _checkVariableTypeInDec(TreeNode *t, SymbolInfo info){
  int flag = 0;
  char *str = NULL;
  if( info->decKind == SimpleK ){
    flag = 1;
    str = "Variable";
  } else if( info->decKind == ArrayK){
    flag = 1;
    str = "Array";
  } else if( info->decKind == ParamK){
    flag = 1;
    str = "Parameter";
  }
  if( flag && info->expType != Integer ){
    fprintf(listing, "ERROR in line %d, %s(name: %s) must declared as integer not void.\n", 
          t->lineno, str, t->attr.name);
    Error = TRUE;
    return 0;
  }
  
  return 1;
}

/*
  TODO
 */
int callFromFunc = 0;
int functionMemLoc = 0;
char* callFuncName = NULL;

/* Procedure insertNode inserts 
 * identifiers stored in t into 
 * the symbol table 
 */
static void insertNode(TreeNode *t){
  //SymbolInfo info = NULL;

  int memloc = 0;

  if (t->nodekind == StmtK)
  {
    switch (t->kind.stmt)
    {
    case CompoundK:
      if( callFromFunc == 0 )
        st_scopeIn(callFromFunc);
      else 
        callFromFunc = 0;
      break;
    case ReturnK:
      {
        SymbolInfo info = st_lookupInfo(callFuncName);
        t->info = info;
      }
      break;
    }
    
  }
  else if (t->nodekind == ExpK)
  {
    switch (t->kind.exp)
    {
    case IdK:
      if (st_lookup(t->attr.name, Full) == -1)
      {
        /* not yet in table, so treat as new definition */
        //st_insert(t->attr.name,t->lineno,location++);
        fprintf(listing, "ERROR in line %d, use of undeclared identifier '%s'\n", t->lineno, t->attr.name);
        Error = TRUE;
      }
      else
      {
        /* already in table, so ignore location, 
             	add line number of use only */
        SymbolInfo info = st_lookupInfo(t->attr.name);
        t->info = info;
        st_insert(t->attr.name, t->lineno, 0, NULL);
      }
      break;
    case FuncCallK:
      if (st_lookup(t->attr.name, Full) == -1)
      {
        fprintf(listing, "ERROR in line %d, use of undeclared function '%s'\n", t->lineno, t->attr.name);
        Error = TRUE;
      }
      else
      {
        SymbolInfo info = st_lookupInfo(t->attr.name);
        t->info = info;
        st_insert(t->attr.name, t->lineno, 0, NULL);
      }
      break;
    case InputCallK:
      t->info = getSymbolInfo(t);
      st_insert(t->attr.name, t->lineno, 0, t->info);
      break;
    case OutputCallK:
      t->info = getSymbolInfo(t);
      st_insert(t->attr.name, t->lineno, 0, t->info);
      break;
    }
  }
  else if (t->nodekind == DeclarationK)
  {
    switch (t->kind.dec)
    {
    case FunctionK:
      if (_checkDuplicatedSymbol(t, LocalNFunc))
      {
        TreeNode *tmp;
        int count = 0;
        callFuncName = t->attr.name;
        t->info = getSymbolInfo(t);
        st_insert(t->attr.name, t->lineno, functionMemLoc, t->info);
        functionMemLoc++;
        
        callFromFunc = 1;
        st_scopeIn(callFromFunc);

        tmp = t->child[0];
        while(tmp!=NULL){
          count++;
          tmp = tmp->sibling;
        }
        getHashTableTop()->memlow += 4*count;
      }
      break;
    case SimpleK:
      if (_checkDuplicatedSymbol(t, LocalNFunc))
      {
        t->info = getSymbolInfo(t);

        if( getHashTableTop()->depth == 0 ){
          getHashTableTop()->memlow += 4;
          t->info->isGlobal = 1;
          memloc = getHashTableTop()->memlow;
        } else {
          getHashTableTop()->memhigh -= 4;
          memloc = getHashTableTop()->memhigh;
        }

        st_insert(t->attr.name, t->lineno, memloc, t->info);
      }
      break;
    case ArrayK:
      if (_checkDuplicatedSymbol(t, LocalNFunc))
      {
        t->info = getSymbolInfo(t);
        if( getHashTableTop()->depth == 0 ){
          getHashTableTop()->memlow += 4*(t->info)->ArraySize;
          memloc = getHashTableTop()->memlow;
          t->info->isGlobal = 1;
        } else {
          getHashTableTop()->memhigh -= 4*(t->info)->ArraySize;
          memloc = getHashTableTop()->memhigh;
        }
        st_insert(t->attr.name, t->lineno, memloc, t->info);
      }
      break;
    case ParamK:
      if (_checkDuplicatedSymbol(t, LocalNFunc))
      {
        t->info = getSymbolInfo(t);
        memloc = getHashTableTop()->memlow;
        st_insert(t->attr.name, t->lineno, memloc, t->info);
        getHashTableTop()->memlow -= 4;
        // memloc -= 4;
        // if (callFrom != NULL)
        {
          SymbolInfo callFuncInfo = st_lookupInfo(callFuncName);
          if (t->info->isArray)
            inssertParamlInfo(callFuncInfo, t->attr.name, Array);
          else
            inssertParamlInfo(callFuncInfo, t->attr.name, t->info->expType);
        }
      }
      break;
    }
  }
}

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode *syntaxTree)
{
  st_scopeIn(0);
  fprintf(listing, "\nSymbol table:\n\n");
  traverse(syntaxTree, insertNode, compoundStatProc);
  //insertNode(syntaxTree, FALSE, NULL, 0);
  //printSymTab(listing);
  if ( !Error && TraceAnalyze )
  {
    
    //printSymTab(listing);
    printSymTab(listing);
  }
  
}

static void typeError(TreeNode *t, char *message)
{
  fprintf(listing, "Type error at line %d: %s\n", t->lineno, message);
  Error = TRUE;
}

/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(TreeNode *t)
{
  BucketList bucket = NULL;
  SymbolInfo info = NULL;
  ExpType e1, e2;
  TreeNode *p1, *p2;
  ExpType res = Dummy;
  ParamInfo pp1;
  int i = 0;
  
  if( Error ){
    return ;
  }
  
  if( t->nodekind == StmtK){
    switch (t->kind.stmt)
    {
    case AssignK:
      e1 = t->child[0]->expType;
      e2 = t->child[1]->expType;
      
      if( !Error && e2 != Integer ){
        Error = TRUE;
        typeError(t, "right hand side's type does not match with left hand side.");
        break;
      }
      t->expType = Integer;
      break;
    case IfK:
      e1 = t->child[0]->expType;
      
      if( e1 != Integer ){
        Error = TRUE;
        typeError(t, "expression part of if statement should be type of integer not void");
        break;
      }
      break;
    case WhileK:
      e1 = t->child[0]->expType;
      if( e1 != Integer ){
        Error = TRUE;
        typeError(t, "expression part of while statement should be type of integer not void");
        break;
      }
      break;
    case ReturnK:
      info = t->info;
      e1 = t->child[0]->expType;
      info->retExpType = e1;
      break;
    case CompoundK:
      break;
    default:
      break;
    }
  } else if (t->nodekind == ExpK) {
    switch (t->kind.exp)
    {
    case IdK:
      info = t->info;
      if( info->isArray == TRUE ){
        if( t->child[0] != NULL ){
          ExpType e = t->child[0]->expType;
          if( e != Integer ){
            typeError(t->child[0], "Invalid type of subscript for using Array");
            Error = TRUE;
            break;
          } 
          t->expType = Integer;
        } else {
          t->expType = Array;
        }
      } else {
        if(t->child[0] != NULL){
          char str[256];
          sprintf(str, "'%s' is not array variable.", t->attr.name);
          typeError(t->child[0], str);
          Error = TRUE;
          break;
        }
        t->expType = info->expType;
      }
      break;
    case OpK:
      e1 = t->child[0]->expType;
      e2 = t->child[1]->expType;
      if( e1 != Integer || e2 != Integer ){
        typeError(t->child[0], "Invalid Data type for using Operations. need int not void");
        Error = TRUE;
        break;
      }
      t->expType = Integer;
      break;
    case ConstK:
      t->expType = Integer;
      break;
    case FuncCallK:
      info = t->info;
      if( info->decKind != FunctionK ){
        char str[256];
        sprintf(str, "'%s' is not function", t->attr.name);
        typeError(t, str);
        Error = TRUE;
        break;
      }
      pp1 = info->p;
      p2 = t->child[0];
      
      if( (pp1 == NULL && p2 != NULL) || (pp1 != NULL && p2 == NULL) ){
        Error = TRUE;
      }
      while( !Error && pp1 != NULL && p2 != NULL ){
        e1 = pp1->expType;
        e2 = p2->expType;
        
        if( (e1 != e2) ){
          Error = TRUE;
          break;
        }
        pp1 = pp1->next;
        p2 = p2->sibling;
      }
      if( !Error && pp1 != NULL ){
        typeError(t, "not enough parameters");
        Error = TRUE;
        break;
      }
      if( !Error && p2 != NULL){
        typeError(t, "too many parameters");
        Error = TRUE;
        break;
      }

      if( Error == TRUE ){
        char str[256];
        sprintf(str, "type miss match using '%s' function", t->attr.name);
        typeError(t, str);
        break;
      }
      
      t->expType = t->info->expType;
      break;
    case InputCallK:
      break;
    case OutputCallK:
      break;
    default:
      break;
    }
  } else if (t->nodekind == DeclarationK) {
    switch (t->kind.dec)
    {
    case FunctionK:
      //info = st_lookupInfo(t->attr.name);
      info = t->info;
      if( strcmp(t->attr.name, "main") == 0 ){
        if( t->sibling != NULL ){
          Error = TRUE;
          typeError(t, "main function should be placed end of file.");
          break;
        }
        if( info->expType != Void ){
          Error = TRUE;
          typeError(t, "main function's return type should be void.");
          break;
        }
        if( t->child[0] != NULL ){
          Error = TRUE;
          typeError(t, "main function do not have parameters.");
          break;
        }
      }
      if( info->expType == Void ){
        if( info->retExpType != -1 ){
          Error = TRUE;
          typeError(t, "void function has no return statement.");
          break;
        }
      } else {
        if( info->retExpType == -1 ){
          Error = TRUE;
          typeError(t, "function should have return statement.");
          break;
        }
      }
      break;
    case SimpleK:
    case ArrayK:
    case ParamK:
      info = t->info;
      if( !_checkVariableTypeInDec(t, info) ){
        break;
      }
      break;
    default:
      break;
    }
  }
  
}

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode *syntaxTree)
{
  //checkNode(syntaxTree, FALSE, 0, NULL);
  //testing();
  
  
  traverse(syntaxTree, nullProc, checkNode);
}
