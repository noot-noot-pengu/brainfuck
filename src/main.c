#include <stdio.h>
#include <stdlib.h>
#define MEMORY_SIZE 30000
#define PROGRAMM_SIZE 30000
#define MAX_LOOP_ITER 10000


struct Brainfuck {
	// memory pointer(cursor)
	long mem_ptr;
	// instruction pointer(cursor)
	long ins_ptr;
	unsigned char programm[PROGRAMM_SIZE];
	unsigned char memory[MEMORY_SIZE];
};


int is_instruction(char c);
void instruction(struct Brainfuck *brainfuck);
void loop(struct Brainfuck *brainfuck);


int main(int argc, char *argv[]) {
	struct Brainfuck brainfuck = { 
		0,
		0,
		{0},
		{0}
	};
	

	if (argv[1] == NULL){
		printf("Error: excpected fp name argument\n");
		return 0;
	}


	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL){
		printf("Error: Could not open fp\n");
		return 0;
	}


	while(1) {
		char c = fgetc(fp);
		if (feof(fp))
			break ;
		if (is_instruction(c)) {
			brainfuck.programm[brainfuck.ins_ptr] = c;
			brainfuck.ins_ptr++;
		}
	}
	brainfuck.ins_ptr = 0;
    fclose(fp);


	printf("\n\n\n");
	for (int i = 0; i < 30000; i++) {
		if (brainfuck.programm[i] == 0){
			break;
		}
		printf("%hhu ", brainfuck.programm[i]);
	}
	printf("\n\n\n");


	for (int i = 0; i < 30000; i++) {
		if (brainfuck.programm[i] == 0){
			//printf("\nprogramm ended\n");
			//exit(0);
			break;
		}
		instruction(&brainfuck);
		brainfuck.ins_ptr++;
	}
	

	printf("\n\n\n");
	for (int i = 0; i < 100; i++) {
		printf("%hhu ", brainfuck.memory[i]);
	}
	printf("\n\n\n");

	return 0;
}



int is_instruction(char c){
	if (c == '+' || c == '-' || c == '<' || c == '>' || c == '[' || c == ']' || c == '.' || c == ','){
		return 1;
	}else{
		return 0;
	}
}



void instruction(struct Brainfuck *brainfuck){
	switch (brainfuck->programm[brainfuck->ins_ptr]) {
		case '+':
			brainfuck->memory[brainfuck->mem_ptr]++;
			printf("added 1 to mem[%li] => %i \n", brainfuck->mem_ptr, brainfuck->memory[brainfuck->mem_ptr]);
			break;
		case '-':
			brainfuck->memory[brainfuck->mem_ptr]--;
			printf("added 1 to mem[%li] => %i \n", brainfuck->mem_ptr, brainfuck->memory[brainfuck->mem_ptr]);
			break;
		case '<':
			if (brainfuck->mem_ptr == 0){
				brainfuck->mem_ptr = MEMORY_SIZE-1;
			}else{
				brainfuck->mem_ptr--;
			}
			printf("moved < to ptr: %li \n", brainfuck->mem_ptr);
			break;
		case '>':
			if (brainfuck->mem_ptr == MEMORY_SIZE-1){
				brainfuck->mem_ptr = 0;
			}else{
				brainfuck->mem_ptr++;
			}
			printf("moved > to ptr: %li \n", brainfuck->mem_ptr);
			break;
		case '[':
			printf("\t loop start\n");
			brainfuck->ins_ptr++;
			loop(brainfuck);
			break;
		case ']':
			//brainfuck->ins_ptr++;
			break;
		case '.':
			printf("%i ", brainfuck->memory[brainfuck->mem_ptr]);
			break;
		case ',':
			break;
		default:
			printf("got %i ", brainfuck->programm[brainfuck->ins_ptr]);
			printf("\nError: unknown instruction %c\n", brainfuck->programm[brainfuck->ins_ptr]);
			//exit(0);
	}
	//printf("got %c ", brainfuck->programm[brainfuck->ins_ptr]);
	//printf("got %ld ", brainfuck->ins_ptr);
	//printf("\n");
}



void loop(struct Brainfuck *brainfuck) {
	int loop_ins_start_ptr = brainfuck->ins_ptr;
	int loop_counter_ptr = brainfuck->mem_ptr;
	int loop_counter = 0;
	//printf("\nloop start\n");
	//printf(" [%i] ", loop_ins_start_ptr);

	while (brainfuck->memory[brainfuck->mem_ptr] != 0){
		if (loop_counter >= MAX_LOOP_ITER) {
			exit(0);
		}

		//printf("loop_counter_ptr %i \n", brainfuck->memory[loop_counter_ptr]);
		//printf("\nf %i \n ", loop_counter);
		if (brainfuck->programm[brainfuck->ins_ptr] == ']'){
			brainfuck->ins_ptr = loop_ins_start_ptr;
		}else{
			instruction(brainfuck);
			brainfuck->ins_ptr++;
		}
		loop_counter++;
	}
	//brainfuck->ins_ptr++;
	printf("\t loop end, %c\n", brainfuck->programm[brainfuck->ins_ptr]);
	printf("\t loop end, %li\n", brainfuck->ins_ptr);
	printf("\t loop end\n");


	//printf("\nloop start %i \n", loop_counter);
}
