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
static int isErrorOccurred = FALSE;

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
  if (isErrorOccurred == TRUE)
    return;

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

/* TODO
 */
int _checkDuplicatedSymbol(TreeNode *t, SearchFlag searchFlag){
  if (st_lookup(t->attr.name, searchFlag) != -1)
  {
    fprintf(listing, "ERROR in line %d, declaration of a duplicated '%s'. first declared at line %d\n", 
            t->lineno, t->attr.name, st_lookupLineNo(t->attr.name));
    isErrorOccurred = TRUE;
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
    isErrorOccurred = TRUE;
    return 0;
  }
  
  return 1;
}

/* Procedure insertNode inserts 
 * identifiers stored in t into 
 * the symbol table 
 */
static void insertNode(TreeNode *t, int scopeIn)
{
  SymbolInfo info = NULL;
  int i = 0;
  while( t != NULL )
  {
    if( isErrorOccurred == TRUE )
      break;

    if( t->nodekind == StmtK){
      switch (t->kind.stmt)
      {
      case AssignK:
      case IfK:
      case WhileK:
      case ReturnK:
        for(i=0; i<MAXCHILDREN; i++){
          insertNode(t->child[i], FALSE);
        }
        break;
      case CompoundK:        
        if( scopeIn == FALSE )
          st_scopeIn();

        for(i=0; i<MAXCHILDREN; i++){
          insertNode(t->child[i], FALSE);
        }

        st_scopeOut();
        break;
      default:
        break;
      }
    } else if (t->nodekind == ExpK) {
      switch (t->kind.exp)
      {
      case IdK:
        if (st_lookup(t->attr.name, Full) == -1)
        {
          /* not yet in table, so treat as new definition */
          //st_insert(t->attr.name,t->lineno,location++);
          fprintf(listing, "ERROR in line %d, use of undeclared identifier '%s'\n", t->lineno, t->attr.name);
          isErrorOccurred = TRUE;
        }
        else
        {
          /* already in table, so ignore location, 
             	add line number of use only */
          st_insert(t->attr.name, t->lineno, 0, NULL);
          insertNode(t->child[0], FALSE); // It will proceed If ID is Array
        }
        break;
      case OpK:
        for(i=0; i<MAXCHILDREN; i++){
          insertNode(t->child[i], FALSE);
        }
        break;
      case ConstK:
        break;
      case FuncCallK:
        if (st_lookup(t->attr.name, Full) == -1)
        {
          fprintf(listing, "ERROR in line %d, use of undeclared function '%s'\n", t->lineno, t->attr.name);
          isErrorOccurred = TRUE;
        }
        else
        {
          st_insert(t->attr.name, t->lineno, 0, NULL);
          insertNode(t->child[0], FALSE);
        }
        break;
      default:
        break;
      }
    } else if (t->nodekind == DeclarationK) {
      switch (t->kind.dec)
      {
      case FunctionK:
        if( _checkDuplicatedSymbol(t, LocalNFunc) ){
          info = getSymbolInfo(t);
          st_insert(t->attr.name, t->lineno, 0, info);
          st_scopeIn();
          insertNode(t->child[0], FALSE); // Parameter part
          insertNode(t->child[1], TRUE); // Compound Part
        }
        break;
      case SimpleK:
      case ArrayK:
      case ParamK:
        if( _checkDuplicatedSymbol(t, LocalNFunc) ){
          info = getSymbolInfo(t);
          if( _checkVariableTypeInDec(t, info) ){
            st_insert(t->attr.name, t->lineno, 0, info);
          } else {
            free(info);
          }
        }
        break;
      default:
        break;
      }
    }
    t = t->sibling;
  }
  
}

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode *syntaxTree)
{
  st_scopeIn();
  //traverse(syntaxTree, insertNode, nullProc);
  insertNode(syntaxTree, FALSE);
  if ( !isErrorOccurred && TraceAnalyze )
  {
    fprintf(listing, "\nSymbol table:\n\n");
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
  switch (t->nodekind)
  {
  case ExpK:
    switch (t->kind.exp)
    {
    case OpK:
      /*if ((t->child[0]->type != Integer) ||
              (t->child[1]->type != Integer))
            typeError(t,"Op applied to non-integer");
          if ((t->attr.op == EQ) || (t->attr.op == LT))
            t->type = Boolean;
          else
            t->type = Integer;*/
      break;
    case ConstK:
    case IdK:
      //t->type = Integer;
      break;
    default:
      break;
    }
    break;
  case StmtK:
    switch (t->kind.stmt)
    {
    case IfK:
      //if (t->child[0]->type == Integer)
      //  typeError(t->child[0],"if test is not Boolean");
      break;
    case AssignK:
      //if (t->child[0]->type != Integer)
      //  typeError(t->child[0],"assignment of non-integer value");
      break;
    case WriteK:
      //if (t->child[0]->type != Integer)
      //  typeError(t->child[0],"write of non-integer value");
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
}

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode *syntaxTree)
{
  checkNode(syntaxTree);
  //traverse(syntaxTree, nullProc, checkNode);
}
