/*
 * ast.c - Implementação de AST
 */

#include "ast.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

ASTNode* ast_create(ASTNodeType type) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->dados = NULL;
    node->children = NULL;
    node->num_children = 0;
    return node;
}

void ast_add_child(ASTNode* parent, ASTNode* child) {
    if (!parent || !child) return;
    parent->children = (ASTNode**)realloc(parent->children, 
                                          sizeof(ASTNode*) * (parent->num_children + 1));
    parent->children[parent->num_children] = child;
    parent->num_children++;
}

void ast_free(ASTNode* node) {
    if (!node) return;
    
    /* Liberar dados específicos */
    switch (node->type) {
        case AST_VAR_DECL: {
            VarDecl* vd = (VarDecl*)node->dados;
            if (vd) {
                free(vd->nome);
                free(vd);
            }
            break;
        }
        case AST_FUNC_DECL: {
            FuncDecl* fd = (FuncDecl*)node->dados;
            if (fd) {
                free(fd->nome);
                for (int i = 0; i < fd->num_params; i++) {
                    free(fd->params[i]);
                }
                free(fd->params);
                ast_free(fd->body);
                free(fd);
            }
            break;
        }
        case AST_CALL_EXPR: {
            CallExpr* ce = (CallExpr*)node->dados;
            if (ce) {
                free(ce->nome);
                for (int i = 0; i < ce->num_args; i++) {
                    ast_free(ce->args[i]);
                }
                free(ce->args);
                free(ce);
            }
            break;
        }
        case AST_BINARY_OP: {
            BinaryOp* bo = (BinaryOp*)node->dados;
            if (bo) {
                ast_free(bo->left);
                ast_free(bo->right);
                free(bo->op);
                free(bo);
            }
            break;
        }
        case AST_UNARY_OP: {
            UnaryOp* uo = (UnaryOp*)node->dados;
            if (uo) {
                ast_free(uo->operand);
                free(uo->op);
                free(uo);
            }
            break;
        }
        case AST_IF_STMT: {
            IfStmt* is = (IfStmt*)node->dados;
            if (is) {
                ast_free(is->condicao);
                ast_free(is->then_block);
                ast_free(is->else_block);
                free(is);
            }
            break;
        }
        case AST_WHILE_STMT: {
            WhileStmt* ws = (WhileStmt*)node->dados;
            if (ws) {
                ast_free(ws->condicao);
                ast_free(ws->body);
                free(ws);
            }
            break;
        }
        case AST_FOR_STMT: {
            ForStmt* fs = (ForStmt*)node->dados;
            if (fs) {
                ast_free(fs->init);
                ast_free(fs->condicao);
                ast_free(fs->update);
                ast_free(fs->body);
                free(fs);
            }
            break;
        }
        case AST_RETURN_STMT: {
            ReturnStmt* rs = (ReturnStmt*)node->dados;
            if (rs) {
                ast_free(rs->expr);
                free(rs);
            }
            break;
        }
        case AST_BLOCK: {
            Block* bl = (Block*)node->dados;
            if (bl) {
                for (int i = 0; i < bl->num_statements; i++) {
                    ast_free(bl->statements[i]);
                }
                free(bl->statements);
                free(bl);
            }
            break;
        }
        case AST_LITERAL: {
            Literal* lit = (Literal*)node->dados;
            if (lit) {
                value_free(lit->value);
                free(lit);
            }
            break;
        }
        case AST_IDENT: {
            Ident* id = (Ident*)node->dados;
            if (id) {
                free(id->nome);
                free(id);
            }
            break;
        }
        case AST_ASSIGN: {
            Assign* as = (Assign*)node->dados;
            if (as) {
                free(as->target);
                ast_free(as->value);
                free(as);
            }
            break;
        }
        default:
            break;
    }
    
    if (node->children) {
        free(node->children);
    }
    free(node);
}

const char* ast_type_to_string(ASTNodeType type) {
    switch (type) {
        case AST_PROGRAMA: return "PROGRAMA";
        case AST_VAR_DECL: return "VAR_DECL";
        case AST_FUNC_DECL: return "FUNC_DECL";
        case AST_CALL_EXPR: return "CALL_EXPR";
        case AST_BINARY_OP: return "BINARY_OP";
        case AST_UNARY_OP: return "UNARY_OP";
        case AST_IF_STMT: return "IF_STMT";
        case AST_WHILE_STMT: return "WHILE_STMT";
        case AST_FOR_STMT: return "FOR_STMT";
        case AST_RETURN_STMT: return "RETURN_STMT";
        case AST_BREAK_STMT: return "BREAK_STMT";
        case AST_CONTINUE_STMT: return "CONTINUE_STMT";
        case AST_BLOCK: return "BLOCK";
        case AST_LITERAL: return "LITERAL";
        case AST_IDENT: return "IDENT";
        case AST_ASSIGN: return "ASSIGN";
        default: return "?";
    }
}

char* ast_to_string(ASTNode* node) {
    char* result = (char*)malloc(1024);
    if (!node) {
        strcpy(result, "NULL");
        return result;
    }
    
    snprintf(result, 1024, "<%s>", ast_type_to_string(node->type));
    return result;
}
