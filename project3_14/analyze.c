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
        for(i=0; i<MAXCHILDREN; i++){
          insertNode(t->child[i], FALSE);
        }
        break;
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
          info->params = t->child[0];
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
    //testing();
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
static ExpType checkNode(TreeNode *t, int scopeIn, int siblingCount)
{
  BucketList bucket = NULL;
  SymbolInfo info = NULL;
  ExpType e1, e2;
  TreeNode *p1, *p2;
  ExpType res = Dummy;
  int i = 0;
  
  //while( t != NULL )
  if( t != NULL && !isErrorOccurred )
  {
    // if( isErrorOccurred ){
    //   break;
    // }
    printf("line no: %d\n", t->lineno);
    if( t->nodekind == StmtK){
      switch (t->kind.stmt)
      {
      case AssignK:
        //printf("boom3 here\n");
        e1 = checkNode(t->child[0], FALSE, 0);
        e2 = checkNode(t->child[1], FALSE, 0);
        
        if( e2 != Integer ){
          isErrorOccurred = TRUE;
          typeError(t, "right side's type from assign should be integer not void");
          break;
        }
        res = e1;
        break;
      case IfK:
        //printf("boom here\n");
        e1 = checkNode(t->child[0], FALSE, 0);
        checkNode(t->child[1], FALSE, 0);
        checkNode(t->child[2], FALSE, 0);
        if( e1 != Integer ){
          isErrorOccurred = TRUE;
          typeError(t, "expression part of if statement should be type of integer not void");
        }
        break;
      case WhileK:
        e1 = checkNode(t->child[0], FALSE, 0);
        checkNode(t->child[1], FALSE, 0);
        if( e1 != Integer ){
          isErrorOccurred = TRUE;
        }
        break;
      case ReturnK:
        break;
      case CompoundK:
        if( scopeIn == FALSE ){
          st_scopeMove(siblingCount);
          siblingCount++;
        }
        for(i=0; i<MAXCHILDREN; i++){
          checkNode(t->child[i], FALSE, 0);
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
        printf("boom4 here %d %s\n", siblingCount, t->attr.name);
        info = st_lookupInfo(t->attr.name);
        if( info->isArray ){
          if( t->child[0] != NULL ){
            ExpType e = checkNode(t->child[0], FALSE, 0);
            if( e != Integer ){
              typeError(t->child[0], "Invalid type of subscript for using Array");
              isErrorOccurred = TRUE;
              break;
            } 
            res = info->expType;
          } else {
            res = Array;
          }
        } else {
          res = info->expType;
        }
        break;
      case OpK:
        //printf("boom2 here\n");
        e1 = checkNode(t->child[0], FALSE, 0);
        e2 = checkNode(t->child[1], FALSE, 0);
        if( isErrorOccurred ){
          /* prevent occurring multiple error messages */
          break;
        }
        if( e1 != Integer || e2 != Integer ){
          typeError(t->child[0], "Invalid Data type for using Operations. need int not void");
          isErrorOccurred = TRUE;
          break;
        }
        res = Integer;
        break;
      case ConstK:
        res = Integer;
        break;
      case FuncCallK:
        info = st_lookupInfo(t->attr.name);
        
        p1 = info->params;
        p2 = t->child[0];
        
        if( (p1 == NULL && p2 != NULL) || (p1 != NULL && p2 == NULL) ){
          isErrorOccurred = TRUE;
        }
        while( !isErrorOccurred && p1 != NULL && p2 != NULL ){
          printf("\tname:%s %s\n", p1->attr.name, p2->attr.name);
          e1 = checkNode(p1, FALSE, 0);
          printf("\tname2:%s %s\n", p1->attr.name, p2->attr.name);
          e2 = checkNode(p2, FALSE, 0);
          
          if( (e1 != e2) ){
            isErrorOccurred = TRUE;
            //printf("here2 %s %s %d %d\n", p1->attr.name, p2->attr.name, e1, e2);
            break;
          }
          p1 = p1->sibling;
          p2 = p2->sibling;
        }
        printf("boom\n");
        if( isErrorOccurred == TRUE ){
          char str[256];
          sprintf(str, "type miss match using '%s' function", t->attr.name);
          typeError(t, str);
          break;
        }
        
        res = info->expType;
        break;
      default:
        break;
      }
    } else if (t->nodekind == DeclarationK) {
      switch (t->kind.dec)
      {
      case FunctionK:
        st_scopeMove(siblingCount);
        siblingCount++;
        if( strcmp(t->attr.name, "main") == 0 ){
          info = st_lookupInfo(t->attr.name);
          if( t->sibling != NULL ){
            isErrorOccurred = TRUE;
            typeError(t, "main function should be placed end of file.");
            break;
          }
          if( info->expType != Void ){
            printf("type: %d\n", t->expType);
            isErrorOccurred = TRUE;
            typeError(t, "main function's return type should be void.");
            break;
          }
          if( t->child[0] != NULL ){
            isErrorOccurred = TRUE;
            typeError(t, "main function do not have parameters.");
            break;
          }
        }
        //printf("boom5 here %s %d\n", t->attr.name, siblingCount);
        checkNode(t->child[0], FALSE, 0); // Parameter part
        checkNode(t->child[1], TRUE, 0); // Compound part
        break;
      case SimpleK:
      case ArrayK:
      case ParamK:
        info = st_lookupInfo(t->attr.name);
        testing();
        printf("boom4 continue\n");
        if( info->isArray )
          res = Array;
        else
          res = info->expType;
        printf("boom4 continue\n");
        break;
      default:
        break;
      }
    }

    printf("boom4 continue\n");
    if( t->sibling != NULL ) {
      //st_scopeMove(1);
      checkNode( t->sibling, FALSE, siblingCount);
    }
    //t = t->sibling;
  }
  return res;
}

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode *syntaxTree)
{
  checkNode(syntaxTree, FALSE, 0);
  testing();
  
  //traverse(syntaxTree, nullProc, checkNode);
}
