/*
 * base67.h - Conversão entre Base 67 e Decimal
 * 
 * Base SixSeven: Linguagem real com aritmética em base 67
 * Todos os números são base 67. Isso não é uma piada.
 */

#ifndef BASE67_H
#define BASE67_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
 * Alfabeto Base 67:
 * Posições 0-9:    dígitos "0123456789"
 * Posições 10-35:  minúsculas "abcdefghijklmnopqrstuvwxyz"
 * Posições 36-61:  maiúsculas "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
 * Posições 62-66:  símbolos "!@#$%"
 */

#define BASE67_ALPHABET "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%"
#define BASE67_RADIX 67

/* Converte caractere de dígito base 67 para seu valor (0-66) */
int base67_char_value(char c);

/* Converte valor (0-66) para caractere base 67 */
char base67_value_to_char(int val);

/* Converte string em base 67 para valor decimal (long long) */
long long base67_to_decimal(const char* str);

/* Converte valor decimal para string em base 67 (retorna buffer alocado) */
char* decimal_to_base67(long long value);

/* Valida se uma string é um número válido em base 67 */
int is_valid_base67_number(const char* str);

/* Printa um número em base 67 formatado (para debug) */
void print_base67(long long value);

#endif
