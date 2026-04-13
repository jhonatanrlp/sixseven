/*
 * memory.c - Gerenciamento de Memória
 */

#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

void* xmalloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr && size > 0) {
        fprintf(stderr, "Erro: Falha ao alocar %zu bytes\n", size);
        exit(1);
    }
    return ptr;
}

void* xrealloc(void* ptr, size_t size) {
    void* new_ptr = realloc(ptr, size);
    if (!new_ptr && size > 0) {
        fprintf(stderr, "Erro: Falha ao realocar para %zu bytes\n", size);
        exit(1);
    }
    return new_ptr;
}

void xfree(void* ptr) {
    if (ptr) free(ptr);
}
