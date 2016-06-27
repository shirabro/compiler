#define SOB_VOID 10 
#define SOB_NIL 11   
#define SOB_BOOLEAN_FALSE 12
#define SOB_BOOLEAN_TRUE 14							

#define INIT_ENVIRONMENT {  \
	PUSH(SOB_NIL);			\
	PUSH(IMM(0));			\
	PUSH(SOB_NIL);	\
	PUSH(IMM(0));	\
	PUSH(IMM(0));	\
	MOV(FP,SP);}
							
							
#define INIT_TOP_LEVEL {				\
	PUSH(IMM(2));						\
	CALL(MALLOC);						\
	DROP(1);							\
	MOV(INDD(R0,0),SOB_NIL);			\
	MOV(INDD(R0,1),SOB_NIL);			\
	MOV(IND(1), R0);					\
	PUSH(R10);							\
	MOV(R10,IMM(0));					\
symbol_table_consts_start:				\
	CMP(R10,IND(0));					\
	JUMP_EQ(symbol_table_consts_end);	\
	CMP(INDD(R10,0), T_SYMBOL);			\
	JUMP_NE(continue_loop);				\
	PUSH(R10);							\
	CALL(ADD_SYMBOL);					\
	DROP(1);							\
continue_loop:							\
	INCR(R10);							\
	JUMP(symbol_table_consts_start);	\
symbol_table_consts_end:				\
	POP(R10);}
	
	
	

	
	
	
	
	
	
	
	
	
	
	
