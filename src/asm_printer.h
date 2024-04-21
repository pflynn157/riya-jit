#pragma once

#include "ir.h"

// The x86-64 (x64) printers
FILE *x64_init(char *output_file);
void x64_close(FILE *file);
void x64_generate_function(FILE *file, char *name);   // TODO: This will be changed
void x64_generate_stmt(FILE *file, ry_stmt *stmt);

