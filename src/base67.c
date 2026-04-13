/*
 * base67.c - Implementação de Conversão Base 67
 */

#include "base67.h"
#include <ctype.h>
#include <stdio.h>

int base67_char_value(char c) {
    if (c >= '0' && c <= '9') return c - '0';           /* 0-9 */
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;      /* 10-35 */
    if (c >= 'A' && c <= 'Z') return c - 'A' + 36;      /* 36-61 */
    
    /* Símbolos especiais */
    switch (c) {
        case '!': return 62;
        case '@': return 63;
        case '#': return 64;
        case '$': return 65;
        case '%': return 66;
        default: return -1;  /* Inválido */
    }
}

char base67_value_to_char(int val) {
    if (val < 0 || val >= BASE67_RADIX) return '?';  /* Inválido */
    return BASE67_ALPHABET[val];
}

int is_valid_base67_number(const char* str) {
    if (!str || strlen(str) == 0) return 0;
    
    for (int i = 0; str[i]; i++) {
        if (base67_char_value(str[i]) == -1) {
            return 0;  /* Caractere inválido para base 67 */
        }
    }
    return 1;
}

long long base67_to_decimal(const char* str) {
    if (!str || strlen(str) == 0) return 0;
    
    long long result = 0;
    long long power = 1;
    int len = strlen(str);
    
    /* Processa dígitos da direita para esquerda */
    for (int i = len - 1; i >= 0; i--) {
        int digit_val = base67_char_value(str[i]);
        if (digit_val == -1) {
            /* Erro: caractere inválido */
            fprintf(stderr, "Erro: Caractere '%c' não é válido em base 67\n", str[i]);
            return 0;
        }
        result += digit_val * power;
        power *= BASE67_RADIX;
    }
    
    return result;
}

char* decimal_to_base67(long long value) {
    if (value == 0) {
        char* result = (char*)malloc(2);
        strcpy(result, "0");
        return result;
    }
    
    char buffer[100];
    int pos = 0;
    long long v = value;
    
    while (v > 0) {
        int remainder = v % BASE67_RADIX;
        buffer[pos++] = base67_value_to_char(remainder);
        v /= BASE67_RADIX;
    }
    
    /* Reverter */
    char* result = (char*)malloc(pos + 1);
    for (int i = 0; i < pos; i++) {
        result[i] = buffer[pos - 1 - i];
    }
    result[pos] = '\0';
    
    return result;
}

void print_base67(long long value) {
    char* str = decimal_to_base67(value);
    printf("%s", str);
    free(str);
}
