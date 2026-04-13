/*
 * parser.c — Recursive Descent Parser
 *
 * btw, this parser has abandonment issues.
 * btw, every error message here was written by someone who cared too much.
 * btw, "Esperado" means "expected" in portuguese. we're multilingual and exhausted.
 */

#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char parse_error[512] = {0};

static Token current_token(Parser* p) {
    if (p->current < p->num_tokens) {
        return p->tokens[p->current];
    }
    return (Token){.type = TOKEN_EOF, .lexeme = "", .linha = 0, .coluna = 0};
}

static void advance(Parser* p) {
    if (p->current < p->num_tokens) {
        p->current++;
    }
}

static int match(Parser* p, TokenType type) {
    if (current_token(p).type == type) {
        advance(p);
        return 1;
    }
    return 0;
}

static int check(Parser* p, TokenType type) {
    return current_token(p).type == type;
}

static void error(const char* msg) {
    strncpy(parse_error, msg, 511);
}

/* Forward declarations */
static ASTNode* parse_expr(Parser* p);
static ASTNode* parse_stmt(Parser* p);
static ASTNode* parse_block(Parser* p);

static ASTNode* parse_primary(Parser* p) {
    Token tok = current_token(p);

    if (tok.type == TOKEN_NUMERO) {
        advance(p);
        Literal* lit = (Literal*)malloc(sizeof(Literal));
        lit->value = value_numero(tok.valor_decimal);
        ASTNode* node = ast_create(AST_LITERAL);
        node->dados = lit;
        return node;
    }

    if (tok.type == TOKEN_STRING) {
        advance(p);
        Literal* lit = (Literal*)malloc(sizeof(Literal));
        lit->value = value_texto(tok.lexeme);
        ASTNode* node = ast_create(AST_LITERAL);
        node->dados = lit;
        return node;
    }

    if (tok.type == TOKEN_BESTIE) {
        advance(p);
        Literal* lit = (Literal*)malloc(sizeof(Literal));
        lit->value = value_bool(1);
        ASTNode* node = ast_create(AST_LITERAL);
        node->dados = lit;
        return node;
    }

    if (tok.type == TOKEN_BETRAYAL) {
        advance(p);
        Literal* lit = (Literal*)malloc(sizeof(Literal));
        lit->value = value_bool(0);
        ASTNode* node = ast_create(AST_LITERAL);
        node->dados = lit;
        return node;
    }

    if (tok.type == TOKEN_THEVOID) {
        advance(p);
        Literal* lit = (Literal*)malloc(sizeof(Literal));
        lit->value = value_nulo();
        ASTNode* node = ast_create(AST_LITERAL);
        node->dados = lit;
        return node;
    }

    if (tok.type == TOKEN_IDENT) {
        advance(p);
        Ident* id = (Ident*)malloc(sizeof(Ident));
        id->nome = (char*)malloc(strlen(tok.lexeme) + 1);
        strcpy(id->nome, tok.lexeme);
        ASTNode* node = ast_create(AST_IDENT);
        node->dados = id;
        return node;
    }

    if (match(p, TOKEN_LPAREN)) {
        ASTNode* expr = parse_expr(p);
        if (!match(p, TOKEN_RPAREN)) {
            error("oh honey, no. we needed a ')' here and you just... didn't.");
        }
        return expr;
    }

    error("oh honey, no. that's not an expression. that's a cry for help.");
    return ast_create(AST_LITERAL);
}

static ASTNode* parse_postfix(Parser* p) {
    ASTNode* expr = parse_primary(p);

    while (check(p, TOKEN_LPAREN)) {
        advance(p);

        CallExpr* ce = (CallExpr*)malloc(sizeof(CallExpr));

        if (expr->type == AST_IDENT) {
            Ident* id = (Ident*)expr->dados;
            ce->nome = (char*)malloc(strlen(id->nome) + 1);
            strcpy(ce->nome, id->nome);
        } else {
            ce->nome = (char*)malloc(16);
            strcpy(ce->nome, "<unknown>");
        }

        ce->args = NULL;
        ce->num_args = 0;

        if (!check(p, TOKEN_RPAREN)) {
            do {
                ASTNode* arg = parse_expr(p);
                ce->args = (ASTNode**)realloc(ce->args, sizeof(ASTNode*) * (ce->num_args + 1));
                ce->args[ce->num_args++] = arg;
            } while (match(p, TOKEN_COMMA));
        }

        if (!match(p, TOKEN_RPAREN)) {
            error("oh honey, no. the ')' was RIGHT THERE and you missed it.");
        }

        ast_free(expr);
        expr = ast_create(AST_CALL_EXPR);
        expr->dados = ce;
    }

    return expr;
}

