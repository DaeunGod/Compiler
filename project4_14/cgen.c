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
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"

/* tmpOffset is the memory offset for temps
   It is decremented each time a temp is
   stored, and incremeted when loaded again
*/
static int tmpOffset = 0;
static int gsize=0; // global area size
static int returnLocLabel = 0;

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
   case IfK :
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
         if(tree->child[2])
         {
            emitInst1param("j", lab2);
            emitLabel(lab1);
            cGen(tree->child[2]);  // else compound
            emitLabel(lab2);
         }
         else
         {
            emitLabel(lab1);
         }
      }
      break; /* if_k */
   
   case WhileK:
      {
      emitComment("WhileK");
      int label1 = _getLabelNumber();
      int label2 = _getLabelNumber();
      char lab1[10] = {0};
      char lab2[10] = {0};
      sprintf(lab1, "L%d", label1);
      sprintf(lab2, "L%d", label2);

      emitLabel(lab1);
      cGen(tree->child[0]);
      emitInst2param("beqz", "$v0", lab2);
      cGen(tree->child[1]);
      emitInst1param("j", lab1);
      emitLabel(lab2);
      }
      break; /* while */
   
   case AssignK:
      {
      /*mem[v0] = v1;*/
      emitComment("AssignK");
      cGen(tree->child[0]);
      emitInst3param("subu", "$sp", "$sp", "4"); 
      emitInst2param("sw", "$v1", "0($sp)");    
       
      cGen(tree->child[1]);
      emitInst2param("lw", "$t1", "0($sp)");
//      emitInst2param("lw", "$v1", "0($sp)");
      emitInst3param("addu", "$sp", "$sp", "4"); 
      emitInst2param("sw", "$v0", "0($t1)"); 
      emitComment("");    
      }
      break; /* assign_k */
   
   case ReturnK:
      {
      char returnLocLab[10] = {0};
      sprintf(returnLocLab, "RET%d", returnLocLabel);
      cGen(tree->child[0]);
      emitInst1param("j", returnLocLab);
      /* 함수 마지막으로 점프 시켜줘야함 */
      //emitInst2param("move", "$sp", "$fp");
      //emitInst2param("lw", "$ra", "-8($sp)");
      //emitInst2param("lw", "$fp", "0($sp)");
      //emitInst3param("subu", "$sp", "$sp", "24"); 
      
      //emitInst1param("jr", "$ra");

      }
      break;
   

   case CompoundK:
      {
      char addedMem[10]={0};
      int statementsize=0;
      /* generate code for expression to write */
      cGen(tree->child[0]);
      statementsize=getdeclsize();
      cGen(tree->child[1]);
      //sprintf(addedMem, "%d", statementsize);
      //emitInst3param("subu", "$sp", "$sp", addedMem);
      /* now output it */
      }
      break;

   default:
      break;
   /* genStmt */
   }
}
/* Procedure genExp generates code at an expression node */
static void genExp(TreeNode *tree)
{
   int loc;
   TreeNode *p1, *p2;
   switch (tree->kind.exp)
   {
   case OpK:
      {
      emitComment("OpK");
      cGen(tree->child[0]);
      emitInst3param("subu", "$sp", "$sp", "4");
      emitInst2param("sw", "$v0", "0($sp)");     
      //emitInst2param("move", "$t1", "$v0");
      cGen(tree->child[1]);
      emitInst2param("lw", "$t1", "0($sp)");     
      emitInst3param("addu", "$sp", "$sp", "4");

      switch(tree->attr.op)
      {
         case PLUS:
         emitInst3param("add", "$v0", "$t1", "$v0"); 
         break;
         case MINUS:
         emitInst3param("sub", "$v0", "$t1", "$v0"); 
         break;
         case TIMES:
         emitInst3param("mul", "$v0", "$t1", "$v0"); 
         break;
         case OVER:
         emitInst3param("div", "$v0", "$t1", "$v0"); 
         break;
         case LTET:
         emitInst3param("sle", "$v0", "$t1", "$v0");       
         break;
         case LT:
         emitInst3param("slt", "$v0", "$t1", "$v0");
         break;
         case GTET:
         emitInst3param("sge", "$v0", "$t1", "$v0");
         break;
         case GT:
         emitInst3param("sgt", "$v0", "$t1", "$v0");
         break;
         case EQ:
         emitInst3param("seq", "$v0", "$t1", "$v0");
         break;
         case NOTEQ:
         emitInst3param("sne", "$v0", "$t1", "$v0");
         break;         
      } 
      }
      break; /* OpK */
   
   case ConstK:
   {
      char val[10]={0};
      emitComment("ConstK");
      sprintf(val, "%d", tree->val);
      emitInst2param("li", "$v0", val);
   } 
      break; /* ConstK */
   
   case IdK:
   {
      char offset[10]={0};
      emitComment("IdK");
      if(tree->child[0])
      {
         if(!(tree->info->isGlobal)){
            sprintf(offset, "%d($fp)",tree->info->memloc);
            emitInst2param("lw", "$v0", offset);
            emitInst2param("la", "$v1", offset);

            emitInst3param("subu", "$sp", "$sp", "$8");
             emitInst2param("sd", "$v1", "0($sp)");
             cGen(tree->child[0]); // index -> $v0
             emitInst2param("ld", "$v1","0($sp)" );
             emitInst3param("addu", "$sp", "$sp", "$8");

             emitInst3param("mulou", "$v0", "$v0", "4");
             
             emitInst3param("add", "$v1", "$v1", "$v0");
             emitInst2param("lw", "$v0", "0($v1)");
            //emitInst2param("li", "$t0", "4");
            //emitInst3param("add", "$t0", "$t0", "4");
            //emitInst2param("move", "$v1", "$t0");
            //emitInst2param("lw", "$v0", "0($v1)");
         }
         else{
            sprintf(offset, "%d($gp)",tree->info->memloc);
            emitInst2param("lw", "$v0", offset);
            emitInst2param("la", "$v1", offset);

            sprintf(offset, "%d($gp)",(gsize+4));
            emitInst3param("subu", "$sp", "$sp", "$8");
            emitInst2param("sd", "$v1", offset);
            cGen(tree->child[0]); // index -> $v0
            emitInst2param("ld", "$v1",offset);
            emitInst3param("addu", "$sp", "$sp", "$8");

             sprintf(offset, "%d",tree->info->ArraySize-1);
              emitInst3param("addu", "$t0", "$0", offset);
              emitInst3param("subu", "$t0", "$t0", "$v0");
              emitInst3param("mulou", "$t0", "$t0", "4");
             
              emitInst3param("sub", "$v1", "$v1", "$t0");
              emitInst2param("lw", "$v0", "0($v1)");            
         }
      }
      else
      {
         if(!(tree->info->isGlobal))
         {
               sprintf(offset, "%d($fp)",tree->info->memloc);
               emitInst2param("lw", "$v0", offset);
               emitInst2param("la", "$v1", offset);

         } else {
            sprintf(offset, "%d($gp)",tree->info->memloc);
            emitInst2param("lw", "$v0", offset);
            emitInst2param("la", "$v1", offset);
         }
      }
   }
      break; /* IdK */

   case FuncCallK:
      {
         TreeNode *par;
         int parcount=0;
         char siz[10]={0};
         emitComment("FuncCallK");
         for(par=tree->child[0];par!=NULL;par=par->sibling)
         {
            char param[10]={0};
             //emitInst3param("subu", "$sp", "$sp", "$4");
             genExp(par);
             //emitInst2param("sw", "$v0", "0($sp)");
             sprintf(param, "$a%d", parcount);
             emitInst2param("move", param, "$v0");
             parcount++;
         }
         emitInst1param("jal", tree->attr.name);
         //if( parcount != 0 ){
          //  sprintf(siz, "%d", parcount*4);
          //  emitInst3param("addu", "$sp", "$sp", siz);
         //}
      }
      
      break; /* FuncCallK */
      
   case InputCallK:
   {
      char regi[10]={0};
      // if( tree->child[0]->info->memloc < 0 )
      //    sprintf(regi, "%d($fp)", tree->child[0]->info->memloc);
      // else
      //    sprintf(regi, "%d($gp)", tree->child[0]->info->memloc);
      cGen(tree->child[0]);
      emitInst1param("jal", "RD_INT");
      emitInst2param("sw", "$a0", "0($v1)"); //"sw", "$a0", "-4($fp)"
   }
         break; /* InputCallK */
   

   case OutputCallK:
   {
      char regi[10]={0};
      // if( tree->child[0]->info->memloc < 0 )
      //    sprintf(regi, "%d($fp)", tree->child[0]->info->memloc);
      // else
      //    sprintf(regi, "%d($gp)", tree->child[0]->info->memloc);
      cGen(tree->child[0]);
      emitInst2param("move", "$a0", "$v0");
      emitInst1param("jal", "WR_INT");
      break; /* OutputCallK */
   }
   default:
      break;
   }
} /* genExp */

