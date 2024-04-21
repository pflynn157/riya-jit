#include <stdio.h>

#include "ir.h"
#include "asm_printer.h"
#include "jit.h"

int main(int argc, char *argv[]) {
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
    
    return 0;
}

