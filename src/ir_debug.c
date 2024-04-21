#include <stdio.h>

#include "ir.h"

//
// The debug function for printing Riya IR instructions
//
// Operands
void ry_debug_operand(ry_kind type, int value, char *label) {
    switch (type) {
        case k_imm: printf("#%d", value); break;
        case k_mem: printf("[%d]", value); break;
        case k_loc: printf("%s", label); break;
        case k_reg: printf("r%d", value); break;
        case k_a_reg: printf("a%d", value); break;
        case k_sa_reg: printf("s%d", value); break;
        default: printf("<unk_op>");
    }
}

// Statements
void ry_debug_stmt(ry_stmt *stmt) {
    // Print the statement kind
    switch (stmt->kind) {
        case k_mov: break;
        case k_li: printf("li"); break;
        case k_alloca: break;
        case k_load: break;
        case k_store: break;
        
        case k_add: printf("add"); break;
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
        
        case k_ret: printf("ret"); break;
        case k_call: break;
        case k_syscall: break;
        
        default: printf("<unk_instr>");
    }
    
    printf(" ");
    
    // Print src1 if applicable
    if (stmt->src1_type) {
        ry_debug_operand(stmt->src1_type, stmt->src1, stmt->src1_label);
        printf(" ");
    }
    
    // Print src2 if applicable
    if (stmt->src2_type) {
        ry_debug_operand(stmt->src2_type, stmt->src2, stmt->src2_label);
        printf(" ");
    }
    
    // Print destination
    if (stmt->dest_type) {
        printf("to ");
        ry_debug_operand(stmt->dest_type, stmt->dest, NULL);
        printf(" ");
    }
    
    // Print type
    printf("as ");
    
    switch (stmt->type) {
        case t_m1: printf("m1"); break;
        case t_m2: printf("m2"); break;
        case t_m4: printf("m4"); break;
        case t_m8: printf("m8"); break;
        case t_ptr: printf("ptr"); break;
        case t_f32: printf("f32"); break;
        case t_f64: printf("f64"); break;
        default: printf("<unk_type>");
    }
    
    printf("\n");
}

