PRIM_procedure_:
	PUSH(FP);					
	MOV(FP,SP);					
	PUSH(R1);					
	MOV(R1,FPARG(1));
	CMP(R1,IMM(1));				
	JUMP_NE(error_incorrect_amount_args);	
	MOV(R1,FPARG(2));			
	MOV(R0,SOB_BOOLEAN_FALSE);	
	CMP(IND(R1),T_CLOSURE);			
	JUMP_NE(exit_type_check);				
	MOV(R0,SOB_BOOLEAN_TRUE);	
	JUMP(exit_type_check);				
	exit_type_check:							
	POP(R1);					
	POP(FP);					
	RETURN;						
	
PRIM_vector_:
	PUSH(FP);					
	MOV(FP,SP);					
	PUSH(R1);					
	MOV(R1,FPARG(1));
	CMP(R1,IMM(1));				
	JUMP_NE(error_incorrect_amount_args);	
	MOV(R1,FPARG(2));			
	MOV(R0,SOB_BOOLEAN_FALSE);	
	CMP(IND(R1),T_VECTOR);			
	JUMP_NE(exit_type_check);				
	MOV(R0,SOB_BOOLEAN_TRUE);	
	JUMP(exit_type_check);		
	
PRIM_symbol_:
	PUSH(FP);					
	MOV(FP,SP);					
	PUSH(R1);					
	MOV(R1,FPARG(1));
	CMP(R1,IMM(1));				
	JUMP_NE(error_incorrect_amount_args);	
	MOV(R1,FPARG(2));			
	MOV(R0,SOB_BOOLEAN_FALSE);	
	CMP(IND(R1),T_SYMBOL);			
	JUMP_NE(exit_type_check);				
	MOV(R0,SOB_BOOLEAN_TRUE);	
	JUMP(exit_type_check);	

PRIM_string_:
	PUSH(FP);					
	MOV(FP,SP);					
	PUSH(R1);					
	MOV(R1,FPARG(1));
	CMP(R1,IMM(1));				
	JUMP_NE(error_incorrect_amount_args);	
	MOV(R1,FPARG(2));			
	MOV(R0,SOB_BOOLEAN_FALSE);	
	CMP(IND(R1),T_STRING);			
	JUMP_NE(exit_type_check);				
	MOV(R0,SOB_BOOLEAN_TRUE);	
	JUMP(exit_type_check);	

PRIM_char_:
	PUSH(FP);					
	MOV(FP,SP);					
	PUSH(R1);					
	MOV(R1,FPARG(1));
	CMP(R1,IMM(1));				
	JUMP_NE(error_incorrect_amount_args);	
	MOV(R1,FPARG(2));			
	MOV(R0,SOB_BOOLEAN_FALSE);	
	CMP(IND(R1),T_CHAR);			
	JUMP_NE(exit_type_check);				
	MOV(R0,SOB_BOOLEAN_TRUE);	
	JUMP(exit_type_check);	
	
PRIM_integer_:
	PUSH(FP);					
	MOV(FP,SP);					
	PUSH(R1);					
	MOV(R1,FPARG(1));
	CMP(R1,IMM(1));				
	JUMP_NE(error_incorrect_amount_args);	
	MOV(R1,FPARG(2));			
	MOV(R0,SOB_BOOLEAN_FALSE);	
	CMP(IND(R1),T_INTEGER);			
	JUMP_NE(exit_type_check);				
	MOV(R0,SOB_BOOLEAN_TRUE);	
	JUMP(exit_type_check);	

PRIM_number_:
	PUSH(FP);					
	MOV(FP,SP);					
	PUSH(R1);					
	MOV(R1,FPARG(1));
	CMP(R1,IMM(1));				
	JUMP_NE(error_incorrect_amount_args);	
	MOV(R1,FPARG(2));			
	MOV(R0,SOB_BOOLEAN_FALSE);	
	CMP(IND(R1),T_INTEGER);			
	JUMP_NE(exit_type_check);				
	MOV(R0,SOB_BOOLEAN_TRUE);	
	JUMP(exit_type_check);	
	
PRIM_boolean_:
	PUSH(FP);					
	MOV(FP,SP);					
	PUSH(R1);					
	MOV(R1,FPARG(1));
	CMP(R1,IMM(1));				
	JUMP_NE(error_incorrect_amount_args);	
	MOV(R1,FPARG(2));			
	MOV(R0,SOB_BOOLEAN_FALSE);	
	CMP(IND(R1),T_BOOL);			
	JUMP_NE(exit_type_check);				
	MOV(R0,SOB_BOOLEAN_TRUE);	
	JUMP(exit_type_check);	

PRIM_pair_:
	PUSH(FP);					
	MOV(FP,SP);					
	PUSH(R1);					
	MOV(R1,FPARG(1));
	CMP(R1,IMM(1));				
	JUMP_NE(error_incorrect_amount_args);	
	MOV(R1,FPARG(2));			
	MOV(R0,SOB_BOOLEAN_FALSE);	
	CMP(IND(R1),T_PAIR);			
	JUMP_NE(exit_type_check);				
	MOV(R0,SOB_BOOLEAN_TRUE);	
	JUMP(exit_type_check);	
	
PRIM_list_:
	PUSH(FP);					
	MOV(FP,SP);						
	CMP(FPARG(1),IMM(1));		
	JUMP_NE(error_incorrect_amount_args);	
	PUSH(R1);						
	MOV(R1, FPARG(2));	
//NULL? => TRUE
	CMP(R1, SOB_NIL);
	JUMP_EQ(is_null);
	JUMP(is_not_null);
is_null:

	MOV(R0,SOB_BOOLEAN_TRUE);
	JUMP(exit_type_check);
is_not_null:

	CMP(INDD(R1,0), T_PAIR);
	JUMP_NE(is_not_pair);
	JUMP(is_pair);
is_not_pair:

	MOV(R0,SOB_BOOLEAN_FALSE);
	JUMP(exit_type_check);
