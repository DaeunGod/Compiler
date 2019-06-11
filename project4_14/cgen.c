/****************************************************/
/* File: cgen.c                                     */
/* The code generator implementation                */
/* for the TINY compiler                            */
/* (generates code for the TM machine)              */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "code.h"
#include "cgen.h"

/* tmpOffset is the memory offset for temps
   It is decremented each time a temp is
   stored, and incremeted when loaded again
*/
static int tmpOffset = 0;

/* prototype for internal recursive code generator */
static void cGen(TreeNode *tree);

int _getLabelNumber();

/* Procedure genStmt generates code at a statement node */
static void genStmt(TreeNode *tree)
{
   TreeNode *p1, *p2, *p3;
   int savedLoc1, savedLoc2, currentLoc;
   int loc;
   switch (tree->kind.stmt)
   {
   case IfK:
   {
      int label1 = _getLabelNumber();
      int label2 = _getLabelNumber();
      char lab1[10] = {0};
      char lab2[10] = {0};
      sprintf(lab1, "L%d", label1);
      sprintf(lab2, "L%d", label2);

      cGen(tree->child[0]);  // expr
      emitInst2param("beqz", "$v0", lab1);
      cGen(tree->child[1]);  // compound1
      emitInst1param("j", lab2);
      emitLabel(lab1);
      cGen(tree->child[2]);  // else compound
      emitLabel(lab2);
      break; /* if_k */
   }
   case WhileK:
   {
      int label1 = _getLabelNumber();
      int label2 = _getLabelNumber();
      char lab1[10] = {0};
      char lab2[10] = {0};
      sprintf(lab1, "L%d", label1);
      sprintf(lab2, "L%d", label2);

      emitLabel(lab1);
      cGen(tree->child[0]);
      emitInst2param("bnez", "$v0", lab2);
      cGen(tree->child[1]);
      emitInst1param("j", lab1);
      emitLabel(lab2);
      break; /* while */
   }
   case AssignK:
      break; /* assign_k */

   case ReturnK:
   {
      cGen(tree->child[0]);
      break;
   }

   case CompoundK:
      /* generate code for expression to write */
      cGen(tree->child[0]);
      cGen(tree->child[1]);
      /* now output it */
      break;

   default:
      break;
   }
} /* genStmt */

/* Procedure genExp generates code at an expression node */
static void genExp(TreeNode *tree)
{
   int loc;
   TreeNode *p1, *p2;
   switch (tree->kind.exp)
   {
   case OpK:
   {
      cGen(tree->child[0]);
      cGen(tree->child[1]);
      break; /* OpK */
   }
   case ConstK:
   {
      char val[10]={0};
      sprintf(val, "%d", tree->val);
      emitInst2param("li", "$v0", val);
      break; /* ConstK */
   }
   case IdK:
      break; /* IdK */

   case FuncCallK:
      break; /* FuncCallK */

   case InputCallK:{
      char regi[10]={0};
      sprintf(regi, "%d($fp)", tree->child[0]->info->memloc);
      emitInst1param("jal", "RD_INT");
      emitInst2param("sw", "$a0", regi);
      break; /* InputCallK */
   }

   case OutputCallK:{
      char regi[10]={0};
      sprintf(regi, "%d($fp)", tree->child[0]->info->memloc);
      emitInst2param("lw", "$a0", regi);
      emitInst1param("jal", "WR_INT");
      break; /* OutputCallK */
   }
   default:
      break;
   }
} /* genExp */

static int addedMemLoc = 0;

static void genDec(TreeNode *tree)
{
   if (tree != NULL)
   {
      switch (tree->kind.dec)
      {
      case FunctionK:
      {
         char addedMem[10]={0};
         emitComment("Function Dec");
         emitLabel(tree->attr.name);

         //    sw      $ra,0($sp)  #Push return address
         //   addiu   $sp,$sp,-4  # onto stack
         //   sw      $a0,0($sp)  #Push $a0
         //   addiu   $sp,$sp,-4  # onto stack
         //   la      $a0,crlfz   #Point to new line string
         //   jal     wr_str      #Output CRLF to console
         //   addiu   $sp,$sp,4   #Pop $a0
         //   lw      $a0,0($sp)  # from stack
         //   addiu   $sp,$sp,4   #Pop return address
         //   lw      $ra,0($sp)  # from stack
         //   jr      $ra         #Return

         emitComment("\tSave registers");
         emitInst3param("subu", "$sp", "$sp", "32"); //Stack frame is 32 bytes long
         emitInst2param("sw", "$ra", "8($sp)");     //Save retrun address
         emitInst2param("sw", "$fp", "0($sp)");     //Save frame pointer
         emitInst3param("addu", "$fp", "$sp", "0"); //Set up frame pointer
         emitComment("");

         cGen(tree->child[1]); // Compound Stmt.

         /* print single integer
         emitInst2param("la", "$a0", "10");
         emitInst1param("jal", "WR_INT"); */

         sprintf(addedMem, "%d", addedMemLoc);
         emitInst3param("addu", "$sp", "$sp", addedMem);
         emitComment("");
         emitComment("\tRestore registers");
         emitInst2param("lw", "$ra", "8($sp)");     // Restore return address
         emitInst2param("lw", "$fp", "0($sp)");     // Restore frame pointer
         emitInst3param("addu", "$sp", "$sp", "32"); // Pop stack frame
         emitInst1param("jr", "$ra");                 // Return to caller
         break;
      }

      case SimpleK:
      {
         //char regi[10]={0};
         //sprintf(regi, "%d", tree->info->memloc);
         addedMemLoc += 4;
         // emitInst2param("sw", "$0", regi);
         emitInst3param("subu", "$sp", "$sp", "4");
         break;
      }
      case ArrayK:
         break;
      case ParamK:
      {
      }
      break;
      default:
         break;
      }
   }
} /* genDec */

/* Procedure cGen recursively generates code by
 * tree traversal
 */
static void cGen(TreeNode *tree)
{
   if (tree != NULL)
   {
      switch (tree->nodekind)
      {
      case StmtK:
         genStmt(tree);
         break;
      case ExpK:
         genExp(tree);
         break;
      case DeclarationK:
         genDec(tree);
         break;
      default:
         break;
      }
      cGen(tree->sibling);
   }
}

/**********************************************/
/* the primary function of the code generator */
/**********************************************/
/* Procedure codeGen generates code to a code
 * file by traversal of the syntax tree. The
 * second parameter (codefile) is the file name
 * of the code file, and is used to print the
 * file name as a comment in the code file
 */
void codeGen(TreeNode *syntaxTree, char *codefile)
{
   char *s = malloc(strlen(codefile) + 7);
   strcpy(s, "File: ");
   strcat(s, codefile);
   emitComment("C- Compilation to TM Code");
   emitComment(s);
   emitComment("##########################################");
   emitDirective(".data");
   emitDataDec("inStr", ".asciiz", "\"Enter value for input instruction: \"");
   emitDataDec("OutStr", ".asciiz", "\"output instruction prints: \"");
   emitDataDec("crlfz", ".ascii", "\"\\n\"");
   emitDirective(".text");
   emitDirective(".globl main\n");

   emitInputOutputFuncs();
   
   cGen(syntaxTree);
}

int _getLabelNumber(){
   static int labelNum = 0;
   return labelNum++;
}