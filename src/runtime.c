/*
 * runtime.c — The Interpreter (where AST nodes go to be judged)
 *
 * btw, all numbers are in base 67. this is still happening.
 * btw, cursed variables lie 10% of the time. you agreed to this by running the program.
 * btw, "stack overflow" means you really said 'go deeper' huh.
 */

#include "runtime.h"
#include "base67.h"
#include "builtins.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

/* ============================================================
 * Environment (scope management, trust issues included)
 * ============================================================ */

static Environment* env_create(Environment* parent) {
    Environment* env = (Environment*)malloc(sizeof(Environment));
    env->var_names  = NULL;
    env->var_values = NULL;
    env->num_vars   = 0;
    env->parent     = parent;
    env->cursed_vars = NULL;
    env->num_cursed  = 0;
    return env;
}

static void env_free(Environment* env) {
    if (!env) return;
    for (int i = 0; i < env->num_vars; i++) {
        free(env->var_names[i]);
        value_free(env->var_values[i]);
    }
    free(env->var_names);
    free(env->var_values);
    for (int i = 0; i < env->num_cursed; i++) {
        free(env->cursed_vars[i]);
    }
    free(env->cursed_vars);
    free(env);
}

static void env_define(Environment* env, const char* name, Value val) {
    for (int i = 0; i < env->num_vars; i++) {
        if (strcmp(env->var_names[i], name) == 0) {
            value_free(env->var_values[i]);
            env->var_values[i] = val;
            return;
        }
    }

    env->var_names  = (char**)realloc(env->var_names,  sizeof(char*)  * (env->num_vars + 1));
    env->var_values = (Value*) realloc(env->var_values, sizeof(Value)  * (env->num_vars + 1));

    env->var_names[env->num_vars]  = (char*)malloc(strlen(name) + 1);
    strcpy(env->var_names[env->num_vars], name);
    env->var_values[env->num_vars] = val;
    env->num_vars++;
}

static void env_mark_cursed(Environment* env, const char* name) {
    env->cursed_vars = (char**)realloc(env->cursed_vars, sizeof(char*) * (env->num_cursed + 1));
    env->cursed_vars[env->num_cursed] = (char*)malloc(strlen(name) + 1);
    strcpy(env->cursed_vars[env->num_cursed], name);
    env->num_cursed++;
}

static int env_is_cursed(Environment* env, const char* name) {
    Environment* e = env;
    while (e) {
        for (int i = 0; i < e->num_cursed; i++) {
            if (strcmp(e->cursed_vars[i], name) == 0) return 1;
        }
        e = e->parent;
    }
    return 0;
}

static Value env_get(Environment* env, const char* name) {
    Environment* e = env;
    while (e) {
        for (int i = 0; i < e->num_vars; i++) {
            if (strcmp(e->var_names[i], name) == 0) {
                Value v = e->var_values[i];

                /* cursed variables: 10% chance of returning absolute garbage.
                 * this is a feature. do not file a bug report. */
                if (env_is_cursed(env, name) && (rand() % 10) == 0) {
                    fprintf(stderr,
                        "[cursed] '%s' looked you right in the eyes and lied.\n", name);
                    return value_numero(rand() % 9999);
                }

                return v;
            }
        }
        e = e->parent;
    }
    /* never heard of her. */
    return value_nulo();
}

/* ============================================================
 * Arithmetic and comparison operations
 * ============================================================ */

static Value arithmetic_op(const char* op, Value left, Value right) {
    if (left.type != VALUE_NUMERO || right.type != VALUE_NUMERO) {
        fprintf(stderr, "this ain't it chief. arithmetic '%s' requires two numbers in base 67.\n", op);
        return value_numero(0);
    }

    long long l = left.dados.numero;
    long long r = right.dados.numero;
    long long result = 0;

    if (strcmp(op, "+") == 0) {
        result = l + r;
    } else if (strcmp(op, "-") == 0) {
        result = l - r;
    } else if (strcmp(op, "*") == 0) {
        result = l * r;
    } else if (strcmp(op, "/") == 0) {
        if (r == 0) {
            fprintf(stderr, "bold of you to assume math works here. (division by zero)\n");
            return value_numero(0);
        }
        result = l / r;
    } else if (strcmp(op, "%") == 0) {
        if (r == 0) {
            fprintf(stderr, "bold of you to assume math works here. (modulo by zero)\n");
            return value_numero(0);
        }
        result = l % r;
    }

    return value_numero(result);
}

