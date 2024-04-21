#pragma once

#include <stdint.h>

//
// Representation for the IR types of all kinds
//
typedef enum {
    k_none = 0,
    
    // Instructions
    k_mov, k_li,
    k_alloca,
    k_load, k_store,
    k_add, k_sub,
    k_mul, k_div, k_rem,
    
    k_beq, k_bne,
    k_bgt, k_bge,
    k_blt, k_ble,
    
    k_ret, k_ret_void,
    k_call, k_syscall,
    
    // Operands
    k_imm, k_mem, k_loc,
    k_reg, k_a_reg, k_sa_reg,
    
    // Types
    t_void,
    t_m1, t_m2, t_m4, t_m8,
    t_ptr,
    t_f32, t_f64
} ry_kind;

//
// Represents an instruction
//
typedef struct {
    ry_kind kind;
    ry_kind type;
    
    ry_kind dest_type;
    ry_kind src1_type;
    ry_kind src2_type;
    
    uint64_t dest;
    uint64_t src1;
    uint64_t src2;
    
    char *src1_label;
    char *src2_label;
} ry_stmt;

//
// Debug functions
//
void ry_debug_operand(ry_kind type, uint64_t value, char *label);
void ry_debug_stmt(ry_stmt *stmt);