is_pair:

	PUSH(INDD(R1,2));
	PUSH(1);
	PUSH(301858270);
	CALL(PRIM_list_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_EQ(is_list);
	JUMP(is_not_list);
is_list:

	MOV(R0,SOB_BOOLEAN_TRUE);
	JUMP(exit_type_check);
is_not_list:

	MOV(R0,SOB_BOOLEAN_FALSE);
	JUMP(exit_type_check);
	
	
PRIM_null_:
	PUSH(FP);					
	MOV(FP,SP);					
	CMP(FPARG(1),IMM(1));
	//printStack(machine, 15);
	JUMP_NE(error_incorrect_amount_args);		
	PUSH(R1);			
	MOV(R1,FPARG(2));			
	MOV(R0,SOB_BOOLEAN_FALSE);	
	CMP(IND(R1),T_NIL);			
	JUMP_NE(exit_type_check);				
	MOV(R0,SOB_BOOLEAN_TRUE);	
	JUMP(exit_type_check);	

PRIM_cons:
	PUSH(FP);
	MOV(FP, SP);
	CMP(FPARG(1),IMM(2));
	JUMP_NE(error_incorrect_amount_args);
	PUSH(FPARG(3));
	PUSH(FPARG(2));
	CALL(MAKE_SOB_PAIR);
	DROP(2);
	POP(FP);
	RETURN;
	
PRIM_car:
	PUSH(FP);
	MOV(FP, SP);
	CMP(FPARG(1),IMM(1));
	JUMP_NE(error_incorrect_amount_args);	
	PUSH(R1);
	MOV(R1,FPARG(2));
	
	//printf("doing car for the arg: %ld\n", IND(R1));
	
	//is pair?
	PUSH(R1);
	PUSH(1);
	PUSH(301858270);
	CALL(PRIM_pair_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	//printf("car: is pair -before check?\n");
	JUMP_NE(error_not_a_pair);	
	//printf("car: is pair -after check?\n");
	MOV(R0,INDD(R1,1));
	POP(R1);
	POP(FP);	
	RETURN;
		
PRIM_cdr:
	PUSH(FP);
	MOV(FP, SP);
	CMP(FPARG(1),IMM(1));
	JUMP_NE(error_incorrect_amount_args);	
	PUSH(R1);
	MOV(R1,FPARG(2));
	//is pair?
	PUSH(R1);
	PUSH(1)
	PUSH(301858270);
	CALL(PRIM_pair_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	//printf("cdr: is pair -before check?\n");
	JUMP_NE(error_not_a_pair);	
	//printf("cdr: is pair -after check?\n");
	MOV(R0,INDD(R1,2));
	POP(R1);
	POP(FP);	
	RETURN;
	
PRIM_zero_:
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(1));
	JUMP_NE(error_incorrect_amount_args);	
	PUSH(R2);
	MOV(R2,SOB_BOOLEAN_FALSE);
	PUSH(R1);
	MOV(R1,FPARG(2));
	//IS INTEGER?		
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE(is_not_zero);
	CMP(INDD(R1, 1), IMM(0));	
	JUMP_NE(is_not_zero);	
	MOV(R2,SOB_BOOLEAN_TRUE);
is_not_zero:		
	MOV(R0,R2);
	POP(R1);
	POP(R2);
	POP(FP);
	RETURN;
	
PRIM_vector_length:
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(1));
	JUMP_NE(error_incorrect_amount_args);	
	PUSH(R1); //ARG
	MOV(R1, FPARG(2));	
	//IS VECTOR?
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_vector_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE(error_not_a_vector);
	MOV(R0,INDD(R1,1));
	PUSH(R0);
	CALL(MAKE_SOB_INTEGER);
	DROP(1);
exit_vector_length:
	POP(R1);
	POP(FP);	
	RETURN;
	
PRIM_set_car_:
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(2));
	JUMP_NE(error_incorrect_amount_args);	
	PUSH(R1);
	PUSH(R2);
	
	MOV(R1,FPARG(2));  // the pair
	MOV(R2,FPARG(3)); // the new value
	//IS PAIR?
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_pair_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE(error_not_a_pair);
	MOV(INDD(R1,1),R2); ;//set the new car 
	MOV(R0,SOB_VOID);
	POP(R2);
	POP(R1);
	POP(FP);
	RETURN;
	
PRIM_set_cdr_:
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(2));
	JUMP_NE(error_incorrect_amount_args);	
	PUSH(R1);
	PUSH(R2);
	
	MOV(R1,FPARG(2));  // the pair
	MOV(R2,FPARG(3)); // the new value
	//IS PAIR?
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_pair_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE(error_not_a_pair);
	MOV(INDD(R1,2),R2); ;//set the new car 
	MOV(R0,SOB_VOID);
	POP(R2);
	POP(R1);
	POP(FP);
	RETURN;
	

PRIM_string_length:
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(1));
	JUMP_NE(error_incorrect_amount_args);	
	PUSH(R1);
	
	MOV(R1,FPARG(2));  // the STRING
	//IS STRING?
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_string_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE(error_not_a_string);
	PUSH(INDD(R1,1));
	CALL(MAKE_SOB_INTEGER);
	DROP(1);
	POP(R1);
	POP(FP);
	RETURN;	

PRIM_make_string:
	PUSH(FP);
	MOV(FP,SP);	
		
	PUSH(R1);
	PUSH(R2);
	PUSH(R10);
	
	CMP(FPARG(1),IMM(2));
	JUMP_GT(error_incorrect_amount_args);
	CMP(FPARG(1),IMM(0));
	JUMP_EQ(error_incorrect_amount_args);	
	CMP(FPARG(1),IMM(1));
	JUMP_NE(make_string_user_char);	

	PUSH(IMM(0)); //EMPTY CHAR
	CALL(MAKE_SOB_CHAR);
	DROP(1);
	MOV(R2,R0);
	JUMP(make_string_start);

make_string_user_char:
	MOV(R2,FPARG(3)); //THE CHAR OBJECT	
make_string_start:
	MOV(R1,FPARG(2)); //THE NUMBER OBJECT
	//IS NUMBER?
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE (error_not_a_integer);
	//IS CHAR?
	PUSH(R2);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_char_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE (error_not_a_char);
	
	MOV(R1,INDD(R1,1)); //THE NUMBER
	MOV(R2,INDD(R2,1)); //THE CHAR (integer)			
	MOV(R10,IMM(2)); //i=0;
	ADD(R1,IMM(2));
	PUSH(R1);
	CALL(MALLOC); //malloc (r1) space for the new string +2 FOR TYPE AND LENGTH
	DROP(1);
	MOV(INDD(R0,0),T_STRING);
	MOV(INDD(R0,1),R1-2);	
string_loop_start:
	CMP(R10, R1);
	JUMP_EQ (string_loop_end);
	MOV(INDD(R0,R10),R2);
	INCR(R10);
	JUMP(string_loop_start);
string_loop_end:
	POP(R10);
	POP(R2);
	POP(R1);
	POP(FP);
	RETURN;
	