static int is_truthy(Value val) {
    switch (val.type) {
        case VALUE_NUMERO: return val.dados.numero != 0;
        case VALUE_BOOL:   return val.dados.boolean;
        case VALUE_TEXTO:  return val.dados.texto && strlen(val.dados.texto) > 0;
        default:           return 0;
    }
}

static Value comparison_op(const char* op, Value left, Value right) {
    int result = 0;

    if (strcmp(op, "==") == 0) {
        result = value_equal(left, right);
    } else if (strcmp(op, "!=") == 0) {
        result = !value_equal(left, right);
    } else if (strcmp(op, "<") == 0) {
        if (left.type == VALUE_NUMERO && right.type == VALUE_NUMERO)
            result = left.dados.numero < right.dados.numero;
    } else if (strcmp(op, ">") == 0) {
        if (left.type == VALUE_NUMERO && right.type == VALUE_NUMERO)
            result = left.dados.numero > right.dados.numero;
    } else if (strcmp(op, "<=") == 0) {
        if (left.type == VALUE_NUMERO && right.type == VALUE_NUMERO)
            result = left.dados.numero <= right.dados.numero;
    } else if (strcmp(op, ">=") == 0) {
        if (left.type == VALUE_NUMERO && right.type == VALUE_NUMERO)
            result = left.dados.numero >= right.dados.numero;
    }

    return value_bool(result);
}

/* ============================================================
 * Evaluation (where things happen, sometimes correctly)
 * ============================================================ */

static Value runtime_eval(Runtime* rt, ASTNode* node);

static Value runtime_eval_expr(Runtime* rt, ASTNode* expr) {
    if (!expr) return value_nulo();

    switch (expr->type) {
        case AST_LITERAL: {
            Literal* lit = (Literal*)expr->dados;
            return lit->value;
        }

        case AST_IDENT: {
            Ident* id = (Ident*)expr->dados;
            Value v = env_get(rt->current_env, id->nome);
            if (v.type == VALUE_NULO) {
                /* could be actually null, or could be: never heard of her. */
            }
            return v;
        }

        case AST_BINARY_OP: {
            BinaryOp* bo = (BinaryOp*)expr->dados;
            Value left  = runtime_eval_expr(rt, bo->left);
            Value right = runtime_eval_expr(rt, bo->right);

            if (strcmp(bo->op, "&&") == 0) {
                return value_bool(is_truthy(left) && is_truthy(right));
            } else if (strcmp(bo->op, "||") == 0) {
                return value_bool(is_truthy(left) || is_truthy(right));
            } else if (strchr("<>=!", bo->op[0])) {
                return comparison_op(bo->op, left, right);
            } else {
                return arithmetic_op(bo->op, left, right);
            }
        }

        case AST_UNARY_OP: {
            UnaryOp* uo = (UnaryOp*)expr->dados;
            Value operand = runtime_eval_expr(rt, uo->operand);

            if (strcmp(uo->op, "!") == 0) {
                return value_bool(!is_truthy(operand));
            } else if (strcmp(uo->op, "-") == 0) {
                if (operand.type == VALUE_NUMERO) {
                    return value_numero(-operand.dados.numero);
                }
            }
            return operand;
        }

        case AST_ASSIGN: {
            Assign* as = (Assign*)expr->dados;
            Value val = runtime_eval_expr(rt, as->value);
            env_define(rt->current_env, as->target, val);
            return val;
        }

        case AST_CALL_EXPR: {
            CallExpr* ce = (CallExpr*)expr->dados;

            Value* args = (Value*)malloc(sizeof(Value) * (ce->num_args + 1));
            for (int i = 0; i < ce->num_args; i++) {
                args[i] = runtime_eval_expr(rt, ce->args[i]);
            }

            if (is_builtin(ce->nome)) {
                NativeFn fn = builtin_get_function(ce->nome);
                Value result = fn(args, ce->num_args);
                free(args);
                return result;
            }

            fprintf(stderr, "never heard of her. (function '%s' is not defined)\n", ce->nome);
            free(args);
            return value_nulo();
        }

        default:
            return runtime_eval(rt, expr);
    }
}

