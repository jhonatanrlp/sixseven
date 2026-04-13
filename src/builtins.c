/*
 * builtins.c — Built-in Function Implementations
 *
 * btw, screamInto() is the civilized print function.
 * btw, chaos() doesn't know what it's going to do either. we're all figuring it out.
 * btw, vibeCheck() will end you. or not. you won't know until it's too late.
 * btw, if you call vibeCheck() and it doesn't crash, it didn't spare you. it's waiting.
 */

#include "builtins.h"
#include "base67.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/* ============================================================
 * screamInto() — the primary print function
 * format: %n for base67 number, %s for string, %t for type
 * ============================================================ */

static void print_formatted(const char* formato, Value* args, int num_args) {
    int arg_index = 1;

    for (int i = 0; formato[i]; i++) {
        if (formato[i] == '%' && formato[i+1]) {
            i++;
            switch (formato[i]) {
                case 'n': {
                    if (arg_index < num_args && args[arg_index].type == VALUE_NUMERO) {
                        char* b67 = decimal_to_base67(args[arg_index].dados.numero);
                        printf("%s", b67);
                        free(b67);
                        arg_index++;
                    }
                    break;
                }
                case 's': {
                    if (arg_index < num_args && args[arg_index].type == VALUE_TEXTO) {
                        printf("%s", args[arg_index].dados.texto);
                        arg_index++;
                    }
                    break;
                }
                case 't': {
                    if (arg_index < num_args) {
                        switch (args[arg_index].type) {
                            case VALUE_NUMERO: printf("chonk"); break;
                            case VALUE_TEXTO:  printf("yapper"); break;
                            case VALUE_BOOL:   printf("sus"); break;
                            case VALUE_NULO:   printf("theVoid"); break;
                            default:           printf("???"); break;
                        }
                        arg_index++;
                    }
                    break;
                }
                default:
                    printf("%%%c", formato[i]);
            }
        } else if (formato[i] == '\\' && formato[i+1]) {
            i++;
            switch (formato[i]) {
                case 'n':  printf("\n");   break;
                case 't':  printf("\t");   break;
                case '\\': printf("\\");  break;
                default:   printf("\\%c", formato[i]);
            }
        } else {
            printf("%c", formato[i]);
        }
    }
}

static const char* dramatic_sign_offs[] = {
    "haha67",
    "kkk67",
    "KKKKK^67^",
    "jajaja67",
    "*base67intensifies*",
    "lolololo67",
    "67lmao",
    "hehehehe67",
    "sent from my base67 device",
    "this message was certified cursed",
    "and scene.",
    "...ok?",
    "wow. just wow.",
    "i am so tired."
};
#define NUM_SIGN_OFFS 14

Value builtin_scream_into(Value* args, int num_args) {
    if (num_args == 0) return value_nulo();

    if (args[0].type != VALUE_TEXTO) {
        fprintf(stderr, "this ain't it chief. screamInto() needs a string as first argument.\n");
        return value_nulo();
    }

    print_formatted(args[0].dados.texto, args, num_args);

    int idx = rand() % NUM_SIGN_OFFS;
    printf("\n%s\n", dramatic_sign_offs[idx]);

    return value_nulo();
}

/* screamInto alias: printf_troll still works because we're sentimental */
Value builtin_printf_troll(Value* args, int num_args) {
    return builtin_scream_into(args, num_args);
}

/* ============================================================
 * chaos() — does one of three things. you'll find out which.
 * ============================================================ */

static const char* passive_aggressive[] = {
    "oh, you called chaos(). bold. brave. stupid.",
    "chaos() was invoked. chaos() is unimpressed.",
    "interesting choice. chaos() is watching you.",
    "wow, chaos(). we're really doing this.",
    "chaos() called. chaos() considered leaving. chaos() stayed. unfortunately.",
    "you asked for chaos. chaos would like to remind you this is your fault.",
    "chaos() has logged your request. chaos() does not care.",
    "chaos() is evaluating your life choices. results pending.",
    "you rang? — chaos (uninvited)",
    "chaos() checked in. chaos() checked right back out."
};
#define NUM_PASSIVE 10

Value builtin_chaos(Value* args, int num_args) {
    int roll = rand() % 3;

    switch (roll) {
        case 0: {
            /* returns a random number. surprise. */
            long long n = rand() % 4489;  /* 4489 = 67*67, for the aesthetic */
            return value_numero(n);
        }
        case 1: {
            /* prints a passive-aggressive message */
            int idx = rand() % NUM_PASSIVE;
            printf("%s\n", passive_aggressive[idx]);
            return value_nulo();
        }
        case 2:
        default: {
            /* does absolutely nothing. silently. */
            /* this is the most disturbing outcome. */
            return value_nulo();
        }
    }
}

/* ============================================================
 * vibeCheck() — you either pass or you don't. no partial credit.
 * ============================================================ */

Value builtin_vibe_check(Value* args, int num_args) {
    if (rand() % 2 == 0) {
        /* vibe check: failed. goodbye. */
        fprintf(stderr, "\nvibe check failed. you simply did not pass.\n");
        fprintf(stderr, "[program terminated by the universe]\n");
        exit(1);
    }
    /* vibe check: passed. this time. */
    printf("vibe check passed. (you got lucky.)\n");
    return value_nulo();
}