PRIM_char_Xinteger:
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(1));
	JUMP_NE(error_incorrect_amount_args);	
	PUSH(R1);	
	MOV(R1,FPARG(2));  // the CHAR
	//IS CHAR?
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_char_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE(error_not_a_char);			
	MOV(R1,INDD(R1,1));
	PUSH(R1);
	CALL(MAKE_SOB_INTEGER);
	DROP(1);
	POP(R1);
	POP(FP);
	RETURN;
	
PRIM_integer_Xchar:
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(1));
	JUMP_NE(error_incorrect_amount_args);	
	PUSH(R1);	
	MOV(R1,FPARG(2));  // the integer OBJECT
	//IS integer?
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE(error_not_a_integer);			
	MOV(R1,INDD(R1,1));  // the integer ITSELF
	CMP(R1,IMM(0));
	JUMP_LT(error_not_a_char_integer);
	CMP(R1,IMM(255));
	JUMP_GE(error_not_a_char_integer);
	PUSH(R1);
	CALL(MAKE_SOB_CHAR);
	DROP(1);
	POP(R1);
	POP(FP);
	RETURN;
	
PRIM_make_vector:
	PUSH(FP);
	MOV(FP,SP);	
		
	PUSH(R1);
	PUSH(R2);
	PUSH(R10);
	
	CMP(FPARG(1),IMM(2));
	JUMP_GT(error_incorrect_amount_args);
	CMP(FPARG(1),IMM(0));
	JUMP_EQ(error_incorrect_amount_args);	
	CMP(FPARG(1),IMM(1));
	JUMP_NE(make_vector_user_arg);	

	PUSH(IMM(0)); //EMPTY CHAR
	CALL(MAKE_SOB_INTEGER);
	DROP(1);
	MOV(R2,R0);
	JUMP(make_vector_start);

make_vector_user_arg:
	MOV(R2,FPARG(3)); //THE CHAR OBJECT	
make_vector_start:
	MOV(R1,FPARG(2)); //THE NUMBER OBJECT
	//IS NUMBER?
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE (error_not_a_integer);

	
	MOV(R1,INDD(R1,1)); //THE NUMBER	
	MOV(R10,IMM(2)); //i=0;
	ADD(R1,IMM(2));
	PUSH(R1);
	CALL(MALLOC); //malloc (r1) space for the new string +2 FOR TYPE AND LENGTH
	DROP(1);
	MOV(INDD(R0,0),T_VECTOR);
	MOV(INDD(R0,1),R1-2);	
vector_loop_start:
	CMP(R10, R1);
	JUMP_EQ (vector_loop_end);
	MOV(INDD(R0,R10),R2);
	INCR(R10);
	JUMP(vector_loop_start);
vector_loop_end:
	POP(R10);
	POP(R2);
	POP(R1);
	POP(FP);
	RETURN;
	
PRIM_symbol_Xstring:
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(1));
	JUMP_NE(error_incorrect_amount_args);
	PUSH(R1);
	MOV(R1,FPARG(2)); //THE symbol OBJECT
	//is symbol?
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_symbol_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE (error_not_a_symbol);
	MOV(R0,INDD(R1,1));
	POP(R1);
	POP(FP);
	RETURN;
	
PRIM_binA: //ADD
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(2));
	JUMP_NE(error_incorrect_amount_args);
	PUSH(R1);
	PUSH(R2);
	MOV(R1,FPARG(2));
	MOV(R2,FPARG(3));
	//IS NUMBER? R1
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE (error_not_a_integer);
	//IS NUMBER? R2
	PUSH(R2);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE (error_not_a_integer);
	MOV(R1,INDD(R1,1));
	MOV(R2,INDD(R2,1));
	MOV(R0,IMM(0));
	ADD(R0,R1);
	ADD(R0,R2);
	PUSH(R0);
	CALL(MAKE_SOB_INTEGER);
	DROP(1);
	POP(R2);		
	POP(R1);
	POP(FP);
	RETURN;
	
PRIM_bin_: //SUB
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(2));
	JUMP_NE(error_incorrect_amount_args);
	PUSH(R1);
	PUSH(R2);
	MOV(R1,FPARG(2));
	MOV(R2,FPARG(3));
	//IS NUMBER? R1
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE (error_not_a_integer);
	//IS NUMBER? R2
	PUSH(R2);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE (error_not_a_integer);
	MOV(R1,INDD(R1,1));
	MOV(R2,INDD(R2,1));
	MOV(R0,R1);
	SUB(R0,R2);	
	PUSH(R0);
	CALL(MAKE_SOB_INTEGER);
	DROP(1);
	POP(R2);		
	POP(R1);
	POP(FP);
	RETURN;	
	
PRIM_binM: // MUL
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(2));
	JUMP_NE(error_incorrect_amount_args);
	PUSH(R1);
	PUSH(R2);
	MOV(R1,FPARG(2));
	MOV(R2,FPARG(3));
	//IS NUMBER? R1
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE (error_not_a_integer);
	//IS NUMBER? R2
	PUSH(R2);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE (error_not_a_integer);
	MOV(R1,INDD(R1,1));
	MOV(R2,INDD(R2,1));
	MOV(R0,IMM(1));
	MUL(R0,R1);
	MUL(R0,R2);
	PUSH(R0);
	CALL(MAKE_SOB_INTEGER);
	DROP(1);
	POP(R2);		
	POP(R1);
	POP(FP);
	RETURN;

PRIM_binD: // DIV
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(2));
	JUMP_NE(error_incorrect_amount_args);
	PUSH(R1);
	PUSH(R2);
	MOV(R1,FPARG(2));
	MOV(R2,FPARG(3));
	//IS NUMBER? R1
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE (error_not_a_integer);
	//IS NUMBER? R2
	PUSH(R2);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE (error_not_a_integer);
	MOV(R1,INDD(R1,1));
	MOV(R2,INDD(R2,1));
	CMP(R2,IMM(0));
	JUMP_EQ(error_divide_by_zero);
	MOV(R0,R1);
	DIV(R0,R2);	
	PUSH(R0);
	CALL(MAKE_SOB_INTEGER);
	DROP(1);
	POP(R2);		
	POP(R1);
	POP(FP);
	RETURN;	

