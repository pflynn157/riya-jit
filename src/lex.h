#pragma once

#include <stdio.h>

typedef enum {
    l_func,
    l_is, l_begin, l_end,
    l_to, l_as,
    
    l_li,
    l_add,
    l_ret,
    
    l_m4, l_m8,
    
    l_id, l_imm,
} lex_kind;

typedef struct {
    FILE *file;
} lex;

//lex *lex_init(char *path);
//lex_kind lex_get_next();