static ASTNode* parse_unary(Parser* p) {
    if (match(p, TOKEN_NOT)) {
        UnaryOp* uo = (UnaryOp*)malloc(sizeof(UnaryOp));
        uo->op = (char*)malloc(2);
        strcpy(uo->op, "!");
        uo->operand = parse_unary(p);
        ASTNode* node = ast_create(AST_UNARY_OP);
        node->dados = uo;
        return node;
    }

    if (match(p, TOKEN_MINUS)) {
        UnaryOp* uo = (UnaryOp*)malloc(sizeof(UnaryOp));
        uo->op = (char*)malloc(2);
        strcpy(uo->op, "-");
        uo->operand = parse_unary(p);
        ASTNode* node = ast_create(AST_UNARY_OP);
        node->dados = uo;
        return node;
    }

    return parse_postfix(p);
}

static ASTNode* parse_multiplicative(Parser* p) {
    ASTNode* left = parse_unary(p);

    while (check(p, TOKEN_STAR) || check(p, TOKEN_SLASH) || check(p, TOKEN_PERCENT)) {
        Token op_tok = current_token(p);
        advance(p);
        ASTNode* right = parse_unary(p);

        BinaryOp* bo = (BinaryOp*)malloc(sizeof(BinaryOp));
        bo->left = left;
        bo->right = right;
        bo->op = (char*)malloc(strlen(op_tok.lexeme) + 1);
        strcpy(bo->op, op_tok.lexeme);

        left = ast_create(AST_BINARY_OP);
        left->dados = bo;
    }

    return left;
}

static ASTNode* parse_additive(Parser* p) {
    ASTNode* left = parse_multiplicative(p);

    while (check(p, TOKEN_PLUS) || check(p, TOKEN_MINUS)) {
        Token op_tok = current_token(p);
        advance(p);
        ASTNode* right = parse_multiplicative(p);

        BinaryOp* bo = (BinaryOp*)malloc(sizeof(BinaryOp));
        bo->left = left;
        bo->right = right;
        bo->op = (char*)malloc(strlen(op_tok.lexeme) + 1);
        strcpy(bo->op, op_tok.lexeme);

        left = ast_create(AST_BINARY_OP);
        left->dados = bo;
    }

    return left;
}

static ASTNode* parse_relational(Parser* p) {
    ASTNode* left = parse_additive(p);

    while (check(p, TOKEN_LT) || check(p, TOKEN_GT) ||
           check(p, TOKEN_LE) || check(p, TOKEN_GE)) {
        Token op_tok = current_token(p);
        advance(p);
        ASTNode* right = parse_additive(p);

        BinaryOp* bo = (BinaryOp*)malloc(sizeof(BinaryOp));
        bo->left = left;
        bo->right = right;
        bo->op = (char*)malloc(strlen(op_tok.lexeme) + 1);
        strcpy(bo->op, op_tok.lexeme);

        left = ast_create(AST_BINARY_OP);
        left->dados = bo;
    }

    return left;
}

static ASTNode* parse_equality(Parser* p) {
    ASTNode* left = parse_relational(p);

    while (check(p, TOKEN_EQ) || check(p, TOKEN_NE)) {
        Token op_tok = current_token(p);
        advance(p);
        ASTNode* right = parse_relational(p);

        BinaryOp* bo = (BinaryOp*)malloc(sizeof(BinaryOp));
        bo->left = left;
        bo->right = right;
        bo->op = (char*)malloc(strlen(op_tok.lexeme) + 1);
        strcpy(bo->op, op_tok.lexeme);

        left = ast_create(AST_BINARY_OP);
        left->dados = bo;
    }

    return left;
}