PRIM_binE_: //numeric equals bin=?
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(2));
	JUMP_NE(error_incorrect_amount_args);
	PUSH(R1);
	PUSH(R2);
	MOV(R1,FPARG(2));
	MOV(R2,FPARG(3));
	//IS NUMBER? R1
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE (error_not_a_integer);
	//IS NUMBER? R2
	PUSH(R2);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE (error_not_a_integer);
	MOV(R1,INDD(R1,1));
	MOV(R2,INDD(R2,1));
	MOV(R0,R1);
	SUB(R0,R2);	//result of sub
	
	MOV(R1,R0);
	MOV(R0,SOB_BOOLEAN_TRUE);
	CMP(R1,IMM(0));
	JUMP_EQ (is_equal);
	MOV(R0,SOB_BOOLEAN_FALSE);
is_equal:	
	POP(R2);		
	POP(R1);
	POP(FP);
	RETURN;	
	
PRIM_binx_: //numeric less_than bin<?
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(2));
	JUMP_NE(error_incorrect_amount_args);
	PUSH(R1);
	PUSH(R2);
	MOV(R1,FPARG(2));
	MOV(R2,FPARG(3));
	//IS NUMBER? R1
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE (error_not_a_integer);
	//IS NUMBER? R2
	PUSH(R2);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE (error_not_a_integer);
	MOV(R1,INDD(R1,1));
	MOV(R2,INDD(R2,1));
	MOV(R0,R1);
	SUB(R0,R2);	//result of sub
	
	MOV(R1,R0);
	MOV(R0,SOB_BOOLEAN_TRUE);
	CMP(R1,IMM(0));
	JUMP_LT (less_than);
	MOV(R0,SOB_BOOLEAN_FALSE);
less_than:	
	POP(R2);		
	POP(R1);
	POP(FP);
	RETURN;	
	
PRIM_remainder: // DIV
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(2));
	JUMP_NE(error_incorrect_amount_args);
	PUSH(R1);
	PUSH(R2);
	MOV(R1,FPARG(2));
	MOV(R2,FPARG(3));
	//IS NUMBER? R1
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE (error_not_a_integer);
	//IS NUMBER? R2
	PUSH(R2);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE (error_not_a_integer);
	MOV(R1,INDD(R1,1));
	MOV(R2,INDD(R2,1));
	CMP(R2,IMM(0));
	JUMP_EQ(error_divide_by_zero);
	MOV(R0,R1);
	REM(R0,R2);	
	PUSH(R0);
	CALL(MAKE_SOB_INTEGER);
	DROP(1);
	POP(R2);		
	POP(R1);
	POP(FP);
	RETURN;		

PRIM_string_set_:
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(3));
	JUMP_NE(error_incorrect_amount_args);
	
	PUSH(R1);	
	MOV(R1,FPARG(2));  // the STRING OBJECT
	
	//IS STRING?
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_string_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE(error_not_a_string);
	
	PUSH(R2);
	MOV(R2,FPARG(3));  // the INTEGER OBJECT
	//IS integer?
	PUSH(R2);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE(error_not_a_integer);			
	MOV(R2,INDD(R2,1)); //THE INTEGER ITSELF
	
	//IS THE NUMBER BIGGER THAN THE STRING?	OR LESS THAN ZERO?
	CMP(R2,IMM(0));
	JUMP_LT(error_bad_index);
	CMP(R2,INDD(R1,1));
	JUMP_GE(error_bad_index);	
	
	PUSH(R3);
	MOV(R3,FPARG(4));  // the NEW CHAR OBJECT
	//IS CHAR?
	PUSH(R3);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_char_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE(error_not_a_char);
	MOV(R3, INDD(R3,1)); // the integer of the char
	
	//SET THE NEW CHAR!
	ADD(R2,IMM(2)); //+2 FOR THE TYPE AND LENGTH
	MOV(INDD(R1,R2), R3);
	MOV(R0,SOB_VOID);
	
	POP(R3);
	POP(R2);
	POP(R1);
	POP(FP);
	RETURN;
	
PRIM_vector_set_:
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(3));
	JUMP_NE(error_incorrect_amount_args);
	
	PUSH(R1);	
	MOV(R1,FPARG(2));  // the vector OBJECT
	
	//IS vector?
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_vector_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE(error_not_a_vector);
	
	PUSH(R2);
	MOV(R2,FPARG(3));  // the INTEGER OBJECT
	//IS integer?
	PUSH(R2);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE(error_not_a_integer);			
	MOV(R2,INDD(R2,1)); //THE INTEGER ITSELF
	
	//IS THE NUMBER BIGGER THAN THE STRING?	OR LESS THAN ZERO?
	CMP(R2,IMM(0));
	JUMP_LT(error_bad_index);
	CMP(R2,INDD(R1,1));
	JUMP_GE(error_bad_index);	
	
	PUSH(R3);
	MOV(R3,FPARG(4));  // the NEW CHAR OBJECT
	
	//SET THE NEW CHAR!
	ADD(R2,IMM(2)); //+2 FOR THE TYPE AND LENGTH
	MOV(INDD(R1,R2), R3);
	MOV(R0,SOB_VOID);
	
	POP(R3);
	POP(R2);
	POP(R1);
	POP(FP);
	RETURN;	
	
PRIM_string_ref:
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(2));
	JUMP_NE(error_incorrect_amount_args);
	
	PUSH(R1);	
	MOV(R1,FPARG(2));  // the STRING OBJECT
	
	//IS STRING?
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_string_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE(error_not_a_string);
	
	PUSH(R2);
	MOV(R2,FPARG(3));  // the INTEGER OBJECT
	//IS integer?
	PUSH(R2);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE(error_not_a_integer);			
	MOV(R2,INDD(R2,1)); //THE INTEGER ITSELF	

	ADD(R2,IMM(2));
	MOV(R0,INDD(R1,R2));
	PUSH(R0);
	CALL(MAKE_SOB_CHAR);
	DROP(1);	
	POP(R2);
	POP(R1);
	POP(FP);
	RETURN;

PRIM_vector_ref:
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(2));
	JUMP_NE(error_incorrect_amount_args);
	
	PUSH(R1);	
	MOV(R1,FPARG(2));  // the vector OBJECT
	
	//IS vector?
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_vector_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE(error_not_a_vector);
	
	PUSH(R2);
	MOV(R2,FPARG(3));  // the INTEGER OBJECT
	//IS integer?
	PUSH(R2);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_integer_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE(error_not_a_integer);			
	MOV(R2,INDD(R2,1)); //THE INTEGER ITSELF	

	ADD(R2,IMM(2));
	MOV(R0,INDD(R1,R2));
	
	POP(R2);
	POP(R1);
	POP(FP);
	RETURN;
