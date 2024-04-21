#include <stdio.h>

#include "ir.h"
#include "asm_printer.h"
#include "jit.h"

void test1() {
    // li 10 to r0 as m4
    ry_stmt instr1 = { .kind = k_li, .type = t_m4,
                       .dest_type = k_reg, .dest = 0,
                       .src1_type = k_imm, .src1 = 10};
    ry_debug_stmt(&instr1);
    
    // li 20 to r1 as m4
    ry_stmt instr2 = { .kind = k_li, .type = t_m4,
                       .dest_type = k_reg, .dest = 1,
                       .src1_type = k_imm, .src1 = 20};
    ry_debug_stmt(&instr2);
    
    // add r0 r1 to r2 as m4
    ry_stmt instr3 = { .kind = k_add, .type = t_m4,
                       .dest_type = k_reg, .dest = 2,
                       .src1_type = k_reg, .src1 = 0,
                       .src2_type = k_reg, .src2 = 1};
    ry_debug_stmt(&instr3);
    
    // ret r2 as m4
    ry_stmt instr4 = { .kind = k_ret, .type = t_m4,
                       .src1_type = k_reg, .src1 = 2};
    ry_debug_stmt(&instr4);
    
    // Test assembly printing
    puts("----------------------");
    
    FILE *f = x64_init(NULL);
    x64_generate_function(f, "main");
    x64_generate_stmt(f, &instr1);
    x64_generate_stmt(f, &instr2);
    x64_generate_stmt(f, &instr3);
    x64_generate_stmt(f, &instr4);
    x64_close(f);
    
    // Test JIT
    puts("----------------------");
    
    eng_context *ctx = eng_init();
    x64_asm_stmt(ctx, &instr1);
    x64_asm_stmt(ctx, &instr2);
    x64_asm_stmt(ctx, &instr3);
    x64_asm_stmt(ctx, &instr4);
    eng_dump(ctx);
    eng_run(ctx);
}

void test2() {
    // li 1 to sa0 as m4
    ry_stmt instr1 = { .kind = k_li, .type = t_m4,
                       .dest_type = k_sa_reg, .dest = 0,
                       .src1_type = k_imm, .src1 = 1};
    ry_debug_stmt(&instr1);
    
    // li 1 to sa1 as m4
    ry_stmt instr2 = { .kind = k_li, .type = t_m4,
                       .dest_type = k_sa_reg, .dest = 1,
                       .src1_type = k_imm, .src1 = 1};
    ry_debug_stmt(&instr2);
    
    // li STR1 to sa2 as m4
    ry_stmt instr3 = { .kind = k_li, .type = t_m8,
                       .dest_type = k_sa_reg, .dest = 2,
                       .src1_type = k_loc, .src1_label = "STR1"};
    ry_debug_stmt(&instr3);
    
    // li 4 to sa3 as m4
    ry_stmt instr4 = { .kind = k_li, .type = t_m4,
                       .dest_type = k_sa_reg, .dest = 3,
                       .src1_type = k_imm, .src1 = 4};
    ry_debug_stmt(&instr4);
    
    // syscall
    ry_stmt instr5 = { .kind = k_syscall, .type = t_void };
    ry_debug_stmt(&instr5);
    
    // ret.void
    ry_stmt instr6 = { .kind = k_ret_void, .type = t_void };
    ry_debug_stmt(&instr6);
    
    // Test assembly printing
    /*puts("----------------------");
    
    FILE *f = x64_init(NULL);
    x64_generate_function(f, "main");
    x64_generate_stmt(f, &instr1);
    x64_generate_stmt(f, &instr2);
    x64_generate_stmt(f, &instr3);
    x64_generate_stmt(f, &instr4);
    x64_close(f);*/
    
    // Test JIT
    puts("----------------------");
    
    eng_context *ctx = eng_init();
    
    char *s = "Hi!\n";
    memcpy(ctx->data, s, strlen(s));
    
    // Set the third instruction
    instr3.src1_type = k_imm;
    instr3.src1 = ctx->data;
    instr3.src1_label = NULL;
    ry_debug_stmt(&instr3);
    puts("----------------------");
    
    // Assemble
    x64_asm_stmt(ctx, &instr1);
    x64_asm_stmt(ctx, &instr2);
    x64_asm_stmt(ctx, &instr3);
    x64_asm_stmt(ctx, &instr4);
    x64_asm_stmt(ctx, &instr5);
    x64_asm_stmt(ctx, &instr6);
    eng_dump(ctx);
    eng_run(ctx);
}

int main(int argc, char *argv[]) {
    test2();
    return 0;
}

