/*
 * parser.h - Parser (Análise Sintática)
 * 
 * Converte tokens em árvore de sintaxe abstrata (AST)
 */

#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct {
    Token* tokens;
    int num_tokens;
    int current;
} Parser;

/* Criar parser a partir de tokens */
Parser* parser_create(Token* tokens, int num_tokens);

/* Parse programa completo */
ASTNode* parser_parse(Parser* parser);

/* Liberar parser */
void parser_free(Parser* parser);

/* Obter último erro (se houver) */
const char* parser_get_error(Parser* parser);

#endif