static ASTNode* parse_logical_and(Parser* p) {
    ASTNode* left = parse_equality(p);

    while (match(p, TOKEN_AND)) {
        ASTNode* right = parse_equality(p);

        BinaryOp* bo = (BinaryOp*)malloc(sizeof(BinaryOp));
        bo->left = left;
        bo->right = right;
        bo->op = (char*)malloc(3);
        strcpy(bo->op, "&&");

        left = ast_create(AST_BINARY_OP);
        left->dados = bo;
    }

    return left;
}

static ASTNode* parse_logical_or(Parser* p) {
    ASTNode* left = parse_logical_and(p);

    while (match(p, TOKEN_OR)) {
        ASTNode* right = parse_logical_and(p);

        BinaryOp* bo = (BinaryOp*)malloc(sizeof(BinaryOp));
        bo->left = left;
        bo->right = right;
        bo->op = (char*)malloc(3);
        strcpy(bo->op, "||");

        left = ast_create(AST_BINARY_OP);
        left->dados = bo;
    }

    return left;
}

static ASTNode* parse_assignment(Parser* p) {
    ASTNode* expr = parse_logical_or(p);

    if (match(p, TOKEN_ASSIGN)) {
        if (expr->type != AST_IDENT) {
            error("this ain't it chief. assignment target must be a variable, not... whatever that was.");
            return expr;
        }

        Ident* id = (Ident*)expr->dados;
        ASTNode* value = parse_assignment(p);

        Assign* as = (Assign*)malloc(sizeof(Assign));
        as->target = (char*)malloc(strlen(id->nome) + 1);
        strcpy(as->target, id->nome);
        as->value = value;

        ast_free(expr);

        expr = ast_create(AST_ASSIGN);
        expr->dados = as;
    }

    return expr;
}

static ASTNode* parse_expr(Parser* p) {
    return parse_assignment(p);
}

/*
 * parse_var_decl — handles:
 *   idk x = expr ok?
 *   cursed idk x = expr ok?   (cursed = variable may lie 10% of the time)
 */
static ASTNode* parse_var_decl(Parser* p) {
    int is_cursed = 0;

    /* optional "cursed" modifier — for variables with trust issues */
    if (match(p, TOKEN_CURSED)) {
        is_cursed = 1;
    }

    if (!match(p, TOKEN_IDK)) {
        error("oh honey, no. we need 'idk' for variable declarations. this is not negotiable.");
        return NULL;
    }

    Token name_tok = current_token(p);
    if (name_tok.type != TOKEN_IDENT) {
        error("never heard of her. (expected a variable name, got... something else entirely.)");
        return NULL;
    }
    advance(p);

    if (!match(p, TOKEN_ASSIGN)) {
        error("oh honey, no. expected '=' in variable declaration. we don't do 'declare and pray' here.");
        return NULL;
    }

    ASTNode* expr = parse_expr(p);

    if (!match(p, TOKEN_SEMICOLON)) {
        error("oh honey, no. where is your 'ok?' at the end of the line. WHERE IS IT.");
        return NULL;
    }

    VarDecl* vd = (VarDecl*)malloc(sizeof(VarDecl));
    vd->nome = (char*)malloc(strlen(name_tok.lexeme) + 1);
    strcpy(vd->nome, name_tok.lexeme);
    vd->expr_init = expr;
    vd->is_cursed = is_cursed;

    ASTNode* node = ast_create(AST_VAR_DECL);
    node->dados = vd;
    return node;
}

static ASTNode* parse_func_decl(Parser* p) {
    if (!match(p, TOKEN_RITUAL)) {
        error("oh honey, no. expected 'ritual' for function declaration. we call them rituals now.");
        return NULL;
    }

    Token name_tok = current_token(p);
    if (name_tok.type != TOKEN_IDENT) {
        error("never heard of her. (expected a ritual name, got silence.)");
        return NULL;
    }
    advance(p);

    if (!match(p, TOKEN_LPAREN)) {
        error("oh honey, no. expected '(' after ritual name. did you skip the parentheses?");
        return NULL;
    }

    FuncDecl* fd = (FuncDecl*)malloc(sizeof(FuncDecl));
    fd->nome = (char*)malloc(strlen(name_tok.lexeme) + 1);
    strcpy(fd->nome, name_tok.lexeme);
    fd->params = NULL;
    fd->num_params = 0;

    if (!check(p, TOKEN_RPAREN)) {
        do {
            Token param_tok = current_token(p);
            if (param_tok.type != TOKEN_IDENT) {
                error("never heard of her. (expected a parameter name.)");
                return NULL;
            }
            advance(p);

            fd->params = (char**)realloc(fd->params, sizeof(char*) * (fd->num_params + 1));
            fd->params[fd->num_params] = (char*)malloc(strlen(param_tok.lexeme) + 1);
            strcpy(fd->params[fd->num_params], param_tok.lexeme);
            fd->num_params++;
        } while (match(p, TOKEN_COMMA));
    }

    if (!match(p, TOKEN_RPAREN)) {
        error("oh honey, no. expected ')' to close the ritual parameters.");
        return NULL;
    }

    fd->body = parse_block(p);

    ASTNode* node = ast_create(AST_FUNC_DECL);
    node->dados = fd;
    return node;
}

