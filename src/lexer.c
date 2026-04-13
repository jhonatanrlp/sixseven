/*
 * lexer.c — Tokenizer Implementation
 *
 * btw, ALL numbers are interpreted in base 67. this is non-negotiable.
 * btw, "ok?" is a valid semicolon. yes. ok?
 * btw, comments start with "btw," because obviously.
 * btw, if your file doesn't start with WAKEY WAKEY, it's not our problem.
 */

#include "lexer.h"
#include "base67.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

typedef struct {
    const char* str;
    TokenType type;
} KeywordEntry;

/*
 * keywords — chosen by 47 people who hated each other.
 * no one agrees on anything. this was intentional.
 */
static const KeywordEntry keywords[] = {
    {"idk",            TOKEN_IDK},
    {"cursed",         TOKEN_CURSED},
    {"ritual",         TOKEN_RITUAL},
    {"ngl",            TOKEN_NGL},
    {"orNot",          TOKEN_ORNOT},
    {"untilIGetTired", TOKEN_UNTILGETIIRED},
    {"doTheThing",     TOKEN_DOTHING},
    {"YEET",           TOKEN_YEET},
    {"iQuit",          TOKEN_IQUIT},
    {"ugh",            TOKEN_UGH},
    {"bestie",         TOKEN_BESTIE},
    {"betrayal",       TOKEN_BETRAYAL},
    {"theVoid",        TOKEN_THEVOID},
    {NULL, TOKEN_ERROR}
};

static TokenType check_keyword(const char* lexeme) {
    for (int i = 0; keywords[i].str; i++) {
        if (strcmp(keywords[i].str, lexeme) == 0) {
            return keywords[i].type;
        }
    }
    return TOKEN_IDENT;
}

Lexer* lexer_create(const char* source) {
    Lexer* lexer = (Lexer*)malloc(sizeof(Lexer));
    lexer->source = source;
    lexer->pos = 0;
    lexer->linha = 1;
    lexer->coluna = 1;
    lexer->current_lexeme = (char*)malloc(1024);
    return lexer;
}

static void skip_whitespace(Lexer* lex) {
    while (lex->pos < strlen(lex->source)) {
        char c = lex->source[lex->pos];
        if (c == ' ' || c == '\t') {
            lex->pos++;
            lex->coluna++;
        } else if (c == '\n') {
            lex->pos++;
            lex->linha++;
            lex->coluna = 1;
        } else {
            break;
        }
    }
}

/*
 * skip_comment — handles both '#' and 'btw,' style comments.
 * btw, "btw," is the comment syntax because we said so.
 */
static void skip_comment(Lexer* lex) {
    size_t src_len = strlen(lex->source);

    /* old-school '#' comment */
    if (lex->source[lex->pos] == '#') {
        while (lex->pos < src_len && lex->source[lex->pos] != '\n') {
            lex->pos++;
        }
        return;
    }

    /* "btw," comment — the civilized option */
    if (lex->pos + 4 <= src_len &&
        strncmp(&lex->source[lex->pos], "btw,", 4) == 0) {
        while (lex->pos < src_len && lex->source[lex->pos] != '\n') {
            lex->pos++;
        }
    }
}

static int is_comment_start(Lexer* lex) {
    size_t src_len = strlen(lex->source);
    if (lex->pos >= src_len) return 0;
    if (lex->source[lex->pos] == '#') return 1;
    if (lex->pos + 4 <= src_len &&
        strncmp(&lex->source[lex->pos], "btw,", 4) == 0) return 1;
    return 0;
}

static int is_base67_digit(char c) {
    return base67_char_value(c) != -1;
}

static Token make_token(TokenType type, const char* lexeme, int linha, int coluna, long long valor_decimal) {
    Token tok;
    tok.type = type;
    tok.lexeme = lexeme;
    tok.linha = linha;
    tok.coluna = coluna;
    tok.valor_decimal = valor_decimal;
    return tok;
}

