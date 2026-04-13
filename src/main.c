/*
 * main.c — Entry Point for the SixSeven Interpreter
 *
 * btw, ALL numbers are in base 67. this is not up for debate.
 * btw, your file MUST start with WAKEY WAKEY or we're not doing anything.
 * btw, the language is watching you. it has opinions. they're not good.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base67.h"
#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "runtime.h"

static char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "never heard of her. (couldn't open file '%s')\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(size + 1);
    if (!buffer) {
        fprintf(stderr, "oh honey, no. memory allocation failed. we can't even start.\n");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, size, file);
    buffer[size] = '\0';
    fclose(file);

    return buffer;
}

static void print_tokens(Token* tokens, int num_tokens) {
    printf("\n=== TOKEN DUMP (you asked for this) ===\n");
    for (int i = 0; i < num_tokens; i++) {
        printf("[%d] %s: '%s' (line %d, col %d)\n",
               i, token_type_to_string(tokens[i].type),
               tokens[i].lexeme, tokens[i].linha, tokens[i].coluna);
        if (tokens[i].type == TOKEN_NUMERO) {
            printf("    base67 value → decimal: %lld\n", tokens[i].valor_decimal);
        }
    }
    printf("\n");
}

static void check_wakey_wakey(const char* source) {
    const char* s = source;
    /* skip leading whitespace (generous, because mornings are hard) */
    while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r') s++;

    if (strncmp(s, "WAKEY WAKEY", 11) != 0) {
        fprintf(stderr, "\n");
        fprintf(stderr, "did you forget to say good morning??? rude.\n");
        fprintf(stderr, "\n");
        fprintf(stderr, "your file must start with:\n");
        fprintf(stderr, "  WAKEY WAKEY\n");
        fprintf(stderr, "\n");
        fprintf(stderr, "not 'hello', not a comment, not a function.\n");
        fprintf(stderr, "WAKEY WAKEY. two words. uppercase. non-negotiable.\n");
        fprintf(stderr, "the language will not compile your code if you cannot\n");
        fprintf(stderr, "be bothered to say good morning. that's just basic manners.\n");
        fprintf(stderr, "\n");
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    printf("\n");
    printf("░██████╗██╗██╗  ██╗███████╗███████╗██╗   ██╗███████╗███╗  ██╗\n");
    printf("██╔════╝██║╚██╗██╔╝██╔════╝██╔════╝██║   ██║██╔════╝████╗ ██║\n");
    printf("╚█████╗ ██║ ╚███╔╝ ███████╗█████╗  ██║   ██║█████╗  ██╔██╗██║\n");
    printf(" ╚═══██╗██║ ██╔██╗ ╚════██║██╔══╝  ╚██╗ ██╔╝██╔══╝  ██║╚████║\n");
    printf("██████╔╝██║██╔╝╚██╗███████║███████╗ ╚████╔╝ ███████╗██║ ╚███║\n");
    printf("╚═════╝ ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝  ╚═══╝  ╚══════╝╚═╝  ╚══╝\n");
    printf("\n");
    printf("  the programming language designed by 47 people who hated each other\n");
    printf("  all numbers are in base 67. this is not a joke. this is not a phase.\n");
    printf("\n");

    if (argc < 2) {
        printf("usage: sixseven <file.67> [--debug-tokens] [--debug-ast]\n");
        printf("\nexample:\n");
        printf("  sixseven hello_world.67\n");
        printf("  sixseven fibonacci.67 --debug-tokens\n");
        printf("\nremember: your file must start with WAKEY WAKEY.\n");
        printf("           yes, seriously. WAKEY WAKEY.\n");
        return 1;
    }

    int debug_tokens = 0;
    int debug_ast = 0;

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--debug-tokens") == 0) debug_tokens = 1;
        if (strcmp(argv[i], "--debug-ast")    == 0) debug_ast    = 1;
    }

    /* read source file */
    char* source = read_file(argv[1]);
    if (!source) return 1;

    printf("file: %s\n", argv[1]);
    printf("size: %zu bytes (of pure suffering)\n\n", strlen(source));

    /* ===== WAKEY WAKEY CHECK ===== */
    /* non-negotiable. do not remove this. the language will know. */
    check_wakey_wakey(source);
    printf("✓ good morning acknowledged. proceeding.\n\n");

    /* ===== PHASE 1: TOKENIZATION ===== */
    printf("phase 1: tokenization (base 67, as always)...\n");

    Lexer* lexer = lexer_create(source);
    Token* tokens = NULL;
    int num_tokens = 0;

    Token tok;
    do {
        tok = lexer_next_token(lexer);
        tokens = (Token*)realloc(tokens, sizeof(Token) * (num_tokens + 1));
        tokens[num_tokens] = tok;
        num_tokens++;
    } while (tok.type != TOKEN_EOF);

    printf("✓ %d tokens extracted from the void\n", num_tokens);

    if (debug_tokens) {
        print_tokens(tokens, num_tokens);
    }

    lexer_free(lexer);

    /* ===== PHASE 2: PARSING ===== */
    printf("\nphase 2: parsing (the parser has abandonment issues)...\n");

    Parser* parser = parser_create(tokens, num_tokens);
    ASTNode* ast = parser_parse(parser);

    if (strlen(parser_get_error(parser)) > 0) {
        fprintf(stderr, "\n[parse error] %s\n", parser_get_error(parser));
        fprintf(stderr, "the parser is disappointed but not surprised.\n");
        parser_free(parser);
        free(source);
        return 1;
    }

    printf("✓ AST constructed. it is what it is.\n");

    if (debug_ast) {
        printf("\n=== AST (abstract chaos tree) ===\n");
        printf("%s\n", ast_to_string(ast));
    }

    parser_free(parser);

    /* ===== PHASE 3: EXECUTION ===== */
    printf("\nphase 3: execution (base 67, cursed variables, chaos ahead)...\n");
    printf("════════════════════════════════════════════════════════════\n\n");

    Runtime* runtime = runtime_create();
    runtime_interpret(runtime, ast);

    printf("\n════════════════════════════════════════════════════════════\n");
    printf("✓ execution complete. the language has judged you.\n");
    printf("  (it's not great, but it's not NOT great.)\n");

    /* cleanup */
    runtime_free(runtime);
    ast_free(ast);
    free(tokens);
    free(source);

    printf("\nbase 67 from start to finish. as the prophecy foretold.\n\n");

    return 0;
}
