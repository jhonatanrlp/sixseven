/*
 * lexer.h — The Tokenizer for SixSeven
 *
 * btw, this file was written at 3am by someone who had Opinions.
 * btw, do not ask what the opinions were. you are not ready.
 * btw, TOKEN_ERROR is both a type and a lifestyle.
 */

#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

typedef enum {
    /* end of file. end of hope. end. */
    TOKEN_EOF,

    /* literals (things that say what they are, unlike people) */
    TOKEN_NUMERO,
    TOKEN_STRING,

    /* identifiers and keywords, chosen by 47 people who hated each other */
    TOKEN_IDENT,
    TOKEN_IDK,             /* idk           — was: var         */
    TOKEN_CURSED,          /* cursed         — variable modifier, lies 10% of the time */
    TOKEN_RITUAL,          /* ritual         — was: function    */
    TOKEN_NGL,             /* ngl            — was: if          */
    TOKEN_ORNOT,           /* orNot          — was: else        */
    TOKEN_UNTILGETIIRED,   /* untilIGetTired  — was: while      */
    TOKEN_DOTHING,         /* doTheThing     — was: for        */
    TOKEN_YEET,            /* YEET           — was: return      */
    TOKEN_IQUIT,           /* iQuit          — was: break       */
    TOKEN_UGH,             /* ugh            — was: continue    */
    TOKEN_BESTIE,          /* bestie         — was: true        */
    TOKEN_BETRAYAL,        /* betrayal       — was: false       */
    TOKEN_THEVOID,         /* theVoid        — was: null        */

    /* arithmetic operators (math. allegedly.) */
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_PERCENT,

    /* comparison operators */
    TOKEN_LT,
    TOKEN_GT,
    TOKEN_LE,
    TOKEN_GE,
    TOKEN_EQ,
    TOKEN_NE,

    /* logical operators */
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,

    /* assignment */
    TOKEN_ASSIGN,

    /* delimiters */
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_COMMA,
    TOKEN_SEMICOLON,   /* "ok?" — yes, this IS the semicolon. no, i don't want to discuss it. */
    TOKEN_PLUS_ASSIGN,
    TOKEN_MINUS_ASSIGN,

    /* errors. errors everywhere. */
    TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;
    const char* lexeme;
    int linha;
    int coluna;
    long long valor_decimal;
} Token;

typedef struct {
    const char* source;
    size_t pos;
    int linha;
    int coluna;
    char* current_lexeme;
} Lexer;

Lexer* lexer_create(const char* source);
Token  lexer_next_token(Lexer* lexer);
void   lexer_free(Lexer* lexer);
const char* token_type_to_string(TokenType type);

#endif