static int addedMemLoc = 0;
static int paramNum = 0;
static int paramCount = 0;
static void genDec(TreeNode *tree)
{
   if (tree != NULL)
   {
      switch (tree->kind.dec)
      {
      case FunctionK:
      {
         char addedMem[10]={0};
         char returnLocLab[10] = {0};
         TreeNode *par=NULL;
         returnLocLabel = _getLabelNumber();
         sprintf(returnLocLab, "RET%d", returnLocLabel);

         emitComment("#Function Dec");
         emitLabel(tree->attr.name);

         emitComment("\t#Save registers");
         emitInst3param("subu", "$sp", "$sp", "24"); //Stack frame is 32 bytes long
         emitInst2param("sw", "$ra", "0($sp)");     //Save retrun address
         emitInst2param("sw", "$fp", "4($sp)");     //Save frame pointer(control link)
         emitInst3param("addu", "$fp", "$sp", "4"); //Set up frame pointer
         
         emitComment("");

         paramNum = 0;
         paramCount = 0;
         for(par=tree->child[0];par!=NULL;par=par->sibling)
            paramCount++;
         
         cGen(tree->child[0]); // Parameter decl.
         cGen(tree->child[1]); // Compound Stmt.

         /* print single integer
         emitInst2param("la", "$a0", "10");
         emitInst1param("jal", "WR_INT"); */

         emitLabel(returnLocLab);
         //sprintf(addedMem, "%d", addedMemLoc);
         //emitInst3param("addu", "$sp", "$sp", addedMem);
         emitInst2param("move", "$sp", "$fp");
         emitInst3param("subu", "$sp", "$sp", "4");
         emitComment("");
         emitComment("\t#Restore registers");
         emitInst2param("lw", "$ra", "0($sp)");     // Restore return address
         emitInst2param("lw", "$fp", "4($sp)");     // Restore frame pointer
         emitInst3param("addu", "$sp", "$sp", "24"); // Pop stack frame
         emitInst1param("jr", "$ra");                 // Return to caller
      }
        break;
      

      case SimpleK:
      {
         //char regi[10]={0};
         //sprintf(regi, "%d", tree->info->memloc);
         if( tree->info->memloc < 0 ){
            /* local variable */
            addedMemLoc += 4;
            // emitInst2param("sw", "$0", regi);
            emitInst3param("subu", "$sp", "$sp", "4");
         } else {
            /* global variable */
         }
      }
         break;
      case ArrayK:
      {
         char s[10]={0};
         int size;
         size = 4 * tree->val;
         if( tree->info->memloc < 0 ){
            /* local variable */
            addedMemLoc += size;
            sprintf(s, "%d", size);
            emitInst3param("subu", "$sp", "$sp", s);
         } else {
            /* global variable */
         }
      }
         break;
      
      case ParamK:{
         char args[10]={0};
         char dest[10]={0};
         emitComment("#PARAM Dec");
         sprintf(args, "$a%d", paramNum);
         sprintf(dest, "%d($fp)", (paramCount*4)-(paramNum*4));
         emitInst2param("sw", args, dest);     //Save arg0
         //cGen(tree->sibling);
         paramNum++;
         break;
      }
/*         TreeNode *param;
         for(param=tree; param!=NULL; param= param->next)
         {
               switch(param->expType)
               {
                  case Integer:
                  declsize=4;
                  break;
                  case Array:
                  declsize=4;
               }
            

         }
         int base = 8;
         char regi[10]={0};
         char pos[10] = {0};
         sprintf(regi, "$a%d", paramCount);
         sprintf(pos, "%d($fp)", base+tree->info->memloc);
         emitInst2param("sw", regi, pos);
         paramCount++;
         break;
      
*/
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
   char si[10]={0};         
   TreeNode* t;
   
   strcpy(s, "File: ");
   strcat(s, codefile);
   emitComment("C- Compilation to TM Code");
   emitComment(s);
   emitComment("##########################################");
   
   emitDirective(".data");
   emitDataDec("inStr", ".asciiz", "\"Enter value for input instruction: \"");
   emitDataDec("outStr", ".asciiz", "\"output instruction prints: \"");
   emitDataDec("crlfz", ".ascii", "\"\\n\"");
   emitDirective(".text");
   emitDirective(".globl main\n");

   emitInputOutputFuncs();

   for(t=syntaxTree; t!=NULL;t=t->sibling)
   {
      if(t->info->memloc>0)
      {
         if(t->kind.dec==SimpleK)
         {
            gsize+=4;
         }
         else if(t->kind.dec == ArrayK)
         {
            gsize+=4*(t->val);
         }  
      }
   }
   
   sprintf(si, "%d", gsize);
   emitInst3param("subu", "$gp", "$gp", si);
   emitInst3param("subu", "$sp", "$gp", "0");
   emitInst3param("subu", "$fp", "$gp", "0");

   cGen(syntaxTree);
}

int _getLabelNumber(){
   static int labelNum = 0;
   return labelNum++;
}
int getdeclsize()
{
   return addedMemLoc;
}