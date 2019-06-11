# conio - console input and output
        .data
a0wrds: .word   1,2,3,0     #Words pointed to by $a0

tst:    .asciiz "Input an integer. \n"
done:   .asciiz "\n Program Terminated \n"
chrmsg: .asciiz "Input a character to be converted to upper case or press Esc key.\n"
TEMP:   .space  256         #Reserve 256 bytes
        .text               #Code goes in text segment
        .globl  main        
##################################################
main:
        sw      $ra,0($sp)  #Push return address
        addiu   $sp,$sp,-4  # onto stack
#
loop:   la      $a0,chrmsg  #Point $a0 to message
        jal     wr_str      #Output request for a character
        jal     rd_chr      #Get character
        jal     crlf        #Go to new line
        addi    $t0,$0,0x1b #Put escape char in $t0
        beq     $a0,$t0,doint #Go to next if escape
        jal     UPPER       #Convert character to upper case
        jal     WR_CHR      #Output upper case character
        jal     crlf        #Go to new line
        j       loop
#
doint:  la      $a0,tst     #Use pseudoinstruction
        jal     wr_str      #OUTPUT TEST STRING TO CONSOLE
        jal     RD_INT      #Read integer
        jal     crlf
        jal     WR_INT      #Output integer
        la      $a0,done    #Point $a0 to done message
        jal     wr_str      #Output done message
#
        addiu   $sp,$sp,4   #Pop return address
        lw      $ra,0($sp)  # from stack
        jr      $ra         #Return              

###############################################################
# 
# FUNCTION: wr_str - OUTPUT 0 TERMINATED STRING TO CONSOLE
#    INPUT: $A0 - POINTER TO STRING
#   OUTPUT: NONE
#    CALLS: SYSCALL
# DESTROYS: $V0
#
###############################################################
wr_str:     
        addi    $v0,$0,4    #PRINT STRING REQUEST CODE
        syscall
        jr      $ra         #Return
###############################################################
# 
# FUNCTION: crlf - OUTPUT 0 TERMINATED STRING TO CONSOLE
#    INPUT: NONE
#   OUTPUT: NONE
#    CALLS: wr_str
# DESTROYS: $A0, $V0
#
###############################################################
        .data
crlfz:  .ascii  "\n" 
        .text       
crlf:
        sw      $ra,0($sp)  #Push return address
        addiu   $sp,$sp,-4  # onto stack
        sw      $a0,0($sp)  #Push $a0 
        addiu   $sp,$sp,-4  # onto stack
        la      $a0,crlfz   #Point to new line string
        jal     wr_str      #Output CRLF to console
        addiu   $sp,$sp,4   #Pop $a0
        lw      $a0,0($sp)  # from stack
        addiu   $sp,$sp,4   #Pop return address
        lw      $ra,0($sp)  # from stack
        jr      $ra         #Return              

 
###############################################################
# 
# FUNCTION: RD_INT - READ INTEGER FROM KEYBOARD
#    INPUT: NONE
#   OUTPUT: $a0 - integer read from console
#    CALLS: SYSCALL
# DESTROYS: $v0
#
###############################################################
RD_INT:     
        addi    $v0,$0,5    #Read integer request code
        syscall
        add     $a0,$v0,$0  #Move integer into $a0
        jr      $ra         #Return
###############################################################
# 
# FUNCTION: WR_INT - Otput integer to console
#    INPUT: $a0 - integer
#   OUTPUT: NONE
#    CALLS: SYSCALL
# DESTROYS: $v0
#
###############################################################
WR_INT:     
        addi    $v0,$0,1    #Print integer request code
        syscall
        jr      $ra         #Return
###############################################################
# FUNCTION: rd_chr - READ Character from KEYBOARD
#    INPUT: NONE
#   OUTPUT: $a0 - Character read from console
#    CALLS: SYSCALL
# DESTROYS: $v0
###############################################################
rd_chr:     
        addi    $v0,$0,12   #Read char request code
        syscall
        add     $a0,$v0,$0  #Move character in $v0 to $a0
        jr      $ra         #Return
 
###############################################################
# FUNCTION: WR_CHR - Output character to console
#    INPUT: NONE
#   OUTPUT: $a0 - Character to output to console
#    CALLS: SYSCALL
# DESTROYS: $v0
###############################################################
WR_CHR:     
        addi    $v0,$0,11   #Print character request code
        syscall
        jr      $ra         #Return
        
###############################################################
# FUNCTION: WR_HEX - Otput integer in Hex to console
#    INPUT: $a0 - integer
#   OUTPUT: NONE
#    CALLS: SYSCALL
# DESTROYS: $v0
###############################################################
WR_HEX: 
            
        addi    $v0,$0,1    #Print integer request code
        syscall
        jr      $ra         #Return

 
###########################################################
# FUNCTION: UPPER - IF ASCII character (see Fig 3.15) in $a0
#           is between 'a' and 'z' convert to upper case
#           else $a0 is unchanged.
#           Note: A lower case ASCII character can be 
#           converted to upeercase by subtracting 32.
#   INPUTS: $a0 - Contains 8 bit ASCII character in least
#           significant byte. High order bytes are 0.
#  OUTPUTS: $a0 - Contains input ASCII character converted
#           to upper case.
# DESTROYS: $a0, $s0
###########################################################
#
UPPER:
        slti    $s0,$a0,'a' #Compare input char with 'a'
        bgtz    $s0,Done    #Exit if less than 'a'
        slti    $s0,$a0,'z'+1 #Compare input char with 'z'
        blez    $s0,Done    #Exit if greater than 'z'
        addi    $a0,-32     #Convert char to upper case.
Done:   jr      $ra         #Return
        .data
