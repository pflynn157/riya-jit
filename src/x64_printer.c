#include <stdio.h>

#include "ir.h"
#include "asm_printer.h"

//
// Opens and initializes a file
//
FILE *x64_init(char *output_file) {
    FILE *file;
    if (output_file == NULL) {
        file = stdout;
    } else {
        file = fopen(output_file, "w");
    }
    
    fprintf(file, "; Generate from Riya\n");
    return file;
}

//
// Closes the file
//
void x64_close(FILE *file) {
    if (file != stdout) {
        fclose(file);
    }
}

//
// Generates and sets up a function
//
void x64_generate_function(FILE *file, char *name) {
    fprintf(file, "%s:\n", name);
}

//
// Generates a statement
//
void x64_generate_operand(FILE *file, ry_kind data_type, ry_kind type, uint64_t value, char *label) {
    char *reg32[] = {
        "eax", "ebx", "ecx", "edx", "edi", "esi",
        "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d"
    };

    switch (type) {
        case k_imm: fprintf(file, "%d", value); break;
        case k_mem: break;
        case k_loc: break;
        
        case k_reg: {
            if (data_type == t_m4) {
                fprintf(file, "%s", reg32[value]);
            }
        } break;
        
        case k_a_reg: break;
        case k_sa_reg: break;
        default:
    }
}

void x64_generate_stmt(FILE *file, ry_stmt *stmt) {   
    switch (stmt->kind) {
        case k_mov: break;
        
        case k_li: {
            fprintf(file, "  mov ");
            x64_generate_operand(file, stmt->type, stmt->dest_type, stmt->dest, NULL);
            fprintf(file, ", ");
            x64_generate_operand(file, stmt->type, stmt->src1_type, stmt->src1, NULL);
            fprintf(file, "\n");
        } break;
        
        case k_alloca: break;
        case k_load: break;
        case k_store: break;
        
        // Math operations are a little complex...
        case k_add: {
            fprintf(file, "  xor ");
            x64_generate_operand(file, stmt->type, stmt->dest_type, stmt->dest, NULL);
            printf(", ");
            x64_generate_operand(file, stmt->type, stmt->dest_type, stmt->dest, NULL);
            fprintf(file, "\n");
            
            fprintf(file, "  add ");
            x64_generate_operand(file, stmt->type, stmt->dest_type, stmt->dest, NULL);
            fprintf(file, ", ");
            x64_generate_operand(file, stmt->type, stmt->src1_type, stmt->src1, NULL);
            fprintf(file, "\n");
            
            fprintf(file, "  add ");
            x64_generate_operand(file, stmt->type, stmt->dest_type, stmt->dest, NULL);
            fprintf(file, ", ");
            x64_generate_operand(file, stmt->type, stmt->src2_type, stmt->src2, NULL);
            fprintf(file, "\n");
        } break;
        
        case k_sub: break;
        case k_mul: break; 
        case k_div: break;
        case k_rem: break;
        
        case k_beq: break;
        case k_bne: break;
        case k_bgt: break;
        case k_bge: break;
        case k_blt: break;
        case k_ble: break;
        
        case k_ret: {
            fprintf(file, "  mov ");
            if (stmt->type == t_m4) fprintf(file, "eax");
            fprintf(file, ", ");
            x64_generate_operand(file, stmt->type, stmt->src1_type, stmt->src1, NULL);
            fprintf(file, "\n");
            
            // TODO: Stack
            fprintf(file, "  ret\n");
        } break;
        
        case k_call: break;
        case k_syscall: break;
        
        default:
    }
}

