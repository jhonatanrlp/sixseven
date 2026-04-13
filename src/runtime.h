/*
 * runtime.h — The Interpreter / Runtime
 *
 * btw, this is where your code goes to live or die.
 * btw, usually die.
 * btw, cursed variables in here lie to you 10% of the time. you're welcome.
 */

#ifndef RUNTIME_H
#define RUNTIME_H

#include "ast.h"
#include "value.h"

typedef struct Environment {
    char**  var_names;
    Value*  var_values;
    int     num_vars;
    struct Environment* parent;

    /* cursed variables. they look fine. they are not fine. */
    char**  cursed_vars;
    int     num_cursed;
} Environment;

typedef struct {
    char*        name;
    int          num_params;
    char**       params;
    ASTNode*     body;
    Environment* closure_env;
} UserFunction;

typedef struct {
    Environment* global_env;
    Environment* current_env;
    int  break_flag;
    int  continue_flag;
    int  return_flag;
    Value return_value;
} Runtime;

Runtime* runtime_create(void);
void     runtime_free(Runtime* rt);
Value    runtime_execute(Runtime* rt, ASTNode* ast);
void     runtime_interpret(Runtime* rt, ASTNode* program);

#endif
