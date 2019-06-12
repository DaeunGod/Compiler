/****************************************************/
/* File: code.c                                     */
/* TM Code emitting utilities                       */
/* implementation for the TINY compiler             */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "code.h"

/* TM location number for current instruction emission */
static int emitLoc = 0;

/* Highest TM location emitted so far
   For use in conjunction with emitSkip,
   emitBackup, and emitRestore */
static int highEmitLoc = 0;

/* Procedure emitComment prints a comment line 
 * with comment c in the code file
 */
void emitComment(char *c)
{
  if (TraceCode)
    fprintf(code, "# %s\n", c);
}

/* Procedure emitRO emits a register-only
 * TM instruction
 * op = the opcode
 * r = target register
 * s = 1st source register
 * t = 2nd source register
 * c = a comment to be printed if TraceCode is TRUE
 */
void emitRO(char *op, int r, int s, int t, char *c)
{
  fprintf(code, "%3d:  %5s  %d,%d,%d ", emitLoc++, op, r, s, t);
  if (TraceCode)
    fprintf(code, "\t%s", c);
  fprintf(code, "\n");
  if (highEmitLoc < emitLoc)
    highEmitLoc = emitLoc;
} /* emitRO */

/* Procedure emitRM emits a register-to-memory
 * TM instruction
 * op = the opcode
 * r = target register
 * d = the offset
 * s = the base register
 * c = a comment to be printed if TraceCode is TRUE
 */
void emitRM(char *op, int r, int d, int s, char *c)
{
  fprintf(code, "%3d:  %5s  %d,%d(%d) ", emitLoc++, op, r, d, s);
  if (TraceCode)
    fprintf(code, "\t%s", c);
  fprintf(code, "\n");
  if (highEmitLoc < emitLoc)
    highEmitLoc = emitLoc;
} /* emitRM */

/* Function emitSkip skips "howMany" code
 * locations for later backpatch. It also
 * returns the current code position
 */
int emitSkip(int howMany)
{
  int i = emitLoc;
  emitLoc += howMany;
  if (highEmitLoc < emitLoc)
    highEmitLoc = emitLoc;
  return i;
} /* emitSkip */

/* Procedure emitBackup backs up to 
 * loc = a previously skipped location
 */
void emitBackup(int loc)
{
  if (loc > highEmitLoc)
    emitComment("BUG in emitBackup");
  emitLoc = loc;
} /* emitBackup */

/* Procedure emitRestore restores the current 
 * code position to the highest previously
 * unemitted position
 */
void emitRestore(void)
{
  emitLoc = highEmitLoc;
}

/* Procedure emitRM_Abs converts an absolute reference 
 * to a pc-relative reference when emitting a
 * register-to-memory TM instruction
 * op = the opcode
 * r = target register
 * a = the absolute location in memory
 * c = a comment to be printed if TraceCode is TRUE
 */
void emitRM_Abs(char *op, int r, int a, char *c)
{
  fprintf(code, "%3d:  %5s  %d,%d(%d) ",
          emitLoc, op, r, a - (emitLoc + 1), pc);
  ++emitLoc;
  if (TraceCode)
    fprintf(code, "\t%s", c);
  fprintf(code, "\n");
  if (highEmitLoc < emitLoc)
    highEmitLoc = emitLoc;
} /* emitRM_Abs */

void emitLabel(char *lab){
  fprintf(code, "%s:\n", lab);
}

void emitDirective(char* dir){
  fprintf(code, "\t%s\n", dir);
}

void emitDataDec(char* name, char* type, char* data){
  fprintf(code, "%s:\t%s\t%s\n", name, type, data);
}

void _emitWriteIntFunc(){
  emitLabel("WR_INT");
  //emitInst2param("la", "$a0", "outStr");
  //emitInst1param("jal", "WR_STR");
  /* Print Input message */
  emitInst2param("move", "$t0", "$a0");
  emitInst2param("la", "$a0", "outStr");
  emitInst3param("addi", "$v0", "$0", "4");
  fprintf(code, "\t%s\n", "syscall");
  emitInst2param("move", "$a0", "$t0");
  /***********************/
  fprintf(code, "\t%s\t%s,%s,%d ", "addi", "$v0", "$0", 1);
  emitComment("Print integer");
  fprintf(code, "\t%s\n", "syscall");
  emitInst2param("la", "$a0", "crlfz");
  emitInst3param("addi", "$v0", "$0", "4");
  fprintf(code, "\t%s\n", "syscall");
  fprintf(code, "\t%s\t%s ", "jr", "$ra");
  emitComment("Return");
}

void _emitWriteStrFunc(){
  emitLabel("WR_STR");
  emitInst3param("addi", "$v0", "$0", "4");
  fprintf(code, "\t%s\n", "syscall");
  emitInst1param("jr", "$ra");
}

void _emitReadFunc(){
  emitLabel("RD_INT");
  /* Print Input message */
  emitInst2param("la", "$a0", "inStr");
  emitInst3param("addi", "$v0", "$0", "4");
  fprintf(code, "\t%s\n", "syscall");
  /***********************/
  fprintf(code, "\t%s\t%s,%s,%d ", "addi", "$v0", "$0", 5);
  emitComment("Read integer");
  fprintf(code, "\t%s\n", "syscall");
  fprintf(code, "\t%s\t%s,%s,%s ", "add", "$a0", "$v0", "$0");
  emitComment("Move Integer into $a0");
  fprintf(code, "\t%s\t%s ", "jr", "$ra");
  emitComment("Return");
}

void emitInputOutputFuncs(){
  emitComment("##########################################");
  emitComment("FUNCTIONS: WR_STR, WR_INT, RD_INT");
  emitComment("WR_STR: print string");
  emitComment("WR_INT: print single integer");
  emitComment("RD_INT: read single integer");
  _emitWriteStrFunc();
  _emitWriteIntFunc();
  _emitReadFunc();
  emitComment("##########################################\n");
}


void emitInst3param(char* op, char* r, char* s, char* t){
  fprintf(code, "\t%s\t%s,%s,%s\n", op, r, s, t);
}

void emitInst2param(char* op, char* r, char* s){
  fprintf(code, "\t%s\t%s,%s\n", op, r, s);
}

void emitInst1param(char* op, char* r){
  fprintf(code, "\t%s\t%s\n", op, r);
}