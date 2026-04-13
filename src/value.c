/*
 * value.c — Generic Value Implementation
 *
 * btw, bestie = true, betrayal = false, theVoid = null.
 * btw, the naming reflects the emotional journey of this runtime.
 */

#include "value.h"
#include "base67.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Value value_numero(long long n) {
    Value v;
    v.type = VALUE_NUMERO;
    v.dados.numero = n;
    return v;
}

Value value_texto(const char* s) {
    Value v;
    v.type = VALUE_TEXTO;
    v.dados.texto = s ? (char*)malloc(strlen(s) + 1) : NULL;
    if (v.dados.texto) strcpy(v.dados.texto, s);
    return v;
}

Value value_bool(int b) {
    Value v;
    v.type = VALUE_BOOL;
    v.dados.boolean = b ? 1 : 0;
    return v;
}

Value value_nulo(void) {
    Value v;
    v.type = VALUE_NULO;
    return v;
}

char* value_numero_to_base67(Value v) {
    if (v.type != VALUE_NUMERO) return NULL;
    return decimal_to_base67(v.dados.numero);
}

char* value_to_string(Value v) {
    char* result = (char*)malloc(256);

    switch (v.type) {
        case VALUE_NUMERO: {
            char* b67 = value_numero_to_base67(v);
            strcpy(result, b67);
            free(b67);
            break;
        }
        case VALUE_TEXTO:
            strcpy(result, v.dados.texto ? v.dados.texto : "(theVoid)");
            break;
        case VALUE_BOOL:
            strcpy(result, v.dados.boolean ? "bestie" : "betrayal");
            break;
        case VALUE_NULO:
            strcpy(result, "theVoid");
            break;
        case VALUE_FUNCAO:
            strcpy(result, "<ritual>");
            break;
        case VALUE_OBJETO:
            strcpy(result, "<lore>");
            break;
        default:
            strcpy(result, "???");
    }

    return result;
}

void value_free(Value v) {
    if (v.type == VALUE_TEXTO && v.dados.texto) {
        free(v.dados.texto);
    }
}

int value_equal(Value a, Value b) {
    if (a.type != b.type) return 0;

    switch (a.type) {
        case VALUE_NUMERO:
            return a.dados.numero == b.dados.numero;
        case VALUE_TEXTO:
            return strcmp(a.dados.texto ? a.dados.texto : "",
                         b.dados.texto ? b.dados.texto : "") == 0;
        case VALUE_BOOL:
            return a.dados.boolean == b.dados.boolean;
        case VALUE_NULO:
            return 1;
        default:
            return 0;
    }
}
