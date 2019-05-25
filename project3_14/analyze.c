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

/* Procedure insertNode inserts 
 * identifiers stored in t into 
 * the symbol table 
 */
static void insertNode(TreeNode *t)
{
  SymbolInfo info = NULL;
  //int i = 0;
  //while (t != NULL)
  //{
    if( t->nodekind == StmtK){
      switch (t->kind.stmt)
      {
      case AssignK:
      case IfK:
        break;
      case WhileK:
        break;
      case ReturnK:
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
        if (st_lookup(t->attr.name) == -1)
        {
          /* not yet in table, so treat as new definition */
          //st_insert(t->attr.name,t->lineno,location++);
          fprintf(listing, "ERROR, No Variable Need to declarate First\n");
          isErrorOccurred = TRUE;
        }
        else
        {
          /* already in table, so ignore location, 
             	add line number of use only */
          st_insert(t->attr.name, t->lineno, 0, NULL);
        }
        break;
      case OpK:
        break;
      case ConstK:
        break;
      case FuncCallK:
        if (st_lookup(t->attr.name) == -1)
        {
          fprintf(listing, "ERROR, No function Need to declarate First\n");
          isErrorOccurred = TRUE;
        }
        else
        {
          st_insert(t->attr.name, t->lineno, 0, NULL);
        }
        break;
      default:
        break;
      }
    } else if (t->nodekind == DeclarationK) {
      switch (t->kind.dec)
      {
      case SimpleK:
        info = getSymbolInfo(t);
        st_insert(t->attr.name, t->lineno, 0, info);
        break;
      case ArrayK:
        info = getSymbolInfo(t);
        st_insert(t->attr.name, t->lineno, 0, info);
        break;
      case FunctionK:
        info = getSymbolInfo(t);
        st_insert(t->attr.name, t->lineno, 0, info);
        break;
      case ParamK:
        info = getSymbolInfo(t);
        st_insert(t->attr.name, t->lineno, 0, info);
        break;
      default:
        break;
      }
    }

    //t = t->sibling;
  //}
}

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode *syntaxTree)
{
  st_scopeIn();
  traverse(syntaxTree, insertNode, nullProc);
  if (TraceAnalyze)
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
  traverse(syntaxTree, nullProc, checkNode);
}
