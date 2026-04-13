/*
 * builtins.h — Built-in Functions for SixSeven
 *
 * btw, these are the built-in functions.
 * btw, some of them are chaotic. this was not an accident.
 * btw, vibeCheck() may crash your program. that's the point.
 */

#ifndef BUILTINS_H
#define BUILTINS_H

#include "value.h"

typedef Value (*NativeFn)(Value* args, int num_args);

/* core chaos functions */
Value builtin_scream_into(Value* args, int num_args);   /* screamInto() — print with drama */
Value builtin_chaos(Value* args, int num_args);          /* chaos()      — unpredictable by design */
Value builtin_vibe_check(Value* args, int num_args);     /* vibeCheck()  — 50/50 chance of death */

/* legacy functions (still work, still unhinged) */
Value builtin_printf_troll(Value* args, int num_args);   /* alias for screamInto */
Value builtin_panic67(Value* args, int num_args);
Value builtin_compile_na_sorte(Value* args, int num_args);
Value builtin_loop_infinito_de_praia(Value* args, int num_args);
Value builtin_segfault_de_brincadeira(Value* args, int num_args);
Value builtin_converter_para_decimal(Value* args, int num_args);
Value builtin_tamanho_em_bytes(Value* args, int num_args);
Value builtin_imprimir_base67(Value* args, int num_args);

int     is_builtin(const char* name);
NativeFn builtin_get_function(const char* name);

#endif
