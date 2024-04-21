#include "jit.h"
#include "ir.h"

//
// Initialize the JIT context
//
eng_context *eng_init() {
    eng_context *ctx = malloc(sizeof(eng_context));
    ctx->memory_size = 1024;
    ctx->memory_index = 0;
    ctx->memory = mmap(0, ctx->memory_size, PROT_READ | PROT_WRITE | PROT_EXEC,
                        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    
    ctx->data_size = 1024;
    ctx->data_index = 0;
    ctx->data = malloc(sizeof(uint8_t) * ctx->data_size);
    return ctx;
}

//
// Perform a hexdump of the JIT memory
//
void eng_dump(eng_context *ctx) {
    for (int i = 0; i<ctx->memory_index; i++) {
        printf("%x ", ctx->memory[i]);
    }
    printf("\n");
}

//
// Run the JIT engine
//
void eng_run(eng_context *ctx) {
    typedef int (*JITMemory)();
    
    JITMemory func = (JITMemory)ctx->memory;
    int result = func();
    printf("result = %d\n", result);
}

