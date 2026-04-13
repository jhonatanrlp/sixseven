/*
 * memory.h - Gerenciamento de Memória
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

void* xmalloc(size_t size);
void* xrealloc(void* ptr, size_t size);
void xfree(void* ptr);

#endif
