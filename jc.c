#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LABELS 1024

int label_counter = 0;

void generate_asm(FILE *asm_file, token current_token) {
    static int label_stack_top = -1;
    static int label_stack[MAX_LABELS];
    static int else_encountered[MAX_LABELS] = {0}; 

    switch (current_token.type) {
        case DEFUN:
            fprintf(asm_file, ".text\n");
            if (strcmp(current_token.str, "main") == 0) {
                fprintf(asm_file, ".globl _start\n");
                fprintf(asm_file, "_start:\n");
                fprintf(asm_file, "    call main\n");
                fprintf(asm_file, "    li a7, 93\n");   
                fprintf(asm_file, "    ecall\n");
            }
            fprintf(asm_file, ".globl %s\n", current_token.str);
            fprintf(asm_file, "%s:\n", current_token.str);
            fprintf(asm_file, "    addi sp, sp, -8\n");
            fprintf(asm_file, "    sw ra, 4(sp)\n");
            fprintf(asm_file, "    sw fp, 0(sp)\n");
            fprintf(asm_file, "    mv fp, sp\n");
            break;

        case IDENT:
            fprintf(asm_file, "    call %s\n", current_token.str); 
            fprintf(asm_file, "    addi sp, sp, -4\n");           
            fprintf(asm_file, "    sw a0, 0(sp)\n");
        break;

        case RETURN:
            fprintf(asm_file, "    lw a0, 0(sp)\n");
            fprintf(asm_file, "    addi sp, sp, 4\n");
            fprintf(asm_file, "    mv sp, fp\n");
            fprintf(asm_file, "    lw fp, 0(sp)\n");
            fprintf(asm_file, "    lw ra, 4(sp)\n");
            fprintf(asm_file, "    addi sp, sp, 8\n");
            fprintf(asm_file, "    ret\n");
            break;

         case LITERAL:
            fprintf(asm_file, "    li t0, %d\n", current_token.literal_value);
            fprintf(asm_file, "    addi sp, sp, -4\n");
            fprintf(asm_file, "    sw t0, 0(sp)\n");
            break;

        case DUP:
            fprintf(asm_file, "    lw t0, 0(sp)\n");             
            fprintf(asm_file, "    addi sp, sp, -4\n");           
            fprintf(asm_file, "    sw t0, 0(sp)\n");              
        break;

        case DROP:
            fprintf(asm_file, "    addi sp, sp, 4\n");
            break;

        case SWAP:
            fprintf(asm_file, "    lw t0, 0(sp)\n");
            fprintf(asm_file, "    lw t1, 4(sp)\n");
            fprintf(asm_file, "    sw t0, 4(sp)\n");
            fprintf(asm_file, "    sw t1, 0(sp)\n");
            break;

        case ROT:
            fprintf(asm_file, "    lw t0, 8(sp)\n");
            fprintf(asm_file, "    lw t1, 4(sp)\n");
            fprintf(asm_file, "    lw t2, 0(sp)\n");
            fprintf(asm_file, "    sw t1, 8(sp)\n");
            fprintf(asm_file, "    sw t2, 4(sp)\n");
            fprintf(asm_file, "    sw t0, 0(sp)\n");
            break;

        case PLUS:
            fprintf(asm_file, "    lw t1, 0(sp)\n");       
            fprintf(asm_file, "    addi sp, sp, 4\n");    
            fprintf(asm_file, "    lw t0, 0(sp)\n");       
            fprintf(asm_file, "    addi sp, sp, 4\n");     
            fprintf(asm_file, "    add t0, t1, t0\n");     
            fprintf(asm_file, "    addi sp, sp, -4\n");    
            fprintf(asm_file, "    sw t0, 0(sp)\n");
            break;

        case MINUS:
            fprintf(asm_file, "    lw t1, 0(sp)\n");       
            fprintf(asm_file, "    addi sp, sp, 4\n");    
            fprintf(asm_file, "    lw t0, 0(sp)\n");       
            fprintf(asm_file, "    addi sp, sp, 4\n");    
            fprintf(asm_file, "    sub t0, t1, t0\n");     
            fprintf(asm_file, "    addi sp, sp, -4\n");    
            fprintf(asm_file, "    sw t0, 0(sp)\n");
            break;

        case MUL:
            fprintf(asm_file, "    lw t1, 0(sp)\n");      
            fprintf(asm_file, "    addi sp, sp, 4\n");     
            fprintf(asm_file, "    lw t0, 0(sp)\n");       
            fprintf(asm_file, "    addi sp, sp, 4\n");    
            fprintf(asm_file, "    mul t0, t1, t0\n");     
            fprintf(asm_file, "    addi sp, sp, -4\n");   
            fprintf(asm_file, "    sw t0, 0(sp)\n");
            break;

        case DIV:
            fprintf(asm_file, "    lw t1, 0(sp)\n");       
            fprintf(asm_file, "    addi sp, sp, 4\n");     
            fprintf(asm_file, "    lw t0, 0(sp)\n");      
            fprintf(asm_file, "    addi sp, sp, 4\n");   
            fprintf(asm_file, "    div t0, t1, t0\n");     
            fprintf(asm_file, "    addi sp, sp, -4\n");   
            fprintf(asm_file, "    sw t0, 0(sp)\n");
            break;

        case MOD:
            fprintf(asm_file, "    lw t1, 0(sp)\n");      
            fprintf(asm_file, "    addi sp, sp, 4\n");    
            fprintf(asm_file, "    lw t0, 0(sp)\n");       
            fprintf(asm_file, "    addi sp, sp, 4\n");    
            fprintf(asm_file, "    rem t0, t1, t0\n");    
            fprintf(asm_file, "    addi sp, sp, -4\n");   
            fprintf(asm_file, "    sw t0, 0(sp)\n");
            break;


        case AND:
            fprintf(asm_file, "    lw t0, 0(sp)\n");    
            fprintf(asm_file, "    lw t1, 4(sp)\n");   
            fprintf(asm_file, "    and t0, t1, t0\n");  
            fprintf(asm_file, "    sw t0, 4(sp)\n");   
            fprintf(asm_file, "    addi sp, sp, 4\n"); 
            break;

        case OR:
            fprintf(asm_file, "    lw t0, 0(sp)\n");   
            fprintf(asm_file, "    lw t1, 4(sp)\n");    
            fprintf(asm_file, "    or t0, t1, t0\n");  
            fprintf(asm_file, "    sw t0, 4(sp)\n");    
            fprintf(asm_file, "    addi sp, sp, 4\n"); 
            break;

        case NOT:
            fprintf(asm_file, "    lw t0, 0(sp)\n");
            fprintf(asm_file, "    not t0, t0\n");
            fprintf(asm_file, "    sw t0, 0(sp)\n");
            break;

        // Comparison operations
        case LT:
            fprintf(asm_file, "    lw t1, 0(sp)\n");   
            fprintf(asm_file, "    lw t0, 4(sp)\n");   
            fprintf(asm_file, "    slt t0, t1, t0\n"); 
            fprintf(asm_file, "    sw t0, 4(sp)\n");
            fprintf(asm_file, "    addi sp, sp, 4\n");
            break;

        case LE:
            fprintf(asm_file, "    lw t1, 0(sp)\n");   
            fprintf(asm_file, "    lw t0, 4(sp)\n");   
            fprintf(asm_file, "    slt t2, t0, t1\n"); 
            fprintf(asm_file, "    xori t0, t2, 1\n"); 
            fprintf(asm_file, "    sw t0, 4(sp)\n");   
            fprintf(asm_file, "    addi sp, sp, 4\n"); 
        break;

        case EQ:
            fprintf(asm_file, "    lw t0, 0(sp)\n");   
            fprintf(asm_file, "    lw t1, 4(sp)\n");   
            fprintf(asm_file, "    sub t0, t1, t0\n");
            fprintf(asm_file, "    seqz t0, t0\n");     
            fprintf(asm_file, "    sw t0, 4(sp)\n");
            fprintf(asm_file, "    addi sp, sp, 4\n");
            break;

        case GE:
            fprintf(asm_file, "    lw t1, 0(sp)\n");
            fprintf(asm_file, "    lw t0, 4(sp)\n");
            fprintf(asm_file, "    slt t0, t1, t0\n");  
            fprintf(asm_file, "    xori t0, t0, 1\n");  
            fprintf(asm_file, "    sw t0, 4(sp)\n");
            fprintf(asm_file, "    addi sp, sp, 4\n");
            break;

        case GT:
            fprintf(asm_file, "    lw t1, 0(sp)\n");    
            fprintf(asm_file, "    lw t0, 4(sp)\n");   
            fprintf(asm_file, "    slt t0, t0, t1\n"); 
            fprintf(asm_file, "    sw t0, 4(sp)\n");
            fprintf(asm_file, "    addi sp, sp, 4\n");
            break;

        case GET_ARG:
            fprintf(asm_file, "    mv t0, a%d\n", current_token.arg_no - 1); 
            fprintf(asm_file, "    addi sp, sp, -4\n");
            fprintf(asm_file, "    sw t0, 0(sp)\n"); 
        break;

        case SET_ARG:
            fprintf(asm_file, "    lw t0, 0(sp)\n"); 
            fprintf(asm_file, "    mv a%d, t0\n", current_token.arg_no - 1); 
            fprintf(asm_file, "    addi sp, sp, 4\n");
        break;

        case IF:
            label_stack_top++;
            label_stack[label_stack_top] = label_counter++;
            else_encountered[label_stack_top] = 0;
            fprintf(asm_file, "    lw t0, 0(sp)\n"); 
            fprintf(asm_file, "    addi sp, sp, 4\n"); 
            fprintf(asm_file, "    beqz t0, if_false_%d\n", label_stack[label_stack_top]);
            break;

        case ELSE:
            else_encountered[label_stack_top] = 1;
            fprintf(asm_file, "    j if_end_%d\n", label_stack[label_stack_top]);  
            fprintf(asm_file, "if_false_%d:\n", label_stack[label_stack_top]);    
            break;

        case ENDIF:
            if (else_encountered[label_stack_top]) {
                fprintf(asm_file, "if_end_%d:\n", label_stack[label_stack_top]);  
            } else {
                fprintf(asm_file, "if_false_%d:\n", label_stack[label_stack_top]);
            }
            label_stack_top--;
            break;

        case WHILE:
            label_stack_top++;
            label_stack[label_stack_top] = label_counter++;
            fprintf(asm_file, "while_begin_%d:\n", label_stack[label_stack_top]);
            fprintf(asm_file, "    lw t0, 0(sp)\n");
            fprintf(asm_file, "    addi sp, sp, 4\n");
            fprintf(asm_file, "    beqz t0, while_end_%d\n", label_stack[label_stack_top]);
            break;

        case ENDWHILE:
            fprintf(asm_file, "    j while_begin_%d\n", label_stack[label_stack_top]);
            fprintf(asm_file, "while_end_%d:\n", label_stack[label_stack_top]);
            label_stack_top--;
            break;

        default:
            fprintf(stderr, "Error: Unsupported token type %d\n", current_token.type);
            break;
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source file>\n", argv[0]);
        return 1;
    }

    FILE *j_file = fopen(argv[1], "r");
    if (!j_file) {
        fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
        return 1;
    }

    char output_filename[512];
    strncpy(output_filename, argv[1], sizeof(output_filename) - 1);
    output_filename[sizeof(output_filename) - 1] = '\0';

    char *ext = strrchr(output_filename, '.');
    if (ext && strcmp(ext, ".j") == 0) {
        strcpy(ext, ".s");
    } else {
        strncat(output_filename, ".s", sizeof(output_filename) - strlen(output_filename) - 1);
    }

    FILE *asm_file = fopen(output_filename, "w");
    if (!asm_file) {
        fprintf(stderr, "Error: Could not create output file %s\n", output_filename);
        fclose(j_file);
        return 1;
    }

    token current_token;
    while (next_token(j_file, &current_token)) {
        if (current_token.type == DEFUN) {
            token func_name_token;
            if (!next_token(j_file, &func_name_token) || func_name_token.type != IDENT) {
                fprintf(stderr, "Error: Expected function name after 'defun'\n");
                fclose(j_file);
                fclose(asm_file);
                return 1;
            }
            strcpy(current_token.str, func_name_token.str);
            generate_asm(asm_file, current_token);
        } else {
            generate_asm(asm_file, current_token);
        }
    }

    fclose(j_file);
    fclose(asm_file);

    printf("Assembly written to %s\n", output_filename);
    return 0;
}