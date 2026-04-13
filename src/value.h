/*
 * value.h - Tipo de valor genérico para Base SixSeven
 * 
 * Representa qualquer valor na linguagem: número (base 67), texto, booleano, etc.
 */

#ifndef VALUE_H
#define VALUE_H

#include <stdint.h>

typedef enum {
    VALUE_NUMERO,       /* long long em base 67 */
    VALUE_TEXTO,        /* string */
    VALUE_BOOL,         /* booleano */
    VALUE_NULO,         /* null */
    VALUE_FUNCAO,       /* função (pointer) */
    VALUE_OBJETO        /* objeto/struct */
} ValueType;

typedef struct Value {
    ValueType type;
    union {
        long long numero;       /* base 67, armazenado como decimal */
        char* texto;
        int boolean;            /* 0 ou 1 */
        void* ptr;              /* para funções e objetos */
    } dados;
} Value;

/* Criar valores */
Value value_numero(long long n);        /* Em base 67 */
Value value_texto(const char* s);
Value value_bool(int b);
Value value_nulo(void);

/* Converter para string para impressão */
char* value_to_string(Value v);

/* Converter número base 67 para string em base 67 */
char* value_numero_to_base67(Value v);

/* Liberar memória */
void value_free(Value v);

/* Comparar valores */
int value_equal(Value a, Value b);

#endif
