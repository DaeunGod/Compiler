/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "tiny.tab.h"
#include "globals.h"
#include "util.h"

extern int yylineno;
/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( TokenType token, const char* tokenString )
{ switch (token)
  { case IF:
	  fprintf(listing,
		"\t\tIF\t\t%s\n", tokenString);
	  break;
    case ELSE:
	  fprintf(listing,
		"\t\tELSE\t\t%s\n", tokenString);
	  break;
	case INT:
	  fprintf(listing,
		"\t\tINT\t\t%s\n", tokenString);
	  break;
	case VOID:
	  fprintf(listing,
		"\t\tVOID\t\t%s\n", tokenString);
	  break;
	case WHILE:
	  fprintf(listing,
		"\t\tWHILE\t\t%s\n", tokenString);
	  break;
	case RETURN:
	  fprintf(listing,
		"\t\tRETURN\t\t%s\n", tokenString);
	  break;
	  
    case STARTCOMMENT: fprintf(listing,"\t\t/*\t\t%s\n", tokenString); break;
    case ASSIGN: fprintf(listing,"\t\t=\t\t%s\n", tokenString); break;
    case LT: fprintf(listing,"<%s\n", tokenString); break;
    case GT: fprintf(listing,">%s\n", tokenString); break;
    case LTET: fprintf(listing,"<=%s\n", tokenString); break;
    case GTET: fprintf(listing,">=%s\n", tokenString); break;
    case EQ: fprintf(listing,"==%s\n", tokenString); break;
    case NOTEQ: fprintf(listing,"!=%s\n", tokenString); break;
    case LPAREN: fprintf(listing,"\t\t(\t\t%s\n", tokenString); break;
    case RPAREN: fprintf(listing,"\t\t)\t\t\%s\n", tokenString); break;
    case LSQBRACKET: fprintf(listing,"\t\t[\t\t\%s\n", tokenString); break;
    case RSQBRACKET: fprintf(listing,"\t\t]\t\t\%s\n", tokenString); break;
    case LBRACE: fprintf(listing,"\t\t{\t\t\%s\n", tokenString); break;
    case RBRACE: fprintf(listing,"\t\t}\t\t\%s\n", tokenString); break;
    case SEMI: fprintf(listing,"\t\t;\t\t%s\n", tokenString); break;
    case PLUS: fprintf(listing,"+%s\n", tokenString); break;
    case MINUS: fprintf(listing,"-%s\n", tokenString); break;
    case TIMES: fprintf(listing,"*%s\n", tokenString); break;
    case OVER: fprintf(listing,"/%s\n", tokenString); break;
    case COMMA: fprintf(listing,"\t\t,\t\t%s\n", tokenString); break;
    case ENDFILE: fprintf(listing,"\t\tEOF\n"); break;
    case NUM:
      fprintf(listing,
          "\t\tNUM\t\t%s\n",tokenString);
      break;
    case ID:
      fprintf(listing,
          "\t\tID\t\t%s\n",tokenString);
      break;
    case ERROR:
      fprintf(listing,
          "\t\tERROR\t\t%s\n","Comment Error");
      break;
    default: /* should never happen */
      ;//fprintf(listing,"Unknown token: %d\n",token);
  }
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->lineno = lineno;
  }
  return t;
}

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->lineno = lineno;
    t->expType = Void;
  }
  return t;
}

/* Function newDecNode creates a new declaration 
 * node for syntax tree construction
 */
TreeNode * newDecNode(DeclarationKind kind) {
  TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = DeclarationK;
    t->kind.dec = kind;
    t->lineno = lineno;
    t->expType = Void;
  }
  return t;
}

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else strcpy(t,s);
  return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{ int i;
  for (i=0;i<indentno;i++)
    fprintf(listing," ");
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * tree )
{ int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
	if( tree->nodekind == DeclarationK ){
		switch (tree->kind.dec) {
			case FunctionK:
				fprintf(listing, "Function: %s\n", tree->attr.name);
				INDENT;
				printSpaces();
				if( tree->expType == INT )
					fprintf(listing, "Type: Int\n");
				else if( tree->expType == VOID )
					fprintf(listing, "Type: Void\n");
				UNINDENT;
				if( tree->child[0] == NULL ){
					INDENT;
					printSpaces();
					fprintf(listing, "Parameter: (null)\n");
					UNINDENT;
				}
			
				//printTree(tree->child[0]);
				//printTree(tree->child[1]);
				break;
			case ParamK:
				if( tree == NULL ){
					fprintf(listing, "Parameter: (null)\n");
				}
				else{
					fprintf(listing, "Parameter: %s\n", tree->attr.name);
					INDENT;
					printSpaces();
					if( tree->expType == INT )
						fprintf(listing, "Type: Int\n");
					else if( tree->expType == VOID )
						fprintf(listing, "Type: Void\n");
					UNINDENT;
				}
				break;
			case ArrayK:
				fprintf(listing, "ID: %s\n", tree->attr.name);
				printSpaces();
				fprintf(listing, "Type: Array %d\n", tree->val);
				break;
			case SimpleK:
				fprintf(listing, "ID: %s\n", tree->attr.name);
				printSpaces();
				if( tree->expType == INT )
					fprintf(listing, "Type: Int\n");
				else if( tree->expType == VOID )
					fprintf(listing, "Type: Void\n");
				break;
		}
	}
	else if (tree->nodekind==StmtK)
    { switch (tree->kind.stmt) {
        case IfK:
          fprintf(listing,"If\n");
		  /*for(i=0; i<MAXCHILDREN; i++){
			  if( tree->child[i] != NULL )
				  printTree(tree->child[i]);
		  }*/
          break;
		case WhileK:
		  fprintf(listing, "While\n");
		  //printTree( tree->child[0] );
		  //printTree( tree->child[1] );
		  break;
		case ReturnK:
		  fprintf(listing, "Return\n");
		  //if( tree->child[0] != NULL )
			//  printTree( tree->child[0] );
		  break;
        case AssignK:
          fprintf(listing,"Op: =\n");
		  //printTree( tree->child[0] );
		  //printTree( tree->child[1] );
          break;
		case CompoundK:
          fprintf(listing,"Compound statement\n");
		  /*TreeNode *tmp = tree->child[0]; // Declaration Part in Compound statement 
		  while(tmp != NULL){
			  printTree(tmp);
			  tmp = tmp->sibling;
		  }
		  tmp = tree->child[1]; // Statemet_list Part in Compound statement 
		  while(tmp != NULL){
			  printTree(tmp);
			  tmp = tmp->sibling;
		  }*/
		  break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==ExpK)
    { switch (tree->kind.exp) {
        case OpK:
          fprintf(listing,"Op: ");
          printToken(tree->attr.op,"\0");
          break;
        case ConstK:
          fprintf(listing,"Const: %d\n",tree->val);
          break;
        case IdK:
          fprintf(listing,"ID: %s\n",tree->attr.name);
          break;
		case FuncCallK:
		  fprintf(listing, "Call procedure: %s\n", tree->attr.name);
		  //if( tree->child[0] != NULL )
			//  printTree(tree->child[0]);
		  break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else fprintf(listing,"Unknown node kind\n");

    for (i=0;i<MAXCHILDREN;i++)
		if(tree->child[i] != NULL)
			printTree(tree->child[i]);

    tree = tree->sibling;
  }
  UNINDENT;
}