Token lexer_next_token(Lexer* lex) {
    skip_whitespace(lex);

    /* skip comments — both btw, and # flavors */
    while (is_comment_start(lex)) {
        skip_comment(lex);
        skip_whitespace(lex);
    }

    if (lex->pos >= strlen(lex->source)) {
        return make_token(TOKEN_EOF, "", lex->linha, lex->coluna, 0);
    }

    char c = lex->source[lex->pos];
    int linha = lex->linha;
    int coluna = lex->coluna;

    /* base 67 numbers */
    if (is_base67_digit(c)) {
        int lexeme_start = lex->pos;
        while (lex->pos < strlen(lex->source) && is_base67_digit(lex->source[lex->pos])) {
            lex->pos++;
            lex->coluna++;
        }

        int len = lex->pos - lexeme_start;
        strncpy(lex->current_lexeme, &lex->source[lexeme_start], len);
        lex->current_lexeme[len] = '\0';

        long long valor = base67_to_decimal(lex->current_lexeme);
        return make_token(TOKEN_NUMERO, lex->current_lexeme, linha, coluna, valor);
    }

    /* identifiers and keywords */
    if (isalpha(c) || c == '_') {
        int lexeme_start = lex->pos;
        while (lex->pos < strlen(lex->source) &&
               (isalnum(lex->source[lex->pos]) || lex->source[lex->pos] == '_')) {
            lex->pos++;
            lex->coluna++;
        }

        int len = lex->pos - lexeme_start;
        strncpy(lex->current_lexeme, &lex->source[lexeme_start], len);
        lex->current_lexeme[len] = '\0';

        /* "ok?" — the semicolon we deserved */
        if (strcmp(lex->current_lexeme, "ok") == 0 &&
            lex->pos < strlen(lex->source) &&
            lex->source[lex->pos] == '?') {
            lex->pos++;
            lex->coluna++;
            return make_token(TOKEN_SEMICOLON, "ok?", linha, coluna, 0);
        }

        TokenType type = check_keyword(lex->current_lexeme);
        return make_token(type, lex->current_lexeme, linha, coluna, 0);
    }

    /* strings */
    if (c == '"') {
        lex->pos++;
        lex->coluna++;
        int lexeme_start = lex->pos;

        while (lex->pos < strlen(lex->source) && lex->source[lex->pos] != '"') {
            if (lex->source[lex->pos] == '\\' && lex->pos + 1 < strlen(lex->source)) {
                lex->pos += 2;
                lex->coluna += 2;
            } else {
                lex->pos++;
                lex->coluna++;
            }
        }

        if (lex->pos < strlen(lex->source)) {
            lex->pos++;
            lex->coluna++;
        }

        int len = lex->pos - lexeme_start - 1;
        if (len < 0) len = 0;
        strncpy(lex->current_lexeme, &lex->source[lexeme_start], len);
        lex->current_lexeme[len] = '\0';

        return make_token(TOKEN_STRING, lex->current_lexeme, linha, coluna, 0);
    }

    /* operators and delimiters */
    lex->pos++;
    lex->coluna++;

    switch (c) {
        case '+':
            if (lex->pos < strlen(lex->source) && lex->source[lex->pos] == '=') {
                lex->pos++; lex->coluna++;
                return make_token(TOKEN_PLUS_ASSIGN, "+=", linha, coluna, 0);
            }
            return make_token(TOKEN_PLUS, "+", linha, coluna, 0);
        case '-':
            if (lex->pos < strlen(lex->source) && lex->source[lex->pos] == '=') {
                lex->pos++; lex->coluna++;
                return make_token(TOKEN_MINUS_ASSIGN, "-=", linha, coluna, 0);
            }
            return make_token(TOKEN_MINUS, "-", linha, coluna, 0);
        case '*':
            return make_token(TOKEN_STAR, "*", linha, coluna, 0);
        case '/':
            return make_token(TOKEN_SLASH, "/", linha, coluna, 0);
        case '%':
            return make_token(TOKEN_PERCENT, "%", linha, coluna, 0);
        case '<':
            if (lex->pos < strlen(lex->source) && lex->source[lex->pos] == '=') {
                lex->pos++; lex->coluna++;
                return make_token(TOKEN_LE, "<=", linha, coluna, 0);
            }
            return make_token(TOKEN_LT, "<", linha, coluna, 0);
        case '>':
            if (lex->pos < strlen(lex->source) && lex->source[lex->pos] == '=') {
                lex->pos++; lex->coluna++;
                return make_token(TOKEN_GE, ">=", linha, coluna, 0);
            }
            return make_token(TOKEN_GT, ">", linha, coluna, 0);
        case '=':
            if (lex->pos < strlen(lex->source) && lex->source[lex->pos] == '=') {
                lex->pos++; lex->coluna++;
                return make_token(TOKEN_EQ, "==", linha, coluna, 0);
            }
            return make_token(TOKEN_ASSIGN, "=", linha, coluna, 0);
        case '!':
            if (lex->pos < strlen(lex->source) && lex->source[lex->pos] == '=') {
                lex->pos++; lex->coluna++;
                return make_token(TOKEN_NE, "!=", linha, coluna, 0);
            }
            return make_token(TOKEN_NOT, "!", linha, coluna, 0);
        case '&':
            if (lex->pos < strlen(lex->source) && lex->source[lex->pos] == '&') {
                lex->pos++; lex->coluna++;
                return make_token(TOKEN_AND, "&&", linha, coluna, 0);
            }
            break;
        case '|':
            if (lex->pos < strlen(lex->source) && lex->source[lex->pos] == '|') {
                lex->pos++; lex->coluna++;
                return make_token(TOKEN_OR, "||", linha, coluna, 0);
            }
            break;
        case '(':  return make_token(TOKEN_LPAREN,  "(", linha, coluna, 0);
        case ')':  return make_token(TOKEN_RPAREN,  ")", linha, coluna, 0);
        case '{':  return make_token(TOKEN_LBRACE,  "{", linha, coluna, 0);
        case '}':  return make_token(TOKEN_RBRACE,  "}", linha, coluna, 0);
        case ',':  return make_token(TOKEN_COMMA,   ",", linha, coluna, 0);
        case ';':  return make_token(TOKEN_SEMICOLON, ";", linha, coluna, 0);
    }

    return make_token(TOKEN_ERROR, "?", linha, coluna, 0);
}

