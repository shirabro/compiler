#include <stdio.h>
#include <stdlib.h>
#include "arch/cisc.h"

/* change to 0 for no debug info to be printed: */
#define DO_SHOW 1

int main(){
START_MACHINE;

JUMP(CONTINUE);

#include "arch/debug.h"
#include "arch/char.lib"
#include "arch/io.lib"
#include "arch/math.lib"
#include "arch/string.lib"
#include "arch/system.lib"
#include "arch/scheme.lib"
#include "arch/init.h"
#include "arch/errors.h"
#include "arch/primitives.h"
CONTINUE:
INIT_ENVIRONMENT;
const long a[]= { T_VOID, T_NIL, T_BOOL, 0, T_BOOL, 1, T_CLOSURE, 301858270, LABEL(PRIM_string_), T_CLOSURE, 301858270, LABEL(PRIM_vector_), T_CLOSURE, 301858270, LABEL(PRIM_symbol_), T_CLOSURE, 301858270, LABEL(PRIM_procedure_), T_CLOSURE, 301858270, LABEL(PRIM_pair_), T_CLOSURE, 301858270, LABEL(PRIM_number_), T_CLOSURE, 301858270, LABEL(PRIM_null_), T_CLOSURE, 301858270, LABEL(PRIM_integer_), T_CLOSURE, 301858270, LABEL(PRIM_char_), T_CLOSURE, 301858270, LABEL(PRIM_boolean_), T_CLOSURE, 301858270, LABEL(PRIM_cdr), T_CLOSURE, 301858270, LABEL(PRIM_car), T_CLOSURE, 301858270, LABEL(PRIM_cons), T_CLOSURE, 301858270, LABEL(PRIM_zero_), T_CLOSURE, 301858270, LABEL(PRIM_vector_length), T_CLOSURE, 301858270, LABEL(PRIM_set_car_), T_CLOSURE, 301858270, LABEL(PRIM_set_cdr_), T_CLOSURE, 301858270, LABEL(PRIM_string_length), T_CLOSURE, 301858270, LABEL(PRIM_make_string), T_CLOSURE, 301858270, LABEL(PRIM_char_Xinteger), T_CLOSURE, 301858270, LABEL(PRIM_integer_Xchar), T_CLOSURE, 301858270, LABEL(PRIM_make_vector), T_CLOSURE, 301858270, LABEL(PRIM_symbol_Xstring), T_CLOSURE, 301858270, LABEL(PRIM_binD), T_CLOSURE, 301858270, LABEL(PRIM_binM), T_CLOSURE, 301858270, LABEL(PRIM_bin_), T_CLOSURE, 301858270, LABEL(PRIM_binA), T_CLOSURE, 301858270, LABEL(PRIM_binE_), T_CLOSURE, 301858270, LABEL(PRIM_binx_), T_CLOSURE, 301858270, LABEL(PRIM_string_set_), T_CLOSURE, 301858270, LABEL(PRIM_vector_set_), T_CLOSURE, 301858270, LABEL(PRIM_remainder), T_CLOSURE, 301858270, LABEL(PRIM_string_ref), T_CLOSURE, 301858270, LABEL(PRIM_vector_ref), T_CLOSURE, 301858270, LABEL(PRIM_apply), T_CLOSURE, 301858270, LABEL(PRIM_string_Xsymbol), T_CLOSURE, 301858270, LABEL(PRIM_eq_), T_CLOSURE, 301858270, LABEL(PRIM_display), T_CLOSURE, 301858270, LABEL(PRIM_A), T_CLOSURE, 301858270, LABEL(PRIM__), T_CLOSURE, 301858270, LABEL(PRIM_D), T_CLOSURE, 301858270, LABEL(PRIM_M), T_CLOSURE, 301858270, LABEL(PRIM_E), T_CLOSURE, 301858270, LABEL(PRIM_x), T_CLOSURE, 301858270, LABEL(PRIM_X), T_CLOSURE, 301858270, LABEL(PRIM_list_), T_INTEGER, 1, T_INTEGER, 30};
memcpy(&(IND(10)),a,sizeof(a));
MOV(IND(0), IMM(158)); //next free address
INIT_TOP_LEVEL;
MOV(R0,SOB_VOID);
			//applic start
PUSH(SOB_NIL);
			//const-start
MOV(R0,156);
			//const-end
PUSH(R0);
PUSH(IMM(1));
			//closure code gen start
closure_simple_start1:

			//R1 <= malloc(|env|+1) new env
PUSH(2);
CALL(MALLOC);
DROP(1);
MOV(R1,R0);

			//R2 <= old env
MOV(R2, FPARG(0));

			//reserve registers
			//copy old env to new env
MOV(R10,IMM(0));
MOV(R11,IMM(1));
loop1_simple_start1:
CMP(R10,1);
JUMP_EQ(loop1_simple_end1);
MOV(INDD(R1,R11), INDD(R2,R10));
ADD(R10, IMM(1));
ADD(R11, IMM(1));
JUMP( loop1_simple_start1);
loop1_simple_end1:

			//R3 <= malloc(|n|); the new cell 
PUSH(FPARG(1));
CALL(MALLOC);
DROP(IMM(1));
MOV(R3,R0);
MOV(INDD(R1,0), R3);
			//copy parameters fro stack to be new bound variables
MOV(R10, IMM(0));
loop2_simple_start1:
CMP(R10, FPARG(1));
JUMP_EQ(loop2_simple_end1);
MOV(INDD(R3,R10), FPARG(2+R10));
ADD(R10,IMM(1));
JUMP( loop2_simple_start1);
loop2_simple_end1:

			//begin closure construction
PUSH(IMM(3));
CALL(MALLOC);
DROP(IMM(1));
MOV(INDD(R0,0), T_CLOSURE);
MOV(INDD(R0,1), R1);
MOV(INDD(R0,2), LABEL(closure_simple_code1));

			//restore register
			//finish closure construction
JUMP(closure_simple_exit1);
			//begin closure code
closure_simple_code1:
PUSH(FP);
MOV(FP, SP);
			//tc-applic start
PUSH(SOB_NIL);
			//const-start
MOV(R0,154);
			//const-end
PUSH(R0);
			//const-start
MOV(R0,154);
			//const-end
PUSH(R0);
MOV(R0,FPARG(2+0));
PUSH(R0);
PUSH(IMM(3));
MOV(R0, 130);

CMP(INDD(R0,0), T_CLOSURE);
JUMP_NE ( error_not_a_procedure );
PUSH (INDD(R0,1));
PUSH(FPARG(-1));//push the return address so that after overriding the frame there will be the ret 
MOV(R3,7);
MOV(R15,FPARG(-2));
MOV(R14,FPARG(1) + 2);
MOV(R2,0);	
shift_stack_loop_start1:
CMP(R2,R3);
JUMP_EQ(shift_stack_loop_end1);
MOV(FPARG(R14 - R2), STACK(SP -(R3-R2)));
INCR(R2);JUMP( shift_stack_loop_start1);
shift_stack_loop_end1:
MOV(SP,FP -3 -(R14 - R2));
MOV(FP , R15);
JUMPA(INDD(R0,2));
POP(FP);
RETURN
			//finish closure code
			//closure code gen end
closure_simple_exit1:

CMP(INDD(R0,0), T_CLOSURE);
JUMP_NE ( error_not_a_procedure );
PUSH(INDD(R0,1));
CALLA(INDD(R0,2));
DROP(STARG(0)+3);
			//applic end
PUSH(R0);
CALL(WRITE_SOB);
DROP(1);
STOP_MACHINE;
return 0;
}
