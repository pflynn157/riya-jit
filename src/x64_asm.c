#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "jit.h"
#include "ir.h"

//
// Register definitions
//
enum x64_reg {
    AX = 0,
    BX = 3,
    CX = 1,
    DX = 2,
};

enum x86_op {
    ADD_RR = 0x01,
    MOV_RR = 0x89,
    RET = 0xC3,
};

uint8_t movi_ops[] = {
    // ax  bx    cx    dx     di    si
    0xB8, 0xBB, 0xB9, 0xBA, 0xBF, 0xBE,
};

uint8_t movi_ops_sa[] = {
    0xB8, //ax
    0xBF, //di
    0xBE, //si
    0xBA, //dx
    0xBB, //bx
    0xB9, //cx
    
};

uint8_t reg_ops[] = {
    AX, BX, CX, DX
};

// Utility functions
void x64_asm_irr(eng_context *ctx, ry_kind type, uint8_t opcode, uint64_t dest, uint64_t src1) {
    // TODO: Check data types
    ctx->memory[ctx->memory_index] = opcode;
    ctx->memory_index += 1;
    
    // Generate the operand
    uint8_t op = 0b11000000;
    op |= reg_ops[src1] << 3;
    op |= reg_ops[dest];
    
    ctx->memory[ctx->memory_index] = op;
    ctx->memory_index += 1;
}

//
// x86 MOV
//
// Immediate to register
void x64_asm_movi(eng_context *ctx, ry_kind type, ry_kind dest_type, uint64_t dest, uint64_t src1) {
    if (type == t_m8) {
        ctx->memory[ctx->memory_index] = 0x48;
        ctx->memory_index += 1;
    }
    
    uint8_t op = 0;
    if (dest_type == k_reg) op = movi_ops[dest];
    else if (dest_type == k_sa_reg) op = movi_ops_sa[dest];
    
    ctx->memory[ctx->memory_index] = op;
    ctx->memory_index += 1;
    
    if (type == t_m8) {
        memcpy(&ctx->memory[ctx->memory_index], &src1, 8);
        ctx->memory_index += 8;
    } else {
        memcpy(&ctx->memory[ctx->memory_index], &src1, 4);
        ctx->memory_index += 4;
    }
}

// The entry point for all moves
void x64_asm_mov(eng_context *ctx, ry_kind type, ry_kind dest_type, uint64_t dest, ry_kind src1_type, uint64_t src1) {
    if (src1_type == k_imm) {
        x64_asm_movi(ctx, type, dest_type, dest, src1);
    } else if (src1_type == k_reg) {
        x64_asm_irr(ctx, type, MOV_RR, dest, src1);
    }
}

//
// x86 returns
//
void x64_asm_ret(eng_context *ctx, ry_stmt *stmt) {
    // Generate the mov
    x64_asm_mov(ctx, stmt->type, k_reg, 0, stmt->src1_type, stmt->src1);
    
    // Generate the return
    // ret = 0xC3
    ctx->memory[ctx->memory_index] = RET;
    ctx->memory_index += 1;
}

void x64_asm_ret_void(eng_context *ctx) {
    // Generate the return
    // ret = 0xC3
    ctx->memory[ctx->memory_index] = RET;
    ctx->memory_index += 1;
}

//
// x86 syscall
//
void x64_asm_syscall(eng_context *ctx) {
    // syscall = 0x0f 0x05
    ctx->memory[ctx->memory_index] = 0x0f;
    ctx->memory[ctx->memory_index+1] = 0x05;
    ctx->memory_index += 2;
}

//
// The entry point for assembling x86 statements
//
void x64_asm_stmt(eng_context *ctx, ry_stmt *stmt) {
    switch (stmt->kind) {
        case k_mov: x64_asm_mov(ctx, stmt->type, stmt->dest_type, stmt->dest, stmt->src1_type, stmt->src1); break;
        case k_li: x64_asm_movi(ctx, stmt->type, stmt->dest_type, stmt->dest, stmt->src1); break;
        case k_alloca: break;
        case k_load: break;
        case k_store: break;
        
        // TODO: This only assumes we have registers
        case k_add: {
            x64_asm_movi(ctx, stmt->type, stmt->dest_type, stmt->dest, 0);
            x64_asm_irr(ctx, stmt->type, ADD_RR, stmt->dest, stmt->src1);
            x64_asm_irr(ctx, stmt->type, ADD_RR, stmt->dest, stmt->src2);
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
        
        case k_ret: x64_asm_ret(ctx, stmt); break;
        case k_ret_void: x64_asm_ret_void(ctx); break;
        case k_call: break;
        case k_syscall: x64_asm_syscall(ctx); break;
        
        default: {}
    }
}