//*********************************************************************
PRIM_apply:
	MOV(R1,SP);
	SUB(R1,IMM(6));
	PUSH(FP);
	MOV(FP,SP);	
	
	CMP(FPARG(1),IMM(2));
	JUMP_NE(error_incorrect_amount_args);
	
	MOV(R7,FPARG(-1)); // return address
	 // old fp
	MOV(R2,FPARG(2)); // procedure

	PUSH(R2);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_procedure_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE(error_not_a_procedure);			
	
	MOV(R2,INDD(FPARG(2),1)); // procedure env
	MOV(R3,INDD(FPARG(2),2)); // procedure code
	MOV(R4,FPARG(3));  // the LIST OBJECT
	
	//IS list?
	PUSH(R4);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_list_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_EQ (args_apply_ok);
	JUMP(error_not_a_list);

args_apply_ok:	
	MOV(R5,IMM(0));
	//printf("R7: return address- %ld\n", R7); 
	//printf("R1: old fp- %ld\n", R1);
	//printf("R2: env(f)- %ld\n", R2);
	//printf("R3: code(f)- %ld\n", R3);
	//printf("R4: arg list- %ld\n", R4);
	//printf("R5: arg count (0) %ld\n", R5);
	//so far:
	// R7 - return address
	// R1 - old fp
	// R2 - env(f)
	// R3 - code(f)
	// R4 - arg list
	// R5 - arg count (0);
	
apply_count_start:
	CMP(R4,SOB_NIL);
	JUMP_EQ(apply_count_end);
	INCR(R5);
	MOV(R4,INDD(R4,2));
	JUMP(apply_count_start);
apply_count_end:
	//printf("R5: arg count (after count) %ld\n", R5);	
	MOV(R4,FPARG(3));
	MOV(SP,R1+1);
	//printf("SP: (SHOULD BE 6) %ld\n", SP);
	ADD(SP,R5);

	MOV(STACK(SP), R5);
	
	//printf("*********stack becore pack********\n");
	//printStack(machine, 20);
	//printf("*********stack becore pack********\n");
apply_unpack_start:
	CMP(R4,SOB_NIL);
	JUMP_EQ(apply_unpack_end);
	DECR(SP);
	MOV(STACK(SP),INDD(R4,1));
	MOV(R4,INDD(R4,2));
	JUMP(apply_unpack_start);
	
apply_unpack_end:
	//printf("SP: (SHOULD BE 6) %ld\n", SP);	
	//printf("*********stack after pack********\n");
	//printStack(machine, 20);
	//printf("*********stack after pack********\n");




	ADD(SP,R5);
	ADD(SP,1);
	PUSH(R2); //ENV
	PUSH(R7); //RETURN ADDRESS
	MOV(FP,R1);
	JUMPA(R3);
	
	
	
//*********************************************************************

PRIM_string_Xsymbol:
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(1));
	JUMP_NE(error_incorrect_amount_args);
	
	PUSH(R1);	
	MOV(R1,FPARG(2));  // the STRING
	//IS STRING?
	PUSH(R1);
	PUSH(IMM(1));
	PUSH(301858270);
	CALL(PRIM_string_);
	DROP(3);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE(error_not_a_string);
	
	//is string not empty?		
	CMP(INDD(R1,1), IMM(0));
	JUMP_EQ(error_empty_string_to_sym)
	PUSH(R1);
	CALL(LOOKUP_SYMBOL);
	DROP(1);
	CMP(R0,SOB_BOOLEAN_FALSE);
	JUMP_EQ(string_symbol_add_sym);
	//OTHERWISE, R0 HAS THE SYMBOL OBJECT;
	POP(R1);
	POP(FP);
	RETURN;
	
string_symbol_add_sym:
	PUSH(2);
	CALL(MALLOC);
	DROP(1);
	MOV(INDD(R0,0), T_SYMBOL);
	MOV(INDD(R0,1), R1);
	MOV(R1,R0);
	PUSH(R0);
	CALL(ADD_SYMBOL);
	DROP(1);
	MOV(R0,R1);
	POP(R1);
	POP(FP);
	RETURN;
	
ADD_SYMBOL:
	PUSH(FP);
	MOV(FP,SP);
	PUSH(R1);
	PUSH(R0);
	
	MOV(R1,IND(1));
	
	PUSH(IMM(2));						
	CALL(MALLOC);						
	DROP(1);							
	
	MOV(INDD(R0,0),FPARG(0));			
	MOV(INDD(R0,1),R1);			
	MOV(IND(1), R0);					
	
	POP(R0);
	POP(R1);
	POP(FP);
	RETURN;

LOOKUP_SYMBOL:
	PUSH(FP);
	MOV(FP,SP);
	PUSH(R1);
	PUSH(R2);
	PUSH(R10);
	PUSH(R11);
	MOV(R1,FPARG(0)); //THE STRING TO LOOK FOR.
	MOV(R10,IND(1)); //THE SYMBOL LIST FIRST LINK
lookup_symbol_loop_start:
	CMP(INDD(R10,1),SOB_NIL);
	JUMP_EQ(lookup_symbol_loop_end);
	MOV(R11,INDD(R10,0));
	MOV(R11,INDD(R11,1));
	PUSH(R1);
	PUSH(R11);
	CALL(STRING_EQUALS);
	DROP(2);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_NE(continue_lookup);
	MOV(R0,INDD(R10,0));
	POP(R11);
	POP(R10);
	POP(R2);
	POP(R1);
	POP(FP);
	RETURN;
continue_lookup:
	MOV(R10,INDD(R10,1));
	JUMP(lookup_symbol_loop_start);
	
lookup_symbol_loop_end:	
	MOV(R0, SOB_BOOLEAN_FALSE);
	POP(R11);
	POP(R10);
	POP(R2);
	POP(R1);
	POP(FP);
	RETURN;
	
STRING_EQUALS:
	PUSH(FP);
	MOV(FP,SP);
	PUSH(R1);
	PUSH(R2);
	PUSH(R10);
	MOV(R1, FPARG(0));
	MOV(R2, FPARG(1));	
	CMP(INDD(R1,1), INDD(R2,1));
	JUMP_NE(not_equal_string);
	MOV(R10, IMM(2));
string_equals_loop_start:	
	CMP(R10,INDD(R1,1)+2);
	JUMP_EQ(yes_equal_string);
	CMP(INDD(R1,R10), INDD(R2,R10));
	JUMP_NE(not_equal_string);
	INCR(R10);
	JUMP(string_equals_loop_start);
	