static ASTNode* parse_if_stmt(Parser* p) {
    if (!match(p, TOKEN_NGL)) {
        error("oh honey, no. expected 'ngl' here.");
        return NULL;
    }

    if (!match(p, TOKEN_LPAREN)) {
        error("oh honey, no. expected '(' after 'ngl'. punctuation exists for a reason.");
        return NULL;
    }

    ASTNode* condicao = parse_expr(p);

    if (!match(p, TOKEN_RPAREN)) {
        error("oh honey, no. expected ')' to close the 'ngl' condition. it's a matched pair. like socks.");
        return NULL;
    }

    ASTNode* then_block = parse_block(p);
    ASTNode* else_block = NULL;

    if (match(p, TOKEN_ORNOT)) {
        else_block = parse_block(p);
    }

    IfStmt* is = (IfStmt*)malloc(sizeof(IfStmt));
    is->condicao = condicao;
    is->then_block = then_block;
    is->else_block = else_block;

    ASTNode* node = ast_create(AST_IF_STMT);
    node->dados = is;
    return node;
}

static ASTNode* parse_while_stmt(Parser* p) {
    if (!match(p, TOKEN_UNTILGETIIRED)) {
        error("oh honey, no. expected 'untilIGetTired' here.");
        return NULL;
    }

    if (!match(p, TOKEN_LPAREN)) {
        error("oh honey, no. expected '(' after 'untilIGetTired'.");
        return NULL;
    }

    ASTNode* condicao = parse_expr(p);

    if (!match(p, TOKEN_RPAREN)) {
        error("oh honey, no. expected ')'. you started something and didn't finish it.");
        return NULL;
    }

    ASTNode* body = parse_block(p);

    WhileStmt* ws = (WhileStmt*)malloc(sizeof(WhileStmt));
    ws->condicao = condicao;
    ws->body = body;

    ASTNode* node = ast_create(AST_WHILE_STMT);
    node->dados = ws;
    return node;
}

static ASTNode* parse_for_stmt(Parser* p) {
    if (!match(p, TOKEN_DOTHING)) {
        error("oh honey, no. expected 'doTheThing' here.");
        return NULL;
    }

    if (!match(p, TOKEN_LPAREN)) {
        error("oh honey, no. expected '(' after 'doTheThing'.");
        return NULL;
    }

    ASTNode* init = NULL;
    if (!check(p, TOKEN_SEMICOLON)) {
        init = parse_expr(p);
    }
    if (!match(p, TOKEN_SEMICOLON)) {
        error("oh honey, no. expected 'ok?' (semicolon) in the 'doTheThing' loop header.");
    }

    ASTNode* condicao = NULL;
    if (!check(p, TOKEN_SEMICOLON)) {
        condicao = parse_expr(p);
    }
    if (!match(p, TOKEN_SEMICOLON)) {
        error("oh honey, no. expected a second 'ok?' in the 'doTheThing' loop header.");
    }

    ASTNode* update = NULL;
    if (!check(p, TOKEN_RPAREN)) {
        update = parse_expr(p);
    }
    if (!match(p, TOKEN_RPAREN)) {
        error("oh honey, no. expected ')' to close 'doTheThing'.");
    }

    ASTNode* body = parse_block(p);

    ForStmt* fs = (ForStmt*)malloc(sizeof(ForStmt));
    fs->init = init;
    fs->condicao = condicao;
    fs->update = update;
    fs->body = body;

    ASTNode* node = ast_create(AST_FOR_STMT);
    node->dados = fs;
    return node;
}

