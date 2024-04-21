#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h>

#include "ir.h"

typedef struct {
    uint8_t *memory;
    int memory_size;
    int memory_index;
    
    uint8_t *data;
    int data_size;
    int data_index;
} eng_context;

eng_context *eng_init();
void eng_dump(eng_context *ctx);
void eng_run(eng_context *ctx);

// Assembly functions for x86-64
void x64_asm_stmt(eng_context *ctx, ry_stmt *stmt);