/* ============================================================
 * panic67() — for when you really need to stop everything
 * ============================================================ */

Value builtin_panic67(Value* args, int num_args) {
    fprintf(stderr, "\n███ PANIC IN BASE 67 ███\n");

    if (num_args > 0 && args[0].type == VALUE_TEXTO) {
        fprintf(stderr, "%s\n", args[0].dados.texto);
    } else {
        fprintf(stderr, "(no message. just vibes. bad vibes.)\n");
    }

    fprintf(stderr, "[process terminated with prejudice]\n");
    exit(1);
}

/* ============================================================
 * compile_na_sorte() — random number 0-66. you're welcome.
 * ============================================================ */

Value builtin_compile_na_sorte(Value* args, int num_args) {
    long long sorte = rand() % 67;
    return value_numero(sorte);
}

/* ============================================================
 * loop_infinito_de_praia() — waves. just... waves.
 * ============================================================ */

Value builtin_loop_infinito_de_praia(Value* args, int num_args) {
    long long segundos = 0;
    if (num_args > 0 && args[0].type == VALUE_NUMERO) {
        segundos = args[0].dados.numero;
    }

    for (long long i = 0; i < segundos; i++) {
        printf("🌊 ");
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
    return value_nulo();
}

/* ============================================================
 * segfault_de_brincadeira() — fake segfault. therapeutic.
 * ============================================================ */

Value builtin_segfault_de_brincadeira(Value* args, int num_args) {
    printf("Segmentation Fault (simulated. we're not animals. base67 is, but we aren't.)\n");
    return value_nulo();
}

/* ============================================================
 * converter_para_decimal() — converts base67 to decimal
 * ============================================================ */

Value builtin_converter_para_decimal(Value* args, int num_args) {
    if (num_args == 0) return value_numero(0);

    if (args[0].type == VALUE_NUMERO) {
        return value_numero(args[0].dados.numero);
    }
    if (args[0].type == VALUE_TEXTO) {
        long long decimal = base67_to_decimal(args[0].dados.texto);
        return value_numero(decimal);
    }
    return value_numero(0);
}

/* ============================================================
 * tamanho_em_bytes() — size in bytes. a fun fact about your data.
 * ============================================================ */

Value builtin_tamanho_em_bytes(Value* args, int num_args) {
    if (num_args == 0) return value_numero(0);

    long long tamanho = 0;
    switch (args[0].type) {
        case VALUE_NUMERO: tamanho = sizeof(long long); break;
        case VALUE_TEXTO:  tamanho = strlen(args[0].dados.texto ? args[0].dados.texto : ""); break;
        case VALUE_BOOL:   tamanho = sizeof(int); break;
        case VALUE_NULO:   tamanho = 1; break;
        default:           tamanho = 0;
    }
    return value_numero(tamanho);
}

/* ============================================================
 * imprimir_base67() — prints number in base67 representation
 * ============================================================ */

Value builtin_imprimir_base67(Value* args, int num_args) {
    if (num_args == 0) return value_nulo();

    if (args[0].type == VALUE_NUMERO) {
        char* b67 = decimal_to_base67(args[0].dados.numero);
        printf("%s\n", b67);
        free(b67);
    } else {
        char* str = value_to_string(args[0]);
        printf("%s\n", str);
        free(str);
    }
    return value_nulo();
}

/* ============================================================
 * Builtin registry — the complete list of things we've done
 * ============================================================ */

int is_builtin(const char* name) {
    if (!name) return 0;

    const char* builtins[] = {
        "screamInto",
        "chaos",
        "vibeCheck",
        "printf_troll",
        "panic67",
        "compile_na_sorte",
        "loop_infinito_de_praia",
        "segfault_de_brincadeira",
        "converter_para_decimal",
        "tamanho_em_bytes",
        "imprimir_base67",
        NULL
    };

    for (int i = 0; builtins[i]; i++) {
        if (strcmp(name, builtins[i]) == 0) return 1;
    }
    return 0;
}

NativeFn builtin_get_function(const char* name) {
    if (!name) return NULL;

    if (strcmp(name, "screamInto")              == 0) return builtin_scream_into;
    if (strcmp(name, "chaos")                   == 0) return builtin_chaos;
    if (strcmp(name, "vibeCheck")               == 0) return builtin_vibe_check;
    if (strcmp(name, "printf_troll")            == 0) return builtin_printf_troll;
    if (strcmp(name, "panic67")                 == 0) return builtin_panic67;
    if (strcmp(name, "compile_na_sorte")        == 0) return builtin_compile_na_sorte;
    if (strcmp(name, "loop_infinito_de_praia")  == 0) return builtin_loop_infinito_de_praia;
    if (strcmp(name, "segfault_de_brincadeira") == 0) return builtin_segfault_de_brincadeira;
    if (strcmp(name, "converter_para_decimal")  == 0) return builtin_converter_para_decimal;
    if (strcmp(name, "tamanho_em_bytes")        == 0) return builtin_tamanho_em_bytes;
    if (strcmp(name, "imprimir_base67")         == 0) return builtin_imprimir_base67;

    return NULL;
}
