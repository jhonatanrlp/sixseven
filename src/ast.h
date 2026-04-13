/*
 * ast.h — Abstract Syntax Tree for SixSeven
 *
 * btw, "abstract" is doing a lot of heavy lifting here.
 * btw, this tree has trust issues.
 */

#ifndef AST_H
#define AST_H

#include "value.h"

typedef enum {
    AST_PROGRAMA,
    AST_VAR_DECL,
    AST_FUNC_DECL,
    AST_CALL_EXPR,
    AST_BINARY_OP,
    AST_UNARY_OP,
    AST_IF_STMT,
    AST_WHILE_STMT,
    AST_FOR_STMT,
    AST_RETURN_STMT,
    AST_BREAK_STMT,
    AST_CONTINUE_STMT,
    AST_BLOCK,
    AST_LITERAL,
    AST_IDENT,
    AST_ASSIGN,
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    void* dados;
    struct ASTNode** children;
    int num_children;
} ASTNode;

typedef struct {
    ASTNode** statements;
    int num_statements;
} Program;

typedef struct {
    char* nome;
    ASTNode* expr_init;
    int is_cursed;   /* if 1, this variable lies to you 10% of the time. no warranty. */
} VarDecl;

typedef struct {
    char* nome;
    char** params;
    int num_params;
    ASTNode* body;
} FuncDecl;

typedef struct {
    char* nome;
    ASTNode** args;
    int num_args;
} CallExpr;

typedef struct {
    ASTNode* left;
    ASTNode* right;
    char* op;
} BinaryOp;

typedef struct {
    ASTNode* operand;
    char* op;
} UnaryOp;

typedef struct {
    ASTNode* condicao;
    ASTNode* then_block;
    ASTNode* else_block;
} IfStmt;

typedef struct {
    ASTNode* condicao;
    ASTNode* body;
} WhileStmt;

typedef struct {
    ASTNode* init;
    ASTNode* condicao;
    ASTNode* update;
    ASTNode* body;
} ForStmt;

typedef struct {
    ASTNode* expr;
} ReturnStmt;

typedef struct {
    ASTNode** statements;
    int num_statements;
} Block;

typedef struct {
    Value value;
} Literal;

typedef struct {
    char* nome;
} Ident;

typedef struct {
    char* target;
    ASTNode* value;
} Assign;

ASTNode* ast_create(ASTNodeType type);
void ast_add_child(ASTNode* parent, ASTNode* child);
void ast_free(ASTNode* node);
char* ast_to_string(ASTNode* node);

#endif