static ASTNode* parse_return_stmt(Parser* p) {
    if (!match(p, TOKEN_YEET)) {
        error("oh honey, no. expected 'YEET' for return statement.");
        return NULL;
    }

    ASTNode* expr = NULL;
    if (!check(p, TOKEN_SEMICOLON)) {
        expr = parse_expr(p);
    }

    if (!match(p, TOKEN_SEMICOLON)) {
        error("oh honey, no. expected 'ok?' after YEET. you YEET and you COMMIT.");
    }

    ReturnStmt* rs = (ReturnStmt*)malloc(sizeof(ReturnStmt));
    rs->expr = expr;

    ASTNode* node = ast_create(AST_RETURN_STMT);
    node->dados = rs;
    return node;
}

static ASTNode* parse_stmt(Parser* p) {
    /* cursed can prefix idk */
    if (check(p, TOKEN_IDK) || check(p, TOKEN_CURSED)) {
        return parse_var_decl(p);
    }
    if (check(p, TOKEN_RITUAL)) {
        return parse_func_decl(p);
    }
    if (check(p, TOKEN_NGL)) {
        return parse_if_stmt(p);
    }
    if (check(p, TOKEN_UNTILGETIIRED)) {
        return parse_while_stmt(p);
    }
    if (check(p, TOKEN_DOTHING)) {
        return parse_for_stmt(p);
    }
    if (check(p, TOKEN_YEET)) {
        return parse_return_stmt(p);
    }
    if (match(p, TOKEN_IQUIT)) {
        if (!match(p, TOKEN_SEMICOLON)) {
            error("oh honey, no. iQuit needs an 'ok?' at the end. even quitting has rules.");
        }
        return ast_create(AST_BREAK_STMT);
    }
    if (match(p, TOKEN_UGH)) {
        if (!match(p, TOKEN_SEMICOLON)) {
            error("oh honey, no. 'ugh' needs an 'ok?' at the end. yes. fine. ok?");
        }
        return ast_create(AST_CONTINUE_STMT);
    }
    if (check(p, TOKEN_LBRACE)) {
        return parse_block(p);
    }

    /* expression statement */
    ASTNode* expr = parse_expr(p);
    if (!match(p, TOKEN_SEMICOLON)) {
        error("oh honey, no. expected 'ok?' at end of statement. it's literally two characters.");
    }
    return expr;
}

static ASTNode* parse_block(Parser* p) {
    if (!match(p, TOKEN_LBRACE)) {
        error("oh honey, no. expected '{' to open a block. the curly brace. you know the one.");
        return NULL;
    }

    Block* bl = (Block*)malloc(sizeof(Block));
    bl->statements = NULL;
    bl->num_statements = 0;

    while (!check(p, TOKEN_RBRACE) && !check(p, TOKEN_EOF)) {
        ASTNode* stmt = parse_stmt(p);
        if (stmt) {
            bl->statements = (ASTNode**)realloc(bl->statements,
                sizeof(ASTNode*) * (bl->num_statements + 1));
            bl->statements[bl->num_statements++] = stmt;
        }
    }

    if (!match(p, TOKEN_RBRACE)) {
        error("oh honey, no. where is the closing '}'? you opened it and just left.");
    }

    ASTNode* node = ast_create(AST_BLOCK);
    node->dados = bl;
    return node;
}

Parser* parser_create(Token* tokens, int num_tokens) {
    Parser* parser = (Parser*)malloc(sizeof(Parser));
    parser->tokens = tokens;
    parser->num_tokens = num_tokens;
    parser->current = 0;
    return parser;
}

ASTNode* parser_parse(Parser* p) {
    Program* prog = (Program*)malloc(sizeof(Program));
    prog->statements = NULL;
    prog->num_statements = 0;

    while (!check(p, TOKEN_EOF)) {
        ASTNode* stmt = parse_stmt(p);
        if (stmt) {
            prog->statements = (ASTNode**)realloc(prog->statements,
                sizeof(ASTNode*) * (prog->num_statements + 1));
            prog->statements[prog->num_statements++] = stmt;
        }
    }

    ASTNode* root = ast_create(AST_PROGRAMA);
    root->dados = prog;
    return root;
}

void parser_free(Parser* p) {
    if (p) free(p);
}

const char* parser_get_error(Parser* p) {
    return parse_error;
}
