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
} eng_context;

eng_context *eng_init();
void eng_run(eng_context *ctx);

