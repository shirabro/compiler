void printMemory(Machine *machine, int address){
	int i;
	long temp;
	printf("MEMORY:\n");
	for (i = 0 ; i <= address ; i++){
		temp = IND(IMM(i));
		switch(temp){
			case 937611:
				printf("%ld	T_UNDEF\n", i);
				break;
			case 937610:
				printf("%ld	T_VOID\n", i);
				break;
			case 722689:
				printf("%ld	T_NIL\n", i);
				break;
			case 741553:
				printf("%ld	T_BOOL\n", i);
				break;
			case 181048:
				printf("%ld	T_CHAR\n", i);
				break;
			case 945311:
				printf("%ld	T_INTEGER\n", i);
				break;
			case 799345:
				printf("%ld	T_STRING\n", i);
				break;
			case 368031:
				printf("%ld	T_SYMBOL\n", i);
				break;
			case 885397:
				printf("%ld	T_PAIR\n", i);
				break;
			case 335728:
				printf("%ld	T_VECTOR\n", i);
				break;
			case 276405:
				printf("%ld	T_CLOSURE\n", i);
				break;
			case 451794:
				printf("%ld	T_UNDEF\n", i);
				break;
			default:
				printf("%ld	%ld\n", i, temp);
				break;
		}
	}
}

void printStack(Machine *machine, int address){
	int i;
	long temp;
	printf("STACK:\n");
	for (i = 0 ; i < address ; i++){
		temp = STACK(i);
		switch(temp){
			case 937611:
				printf("%ld	T_UNDEF\n", i);
				break;
			case 937610:
				printf("%ld	T_VOID\n", i);
				break;
			case 722689:
				printf("%ld	T_NIL\n", i);
				break;
			case 741553:
				printf("%ld	T_BOOL\n", i);
				break;
			case 181048:
				printf("%ld	T_CHAR\n", i);
				break;
			case 945311:
				printf("%ld	T_INTEGER\n", i);
				break;
			case 799345:
				printf("%ld	T_STRING\n", i);
				break;
			case 368031:
				printf("%ld	T_SYMBOL\n", i);
				break;
			case 885397:
				printf("%ld	T_PAIR\n", i);
				break;
			case 335728:
				printf("%ld	T_VECTOR\n", i);
				break;
			case 276405:
				printf("%ld	T_CLOSURE\n", i);
				break;
			case 451794:
				printf("%ld	T_FVAR\n", i);
				break;
			default:
				printf("%ld	%ld\n", i, temp);
				break;
		}
	}
}


#define debug{\
	printf("SP: %ld\n", SP); 	\
	printf("FP: %ld\n", FP);	\
	printf("R0: %ld\n", R0);	\
	printf("R1: %ld\n", R1); 	\
	printf("R2: %ld\n", R2);	\
	printf("R3: %ld\n", R3);	\
	printf("R4: %ld\n", R4);	\
	printf("R5: %ld\n", R5);	\
	printf("R6: %ld\n", R6);	\
	printf("R7: %ld\n", R7);	\
	printStack(machine, 20);	\
	printMemory(machine, 180);		}
	
	
	
	
	