static Value runtime_eval(Runtime* rt, ASTNode* node) {
    if (!node) return value_nulo();

    switch (node->type) {
        case AST_PROGRAMA: {
            Program* prog = (Program*)node->dados;
            Value result = value_nulo();
            for (int i = 0; i < prog->num_statements; i++) {
                result = runtime_eval(rt, prog->statements[i]);
                if (rt->return_flag) break;
            }
            return result;
        }

        case AST_VAR_DECL: {
            VarDecl* vd = (VarDecl*)node->dados;
            Value val = runtime_eval_expr(rt, vd->expr_init);
            env_define(rt->current_env, vd->nome, val);
            if (vd->is_cursed) {
                env_mark_cursed(rt->current_env, vd->nome);
                fprintf(stderr,
                    "[cursed] '%s' has been marked cursed. it may or may not tell the truth. godspeed.\n",
                    vd->nome);
            }
            return value_nulo();
        }

        case AST_FUNC_DECL: {
            /* rituals declared but not yet invocable by user code. they exist in the void. */
            return value_nulo();
        }

        case AST_BLOCK: {
            Block* bl = (Block*)node->dados;
            Value result = value_nulo();

            Environment* local_env = env_create(rt->current_env);
            Environment* prev_env  = rt->current_env;
            rt->current_env = local_env;

            for (int i = 0; i < bl->num_statements; i++) {
                result = runtime_eval(rt, bl->statements[i]);
                if (rt->return_flag || rt->break_flag || rt->continue_flag) break;
            }

            rt->current_env = prev_env;
            env_free(local_env);
            return result;
        }

        case AST_IF_STMT: {
            IfStmt* is = (IfStmt*)node->dados;
            Value cond = runtime_eval_expr(rt, is->condicao);

            if (is_truthy(cond)) {
                return runtime_eval(rt, is->then_block);
            } else if (is->else_block) {
                return runtime_eval(rt, is->else_block);
            }
            return value_nulo();
        }

        case AST_WHILE_STMT: {
            WhileStmt* ws = (WhileStmt*)node->dados;
            Value result = value_nulo();

            while (is_truthy(runtime_eval_expr(rt, ws->condicao))) {
                result = runtime_eval(rt, ws->body);

                if (rt->break_flag) {
                    rt->break_flag = 0;
                    break;
                }
                if (rt->continue_flag) {
                    rt->continue_flag = 0;
                    continue;
                }
                if (rt->return_flag) break;
            }
            return result;
        }

        case AST_FOR_STMT: {
            ForStmt* fs = (ForStmt*)node->dados;
            Value result = value_nulo();

            Environment* loop_env = env_create(rt->current_env);
            Environment* prev_env = rt->current_env;
            rt->current_env = loop_env;

            if (fs->init) runtime_eval_expr(rt, fs->init);

            while (!fs->condicao || is_truthy(runtime_eval_expr(rt, fs->condicao))) {
                result = runtime_eval(rt, fs->body);

                if (rt->break_flag) {
                    rt->break_flag = 0;
                    break;
                }
                if (rt->continue_flag) {
                    rt->continue_flag = 0;
                }
                if (rt->return_flag) break;

                if (fs->update) runtime_eval_expr(rt, fs->update);
            }

            rt->current_env = prev_env;
            env_free(loop_env);
            return result;
        }

        case AST_RETURN_STMT: {
            ReturnStmt* rs = (ReturnStmt*)node->dados;
            rt->return_value = rs->expr ? runtime_eval_expr(rt, rs->expr) : value_nulo();
            rt->return_flag = 1;
            return rt->return_value;
        }

        case AST_BREAK_STMT: {
            rt->break_flag = 1;
            return value_nulo();
        }

        case AST_CONTINUE_STMT: {
            rt->continue_flag = 1;
            return value_nulo();
        }

        default:
            return runtime_eval_expr(rt, node);
    }
}

/* ============================================================
 * Public API
 * ============================================================ */

Runtime* runtime_create(void) {
    srand((unsigned int)time(NULL));
    Runtime* rt = (Runtime*)malloc(sizeof(Runtime));
    rt->global_env   = env_create(NULL);
    rt->current_env  = rt->global_env;
    rt->break_flag   = 0;
    rt->continue_flag = 0;
    rt->return_flag  = 0;
    rt->return_value = value_nulo();
    return rt;
}

void runtime_free(Runtime* rt) {
    if (!rt) return;
    if (rt->global_env) env_free(rt->global_env);
    free(rt);
}

Value runtime_execute(Runtime* rt, ASTNode* ast) {
    return runtime_eval(rt, ast);
}

void runtime_interpret(Runtime* rt, ASTNode* program) {
    runtime_execute(rt, program);
}