not_equal_string:
	MOV(R0,SOB_BOOLEAN_FALSE);
	POP(R10);
	POP(R2);
	POP(R1);
	POP(FP);
	RETURN;

yes_equal_string:
	MOV(R0,SOB_BOOLEAN_TRUE);
	POP(R10);
	POP(R2);
	POP(R1);
	POP(FP);
	RETURN;
	
PRIM_eq_:
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(2));
	JUMP_NE(error_incorrect_amount_args);
	PUSH(R1);
	PUSH(R2);
	MOV(R1,FPARG(2));
	MOV(R2,FPARG(3));
	CMP(IND(R1), IND(R2));
	JUMP_NE(not_equal); //same type? if not, return false; else:
	
	//deep eq?
	CMP(IND(R1), T_INTEGER);
	JUMP_EQ(equal_deep);
	CMP(IND(R1), T_CHAR);
	JUMP_EQ(equal_deep);
	CMP(IND(R1), T_BOOL);
	JUMP_EQ(equal_deep);
	//shallow eq?	
	CMP(IND(R1), T_CLOSURE);
	JUMP_EQ(equal_shallow);
	CMP(IND(R1), T_VECTOR);
	JUMP_EQ(equal_shallow);
	CMP(IND(R1), T_PAIR);
	JUMP_EQ(equal_shallow);
	CMP(IND(R1), T_STRING);
	JUMP_EQ(equal_shallow);
	CMP(IND(R1), T_SYMBOL);
	JUMP_EQ(equal_shallow);			
	//eq? => true
	CMP(IND(R1), T_NIL);
	JUMP_EQ(yes_equal);
	CMP(IND(R1), T_VOID);
	JUMP_EQ(yes_equal);
	JUMP(error_unknown);

	
equal_shallow:
	CMP(R1,R2);
	JUMP_EQ(yes_equal);
	JUMP(not_equal);	
	
equal_deep:
	CMP(INDD(R1,1),INDD(R2,1));
	JUMP_EQ(yes_equal);
	JUMP(not_equal);

	
yes_equal:
	MOV(R0,SOB_BOOLEAN_TRUE);
	JUMP(equal_finish);
		
not_equal:
	MOV(R0,SOB_BOOLEAN_FALSE);
	JUMP(equal_finish);
	
equal_finish:
	POP(R2);
	POP(R1);
	POP(FP);
	RETURN;
	
PRIM_display:
	PUSH(FP);
	MOV(FP,SP);	
	CMP(FPARG(1),IMM(1));
	JUMP_NE(error_incorrect_amount_args);
	
	PUSH(FPARG(2));
	CALL(WRITE_SOB);
	DROP(1);
	PUSH(IMM('\n'));
	CALL(PUTCHAR);
	DROP(1);
	MOV(R0,SOB_VOID);
	
	
	POP(FP);
	RETURN;
	
	
PRIM_A: //VARIADIC +
	PUSH(FP);
	MOV(FP,SP);	
PRIM_A_start:	
PRIM_A_zero:
	CMP(FPARG(1),IMM(0));
	JUMP_NE(PRIM_A_one);
	PUSH(IMM(0));
	CALL(MAKE_SOB_INTEGER);
	DROP(1);
	POP(FP);
	RETURN;
	
PRIM_A_one:	
	CMP(FPARG(1),IMM(1));
	JUMP_NE(PRIM_A_two);
	MOV(R0,FPARG(2));
	POP(FP);
	RETURN;
	
PRIM_A_two:	
	CMP(FPARG(1),IMM(2));
	JUMP_NE(PRIM_A_general);

	PUSH(FPARG(2));
	PUSH(FPARG(3));
	PUSH(2);
	PUSH(301858270);
	CALL(PRIM_binA);
	DROP(4);
	POP(FP);
	RETURN;
	
PRIM_A_general:
	
	//MOV(R4, SP);
	//DECR(R4);
	PUSH(R1);	
	MOV(R1, FPARG(1));
	DECR(R1); //NEW NUM OF ARGS
	PUSH(R2);
	MOV(R2, FPARG(0)); //ENV
	
	PUSH(R3);
	MOV(R3, FPARG(-1)); //THE RETURN ADDRESS
	PUSH(R4);
	MOV(R4,FPARG(-2)); //OLD FP
	
	//ADD THE FIRST TWO
	PUSH(FPARG(2));
	PUSH(FPARG(3));
	PUSH(2);
	PUSH(301858270);
	CALL(PRIM_binA);
	DROP(4);
	
	
	MOV(FPARG(3), R0);
	MOV(FPARG(2), R1);
	MOV(FPARG(1), R2);
	MOV(FPARG(0), R3);	
	MOV(FPARG(-1), R4);
	
	POP(R4);
	POP(R3);
	POP(R2);
	POP(R1);

	DECR(SP);
	DECR(FP);
	JUMP(PRIM_A_start);
	
	
PRIM_M: //VARIADIC *
	PUSH(FP);
	MOV(FP,SP);	
PRIM_M_start:	
PRIM_M_zero:
	CMP(FPARG(1),IMM(0));
	JUMP_NE(PRIM_M_one);
	PUSH(IMM(1));
	CALL(MAKE_SOB_INTEGER);
	DROP(1);
	POP(FP);
	RETURN;
	
PRIM_M_one:	
	CMP(FPARG(1),IMM(1));
	JUMP_NE(PRIM_M_two);
	MOV(R0,FPARG(2));
	POP(FP);
	RETURN;
	
PRIM_M_two:	
	CMP(FPARG(1),IMM(2));
	JUMP_NE(PRIM_M_general);

	PUSH(FPARG(2));
	PUSH(FPARG(3));
	PUSH(2);
	PUSH(301858270);
	CALL(PRIM_binM);
	DROP(4);
	POP(FP);
	RETURN;
	
PRIM_M_general:
	
	//MOV(R4, SP);
	//DECR(R4);
	PUSH(R1);	
	MOV(R1, FPARG(1));
	DECR(R1); //NEW NUM OF ARGS
	PUSH(R2);
	MOV(R2, FPARG(0)); //ENV
	
	PUSH(R3);
	MOV(R3, FPARG(-1)); //THE RETURN ADDRESS
		
	PUSH(R4);
	MOV(R4,FPARG(-2)); //OLD FP
	
	//MUL THE FIRST TWO
	PUSH(FPARG(2));
	PUSH(FPARG(3));
	PUSH(2);
	PUSH(301858270);
	CALL(PRIM_binM);
	DROP(4);
	
	
	MOV(FPARG(3), R0);
	MOV(FPARG(2), R1);
	MOV(FPARG(1), R2);
	MOV(FPARG(0), R3);	
	MOV(FPARG(-1), R4);
	
	POP(R4);
	POP(R3);
	POP(R2);
	POP(R1);

	DECR(SP);
	DECR(FP);
	JUMP(PRIM_M_start);

