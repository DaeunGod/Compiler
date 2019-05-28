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
int isErrorOccurred = FALSE;

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

int functionMemLoc = 0;
/* Procedure insertNode inserts 
 * identifiers stored in t into 
 * the symbol table 
 */
static int insertNode(TreeNode *t, int scopeIn, char* callFrom, int memloc)
{
  SymbolInfo info = NULL;
  int i = 0;
  int localVarLoc = 0;
  while( t != NULL )
  {
    if( isErrorOccurred == TRUE )
      break;

    if( t->nodekind == StmtK){
      switch (t->kind.stmt)
      {
      case AssignK:
        for(i=0; i<MAXCHILDREN; i++){
          insertNode(t->child[i], FALSE, callFrom, memloc);
        }
        break;
      case IfK:
      case WhileK:
      case ReturnK:
        for(i=0; i<MAXCHILDREN; i++){
          insertNode(t->child[i], FALSE, callFrom, memloc);
        }
        break;
      case CompoundK:        
        if( scopeIn == FALSE )
          st_scopeIn();

        localVarLoc = insertNode(t->child[0], FALSE, callFrom, memloc);
        
        insertNode(t->child[1], FALSE, callFrom, memloc+localVarLoc);

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
          insertNode(t->child[0], FALSE, callFrom, memloc); // It will proceed If ID is Array
        }
        break;
      case OpK:
        for(i=0; i<MAXCHILDREN; i++){
          insertNode(t->child[i], FALSE, callFrom, memloc);
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
          insertNode(t->child[0], FALSE, callFrom, memloc);
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
          TreeNode *tmp;
          int count=0;
          info = getSymbolInfo(t);
          st_insert(t->attr.name, t->lineno, functionMemLoc, info);
          functionMemLoc++;
          st_scopeIn();
          tmp = t->child[0];
          while(tmp!=NULL){
            count++;
            tmp = tmp->sibling;
          }
          insertNode(t->child[0], FALSE, t->attr.name, 4*count); // Parameter part
          insertNode(t->child[1], TRUE, t->attr.name, -4); // Compound Part
        }
        break;
      case SimpleK:
        if( _checkDuplicatedSymbol(t, LocalNFunc) ){
          info = getSymbolInfo(t);
          //if( _checkVariableTypeInDec(t, info) ){
            if( callFrom == NULL ){
              memloc += 4;
            } else {
              memloc -= 4;
              localVarLoc -= 4;
            }
            
            st_insert(t->attr.name, t->lineno, memloc, info);
          //} else {
          //  free(info);
          //}
        }
        break;
      case ArrayK:
        if( _checkDuplicatedSymbol(t, LocalNFunc) ){
          info = getSymbolInfo(t);
          //if( _checkVariableTypeInDec(t, info) ){
            if( callFrom == NULL ){
              memloc += 4*info->ArraySize;
            } else {
              memloc -= 4*info->ArraySize;
              localVarLoc -= 4*info->ArraySize;
            }
            st_insert(t->attr.name, t->lineno, memloc, info);
          //} else {
          //  free(info);
          //} 
        }
      break;
      case ParamK:
        if( _checkDuplicatedSymbol(t, LocalNFunc) ){
          info = getSymbolInfo(t);
          //if( _checkVariableTypeInDec(t, info) ){
            
            st_insert(t->attr.name, t->lineno, memloc, info);
            memloc -= 4;
            if( callFrom != NULL ){
              SymbolInfo callFuncInfo = st_lookupInfo(callFrom);
              if( info->isArray )
                inssertParamlInfo(callFuncInfo, t->attr.name, Array);
              else
                inssertParamlInfo(callFuncInfo, t->attr.name, info->expType);
            }
          //} else {
          //  free(info);
          //}
        }
        break;
      default:
        break;
      }
    }
  
    t = t->sibling;
  }
  
  return localVarLoc;
}

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode *syntaxTree)
{
  st_scopeIn();
  //traverse(syntaxTree, insertNode, nullProc);
  insertNode(syntaxTree, FALSE, NULL, 0);
  //printSymTab(listing);
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
static ExpType checkNode(TreeNode *t, int scopeIn, int siblingCount, char* callFrom)
{
  BucketList bucket = NULL;
  SymbolInfo info = NULL;
  ExpType e1, e2;
  TreeNode *p1, *p2;
  ExpType res = Dummy;
  ParamInfo pp1;
  int i = 0;
  int errorcheck=0;
  
  //while( t != NULL )
  if( t != NULL && !isErrorOccurred )
  {
    // if( isErrorOccurred ){
    //   break;
    // }
    //printf("line no: %d\n", t->lineno);
    if( t->nodekind == StmtK){
      switch (t->kind.stmt)
      {
      case AssignK:
        e1 = checkNode(t->child[0], FALSE, 0, callFrom);
        e2 = checkNode(t->child[1], FALSE, 0, callFrom);
        
        if( !isErrorOccurred && e2 != Integer ){
          isErrorOccurred = TRUE;
          typeError(t, "right hand side's type does not match with left hand side.");
          break;
        }
        res = e1;
        break;
      case IfK:
        e1 = checkNode(t->child[0], FALSE, 0, callFrom);
        checkNode(t->child[1], FALSE, siblingCount, callFrom); // compound stat
        if( t->child[1]->kind.stmt == CompoundK)
          siblingCount++;
        if( t->child[2] != NULL){
          checkNode(t->child[2], FALSE, siblingCount, callFrom); // compound stat
          if( t->child[1]->kind.stmt == CompoundK)
            siblingCount++;
        }
        
        if( e1 != Integer ){
          isErrorOccurred = TRUE;
          typeError(t, "expression part of if statement should be type of integer not void");
        }
        break;
      case WhileK:
        e1 = checkNode(t->child[0], FALSE, 0, callFrom);
        checkNode(t->child[1], FALSE, siblingCount, callFrom); // compound stat
        siblingCount++;
        if( e1 != Integer ){
          isErrorOccurred = TRUE;
          typeError(t, "expression part of while statement should be type of integer not void");
        }
        break;
      case ReturnK:
        info = st_lookupInfo(callFrom);
        e1 = checkNode(t->child[0], FALSE, 0, callFrom);
        info->retExpType = e1;
        break;
      case CompoundK:
        if( scopeIn == FALSE ){
          //printf("sibl %d %d\n", siblingCount, scopeIn);
          st_scopeMove(siblingCount);
          siblingCount++;
        }
        
        checkNode(t->child[0], FALSE, 0, callFrom);
        checkNode(t->child[1], FALSE, 0, callFrom);
        st_scopeOut();
        break;
      default:
        break;
      }
    } else if (t->nodekind == ExpK) {
      switch (t->kind.exp)
      {
      case IdK:
        info = st_lookupInfo(t->attr.name);
        if( info->isArray ){
          if( t->child[0] != NULL ){
            ExpType e = checkNode(t->child[0], FALSE, 0, callFrom);
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
          if(t->child[0] != NULL){
            char str[256];
            sprintf(str, "'%s' is not array variable.", t->attr.name);
            typeError(t->child[0], str);
            isErrorOccurred = TRUE;
            break;
          }
          res = info->expType;
        }
        break;
      case OpK:
        e1 = checkNode(t->child[0], FALSE, 0, callFrom);
        e2 = checkNode(t->child[1], FALSE, 0, callFrom);
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
        if( info->decKind != FunctionK ){
          char str[256];
          sprintf(str, "'%s' is not function", t->attr.name);
          typeError(t, str);
          isErrorOccurred = TRUE;
          break;
        }
        pp1 = info->p;
        p2 = t->child[0];
        
        if( (pp1 == NULL && p2 != NULL) || (pp1 != NULL && p2 == NULL) ){
          isErrorOccurred = TRUE;
        }
        while( !isErrorOccurred && pp1 != NULL && p2 != NULL ){
          e1 = pp1->expType;
          e2 = checkNode(p2, FALSE, 0, callFrom);
          
          if( (e1 != e2) ){
            isErrorOccurred = TRUE;
            break;
          }
          pp1 = pp1->next;
          p2 = p2->sibling;
        }
        if( !isErrorOccurred && pp1 != NULL ){
          typeError(t, "not enough parameters");
          isErrorOccurred = TRUE;
          break;
        }
        if( !isErrorOccurred && p2 != NULL){
          typeError(t, "too many parameters");
          isErrorOccurred = TRUE;
          break;
        }

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
        info = st_lookupInfo(t->attr.name);
        if( strcmp(t->attr.name, "main") == 0 ){
          if( t->sibling != NULL ){
            isErrorOccurred = TRUE;
            typeError(t, "main function should be placed end of file.");
            break;
          }
          if( info->expType != Void ){
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
        checkNode(t->child[0], FALSE, 0, t->attr.name); // Parameter part
        checkNode(t->child[1], TRUE, 0, t->attr.name); // Compound part
        if( info->expType == Void ){
          if( info->retExpType != -1 ){
            isErrorOccurred = TRUE;
            typeError(t, "void function has no return statement.");
            break;
          }
        } else {
          if( info->retExpType == -1 ){
            isErrorOccurred = TRUE;
            typeError(t, "function should have return statement.");
            break;
          }
        }
        break;
      case SimpleK:
      case ArrayK:
      case ParamK:
        info = st_lookupInfo(t->attr.name);
        if( !_checkVariableTypeInDec(t, info) ){
          break;
        }
        // testing();
        // if( info == NULL ){
        //   printf("info null error\n");
        // }
        if( info->isArray )
          res = Array;
        else
          res = info->expType;
        break;
      default:
        break;
      }
    }
    if( t->sibling != NULL ) {
      checkNode( t->sibling, FALSE, siblingCount, callFrom);
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
  checkNode(syntaxTree, FALSE, 0, NULL);
  //testing();
  
  
  //traverse(syntaxTree, nullProc, checkNode);
}