void lexer_free(Lexer* lex) {
    if (lex) {
        free(lex->current_lexeme);
        free(lex);
    }
}

const char* token_type_to_string(TokenType type) {
    switch (type) {
        case TOKEN_EOF:           return "EOF";
        case TOKEN_NUMERO:        return "NUMERO";
        case TOKEN_STRING:        return "STRING";
        case TOKEN_IDENT:         return "IDENT";
        case TOKEN_IDK:           return "idk";
        case TOKEN_CURSED:        return "cursed";
        case TOKEN_RITUAL:        return "ritual";
        case TOKEN_NGL:           return "ngl";
        case TOKEN_ORNOT:         return "orNot";
        case TOKEN_UNTILGETIIRED: return "untilIGetTired";
        case TOKEN_DOTHING:       return "doTheThing";
        case TOKEN_YEET:          return "YEET";
        case TOKEN_IQUIT:         return "iQuit";
        case TOKEN_UGH:           return "ugh";
        case TOKEN_BESTIE:        return "bestie";
        case TOKEN_BETRAYAL:      return "betrayal";
        case TOKEN_THEVOID:       return "theVoid";
        case TOKEN_PLUS:          return "+";
        case TOKEN_MINUS:         return "-";
        case TOKEN_STAR:          return "*";
        case TOKEN_SLASH:         return "/";
        case TOKEN_PERCENT:       return "%";
        case TOKEN_LT:            return "<";
        case TOKEN_GT:            return ">";
        case TOKEN_LE:            return "<=";
        case TOKEN_GE:            return ">=";
        case TOKEN_EQ:            return "==";
        case TOKEN_NE:            return "!=";
        case TOKEN_AND:           return "&&";
        case TOKEN_OR:            return "||";
        case TOKEN_NOT:           return "!";
        case TOKEN_ASSIGN:        return "=";
        case TOKEN_LPAREN:        return "(";
        case TOKEN_RPAREN:        return ")";
        case TOKEN_LBRACE:        return "{";
        case TOKEN_RBRACE:        return "}";
        case TOKEN_COMMA:         return ",";
        case TOKEN_SEMICOLON:     return "ok?";
        default:                  return "?";
    }
}