PRIM__: ////VARIADIC -
	PUSH(FP);
	MOV(FP,SP);	
PRIM_S_start:	
PRIM_S_zero:
	CMP(FPARG(1),IMM(0));
	JUMP_EQ(error_incorrect_amount_args);
	
PRIM_S_one:	
	CMP(FPARG(1),IMM(1));
	JUMP_NE(PRIM_S_two);
	PUSH(FPARG(2));
	PUSH(IMM(0));
	CALL(MAKE_SOB_INTEGER);
	DROP(1);
	PUSH(R0);
	PUSH(IMM(2));
	PUSH(301858270);
	CALL(PRIM_bin_);
	DROP(4);			
	POP(FP);
	RETURN;
	
PRIM_S_two:	
	CMP(FPARG(1),IMM(2));
	JUMP_NE(PRIM_S_general);

	PUSH(FPARG(3));
	PUSH(FPARG(2));
	PUSH(2);
	PUSH(301858270);
	CALL(PRIM_bin_);
	DROP(4);
	POP(FP);
	RETURN;
	
PRIM_S_general:
	
	//MOV(R4, SP);
	//DECR(R4);
	PUSH(R1);	
	MOV(R1, FPARG(1));
	DECR(R1); //NEW NUM OF ARGS
	PUSH(R2);
	MOV(R2, FPARG(0)); //ENV
	
	PUSH(R3);
	MOV(R3, FPARG(-1)); //THE RETURN ADDRESS
		
	PUSH(R4);
	MOV(R4,FPARG(-2)); //OLD FP
	
	//SUB THE FIRST TWO
	PUSH(FPARG(3));
	PUSH(FPARG(2));
	PUSH(2);
	PUSH(301858270);
	CALL(PRIM_bin_);
	DROP(4);
	
	
	MOV(FPARG(3), R0);
	MOV(FPARG(2), R1);
	MOV(FPARG(1), R2);
	MOV(FPARG(0), R3);	
	MOV(FPARG(-1), R4);
	
	POP(R4);
	POP(R3);
	POP(R2);
	POP(R1);

	DECR(SP);
	DECR(FP);
	JUMP(PRIM_S_start);	
	

PRIM_D: ////VARIADIC -
	PUSH(FP);
	MOV(FP,SP);	
PRIM_D_start:	
PRIM_D_zero:
	CMP(FPARG(1),IMM(0));
	JUMP_EQ(error_incorrect_amount_args);
	
PRIM_D_one:	
	CMP(FPARG(1),IMM(1));
	JUMP_NE(PRIM_D_two);
	PUSH(FPARG(2));
	PUSH(IMM(1));
	CALL(MAKE_SOB_INTEGER);
	DROP(1);
	PUSH(R0);
	PUSH(IMM(2));
	PUSH(301858270);
	CALL(PRIM_binD);
	DROP(4);			
	POP(FP);
	RETURN;
	
PRIM_D_two:	
	CMP(FPARG(1),IMM(2));
	JUMP_NE(PRIM_D_general);

	PUSH(FPARG(3));
	PUSH(FPARG(2));
	PUSH(2);
	PUSH(301858270);
	CALL(PRIM_binD);
	DROP(4);
	POP(FP);
	RETURN;
	
PRIM_D_general:
	
	//MOV(R4, SP);
	//DECR(R4);
	PUSH(R1);	
	MOV(R1, FPARG(1));
	DECR(R1); //NEW NUM OF ARGS
	PUSH(R2);
	MOV(R2, FPARG(0)); //ENV
	
	PUSH(R3);
	MOV(R3, FPARG(-1)); //THE RETURN ADDRESS
		
	PUSH(R4);
	MOV(R4,FPARG(-2)); //OLD FP
	
	//SUB THE FIRST TWO
	PUSH(FPARG(3));
	PUSH(FPARG(2));
	PUSH(2);
	PUSH(301858270);
	CALL(PRIM_binD);
	DROP(4);
	
	
	MOV(FPARG(3), R0);
	MOV(FPARG(2), R1);
	MOV(FPARG(1), R2);
	MOV(FPARG(0), R3);	
	MOV(FPARG(-1), R4);
	
	POP(R4);
	POP(R3);
	POP(R2);
	POP(R1);

	DECR(SP);
	DECR(FP);
	JUMP(PRIM_D_start);	


PRIM_E: ////VARIADIC EQUAL NUMERIC
	PUSH(FP);
	MOV(FP,SP);	
PRIM_E_start:	
PRIM_E_zero:
	CMP(FPARG(1),IMM(0));
	JUMP_EQ(error_incorrect_amount_args);
	
PRIM_E_one:	
	CMP(FPARG(1),IMM(1));
	JUMP_NE(PRIM_E_two);
	MOV(R0,SOB_BOOLEAN_TRUE);	
	POP(FP);
	RETURN;
	
PRIM_E_two:	
	CMP(FPARG(1),IMM(2));
	JUMP_NE(PRIM_E_general);

	PUSH(FPARG(3));
	PUSH(FPARG(2));
	PUSH(2);
	PUSH(301858270);
	
	CALL(PRIM_binE_);

	DROP(4);
	POP(FP);
	RETURN;
	
PRIM_E_general:
	
	//MOV(R4, SP);
	//DECR(R4);
	PUSH(R1);	
	MOV(R1, FPARG(1));
	DECR(R1); //NEW NUM OF ARGS
	PUSH(R2);
	MOV(R2, FPARG(0)); //ENV
	
	PUSH(R3);
	MOV(R3, FPARG(-1)); //THE RETURN ADDRESS
		
	PUSH(R4);
	MOV(R4,FPARG(-2)); //OLD FP
	
	//EQ THE FIRST TWO
	PUSH(FPARG(3));
	PUSH(FPARG(2));
	PUSH(2);
	PUSH(301858270);
	CALL(PRIM_binE_);
	DROP(4);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_EQ(prim_equal_yes);
	JUMP(prim_numeric_equals_false);
prim_equal_yes:
	MOV(R0,FPARG(2));
	
	MOV(FPARG(3), R0);
	MOV(FPARG(2), R1);
	MOV(FPARG(1), R2);
	MOV(FPARG(0), R3);	
	MOV(FPARG(-1), R4);
	
	POP(R4);
	POP(R3);
	POP(R2);
	POP(R1);

	DECR(SP);
	DECR(FP);
	JUMP(PRIM_E_start);		
	
prim_numeric_equals_false:
	POP(R4);
	POP(R3);
	POP(R2);
	POP(R1);
	MOV(R0,SOB_BOOLEAN_FALSE);
	POP(FP);
	
	RETURN;
	


PRIM_x: ////VARIADIC LT NUMERIC
	PUSH(FP);
	MOV(FP,SP);	
PRIM_x_start:	
PRIM_x_zero:
	CMP(FPARG(1),IMM(0));
	JUMP_EQ(error_incorrect_amount_args);
	
PRIM_x_one:	
	CMP(FPARG(1),IMM(1));
	JUMP_NE(PRIM_x_two);
	MOV(R0,SOB_BOOLEAN_TRUE);	
	POP(FP);
	RETURN;
	
PRIM_x_two:	
	CMP(FPARG(1),IMM(2));
	JUMP_NE(PRIM_x_general);

	PUSH(FPARG(3));
	PUSH(FPARG(2));
	PUSH(2);
	PUSH(301858270);
	
	CALL(PRIM_binx_);

	DROP(4);
	POP(FP);
	RETURN;
	
PRIM_x_general:
	
	//MOV(R4, SP);
	//DECR(R4);
	PUSH(R1);
	MOV(R1, FPARG(1));
	DECR(R1); //NEW NUM OF ARGS
	PUSH(R2);
	MOV(R2, FPARG(0)); //ENV
	
	PUSH(R3);
	MOV(R3, FPARG(-1)); //THE RETURN ADDRESS
		
	PUSH(R4);
	MOV(R4,FPARG(-2)); //OLD FP
	
	//LT THE FIRST TWO
	PUSH(FPARG(3));
	PUSH(FPARG(2));
	PUSH(2);
	PUSH(301858270);
	CALL(PRIM_binx_);
	DROP(4);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_EQ(prim_lt_yes);
	JUMP(prim_numeric_lt_false);
prim_lt_yes:
	PUSH(FPARG(2));
	PUSH(FPARG(3));
	PUSH(2);
	PUSH(301858270);
	CALL(PRIM_bin_);
	DROP(4);
	CMP(R0, 0);
	JUMP_LT(first_bigger)
	MOV(R0,FPARG(3));		
	JUMP(constinue_lt);
first_bigger:	
		MOV(R0,FPARG(2));		
constinue_lt:
	MOV(FPARG(3), R0);
	MOV(FPARG(2), R1);
	MOV(FPARG(1), R2);
	MOV(FPARG(0), R3);	
	MOV(FPARG(-1), R4);
	
	POP(R4);
	POP(R3);
	POP(R2);
	POP(R1);

	DECR(SP);
	DECR(FP);
	JUMP(PRIM_x_start);		
	
prim_numeric_lt_false:
	POP(R4);
	POP(R3);
	POP(R2);
	POP(R1);
	MOV(R0,SOB_BOOLEAN_FALSE);
	POP(FP);
	
	RETURN;
//////////////////////////////////////
PRIM_X: //VARIADIC GT NUMERIC
	PUSH(FP);
	MOV(FP,SP);	
PRIM_X_start:	
PRIM_X_zero:
	CMP(FPARG(1),IMM(0));
	JUMP_EQ(error_incorrect_amount_args);
	
PRIM_X_one:	
	CMP(FPARG(1),IMM(1));
	JUMP_NE(PRIM_X_two);
	MOV(R0,SOB_BOOLEAN_TRUE);	
	POP(FP);
	RETURN;
	
PRIM_X_two:		
	CMP(FPARG(1),IMM(2));
	JUMP_NE(PRIM_X_general);
	PUSH(FPARG(2));
	PUSH(FPARG(3));
	PUSH(2);
	PUSH(301858270);
	CALL(PRIM_bin_);
	DROP(4);
	CMP(INDD(R0,1), IMM(0));	
	JUMP_LT(prim_gt_two_yes);
	MOV(R0,SOB_BOOLEAN_FALSE);
	JUMP(finish_two_gt);
prim_gt_two_yes:
	MOV(R0,SOB_BOOLEAN_TRUE);
finish_two_gt:	
	POP(FP);
	RETURN;
	
PRIM_X_general:
	
	//MOV(R4, SP);
	//DECR(R4);
	PUSH(R1);
	MOV(R1, FPARG(1));
	DECR(R1); //NEW NUM OF ARGS
	PUSH(R2);
	MOV(R2, FPARG(0)); //ENV
	
	PUSH(R3);
	MOV(R3, FPARG(-1)); //THE RETURN ADDRESS
		
	PUSH(R4);
	MOV(R4,FPARG(-2)); //OLD FP
	
	//EQ THE FIRST TWO
	PUSH(FPARG(3));
	PUSH(FPARG(2));
	PUSH(2);
	PUSH(301858270);
	CALL(PRIM_X);
	DROP(4);
	CMP(R0,SOB_BOOLEAN_TRUE);
	JUMP_EQ(prim_gt_yes);
	JUMP(prim_numeric_gt_false);
prim_gt_yes:
	PUSH(FPARG(2));
	PUSH(FPARG(3));
	PUSH(2);
	PUSH(301858270);
	CALL(PRIM_bin_);
	DROP(4);
	CMP(R0, 0);
	JUMP_LT(first_bigger_gt)
	MOV(R0,FPARG(3));		
	JUMP(constinue_gt);
first_bigger_gt:	
		MOV(R0,FPARG(2));		
constinue_gt:
	MOV(FPARG(3), R0);
	MOV(FPARG(2), R1);
	MOV(FPARG(1), R2);
	MOV(FPARG(0), R3);	
	MOV(FPARG(-1), R4);
	
	POP(R4);
	POP(R3);
	POP(R2);
	POP(R1);

	DECR(SP);
	DECR(FP);
	JUMP(PRIM_X_start);		
	
prim_numeric_gt_false:
	POP(R4);
	POP(R3);
	POP(R2);
	POP(R1);
	MOV(R0,SOB_BOOLEAN_FALSE);
	POP(FP);
	
	RETURN;
/////////////////////////////////	
	

	
	
	
	
	
	
	
	
	