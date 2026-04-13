# Base SixSeven - Guia de Implementação em C

**Versão: 1.0**

---

## 1. Visão Geral da Arquitetura

A implementação de Base SixSeven em C segue uma arquitetura clássica de interpretadores:

```
Código Fonte
    ↓
[LEXER] → Tokens (base 67 com valores decimais)
    ↓
[PARSER] → AST (Árvore de Sintaxe Abstrata)
    ↓
[RUNTIME] → Execução (Interpretação direta da AST)
    ↓
Resultado
```

---

## 2. Módulos Principais

### 2.1 base67.c / base67.h

**Responsabilidade:** Conversão entre base 67 e decimal

**Funções principais:**
- `base67_char_value(char)` – Retorna valor (0-66) de um símbolo base 67
- `base67_value_to_char(int)` – Converte valor para símbolo
- `base67_to_decimal(str)` – String base 67 → long long decimal
- `decimal_to_base67(long)` – long long decimal → string base 67
- `is_valid_base67_number(str)` – Valida se string é número válido

**Exemplo de use:**
```c
long long decimal = base67_to_decimal("1a");  // 77
char* b67 = decimal_to_base67(77);             // "1a"
```

### 2.2 lexer.c / lexer.h

**Responsabilidade:** Tokenização do código-fonte

**Estruturas principais:**
- `TokenType` – Enum dos tipos de token (TOKEN_NUMERO, TOKEN_IDENT, etc)
- `Token` – Estrutura com tipo, lexema, linha, coluna, e valor decimal (para números)
- `Lexer` – Estado do lexer

**Funções principais:**
- `lexer_create(source)` – Inicializa lexer
- `lexer_next_token(lexer)` – Obtém próximo token
- `lexer_free(lexer)` – Libera lexer

**Aspecto crítico:** Números são parseados como base 67 e convertidos para decimal usando `base67_to_decimal()`.

```c
Token tok = lexer_next_token(lexer);
if (tok.type == TOKEN_NUMERO) {
    // tok.valor_decimal já contém conversão de base 67
    printf("Número: %lld\n", tok.valor_decimal);
}
```

### 2.3 value.c / value.h

**Responsabilidade:** Tipo genérico para valores em runtime

**Estrutura principal:**
```c
typedef struct Value {
    ValueType type;  // NUMERO, TEXTO, BOOL, NULO, etc
    union {
        long long numero;    // Sempre em decimal (equivalente base 67)
        char* texto;
        int boolean;
        void* ptr;
    } dados;
} Value;
```

**Funções principais:**
- `value_numero(long)` – Criar número
- `value_texto(str)` – Criar string
- `value_bool(int)` – Criar booleano
- `value_to_string(Value)` – Converter valor para string (números → base 67)
- `value_numero_to_base67(Value)` – Número → base 67 string

### 2.4 ast.c / ast.h

**Responsabilidade:** Representação da árvore de sintaxe abstrata

**Estrutura principal:**
```c
typedef struct ASTNode {
    ASTNodeType type;     // AST_LITERAL, AST_BINARY_OP, etc
    void* dados;          // Polimórfico
    struct ASTNode** children;
    int num_children;
} ASTNode;
```

**Tipos de nó:**
- `AST_PROGRAMA` – Raiz do programa
- `AST_LITERAL` – Valor constante
- `AST_IDENT` – Identificador
- `AST_BINARY_OP` – Operação binária (+, -, *, /, ==, etc)
- `AST_VAR_DECL` – Declaração de variável
- `AST_IF_STMT`, `AST_WHILE_STMT`, `AST_FOR_STMT` – Controle de fluxo
- `AST_CALL_EXPR` – Chamada de função
- etc

### 2.5 parser.c / parser.h

**Responsabilidade:** Análise sintática (tokens → AST)

**Abordagem:** Recursive descent parsing com precedência de operadores

**Estrutura:**
```c
typedef struct {
    Token* tokens;
    int num_tokens;
    int current;
} Parser;
```

**Funções principais:**
- `parser_create(tokens, num)` – Inicializa parser
- `parser_parse(parser)` – Parsea programa completo
- `parser_get_error(parser)` – Obtém mensagem de erro

**Precedência:** Implementada via funções aninhadas:
```
parse_program() → parse_stmt() → parse_expr()
    → parse_assignment() → parse_logical_or()
        → parse_logical_and() → parse_equality()
            → parse_relational() → parse_additive()
                → parse_multiplicative() → parse_unary()
                    → parse_postfix() → parse_primary()
```

### 2.6 runtime.c / runtime.h

**Responsabilidade:** Interpretação (execução da AST)

**Estruturas principais:**
```c
typedef struct Environment {
    char** var_names;
    Value* var_values;
    int num_vars;
    struct Environment* parent;  // Para escopo aninhado
} Environment;

typedef struct {
    Environment* global_env;
    Environment* current_env;
    int break_flag;
    int continue_flag;
    int return_flag;
    Value return_value;
} Runtime;
```

**Funções principais:**
- `runtime_create()` – Cria runtime
- `runtime_execute(rt, ast)` – Executa nó AST
- `runtime_interpret(rt, program)` – Interpretador principal

**Operações aritméticas:** Aproveitam que valores estão em decimal. As operações mantêm o invariante de que números sempre se comportam como base 67.

### 2.7 builtins.c / builtins.h

**Responsabilidade:** Funções integradas (printf_troll, panic67, etc)

**Estrutura:**
```c
typedef Value (*NativeFn)(Value* args, int num_args);
```

**Funções:**
- `printf_troll()` – Print com risada
- `panic67()` – Pânico
- `compile_na_sorte()` – Aleatório
- `loop_infinito_de_praia()` – Loop com ondas
- `segfault_de_brincadeira()` – Simulação de erro
- etc

---

## 3. Fluxo de Execução Completo

### 3.1 Entrada: hello_world.s67

```base67
funcao main() {
    printf_troll("Olá!");
}

main();
```

### 3.2 Fase 1: Tokenização

```
main → TOKEN_FUNCAO
"Olá!" → TOKEN_STRING (lexeme="Olá!")
etc
```

**Código:**
```c
Lexer* lex = lexer_create(source);
Token tok = lexer_next_token(lex);
```

### 3.3 Fase 2: Parsing

Tokens são convertidos em AST:

```
AST_PROGRAMA
└── AST_FUNC_DECL (main)
    └── AST_BLOCK
        └── AST_CALL_EXPR (printf_troll)
            └── AST_LITERAL ("Olá!")
└── AST_CALL_EXPR (main)
```

**Código:**
```c
Parser* p = parser_create(tokens, num_tokens);
ASTNode* ast = parser_parse(p);
```

### 3.4 Fase 3: Execução

Runtime percorre AST recursivamente:

```c
case AST_CALL_EXPR: {
    CallExpr* ce = (CallExpr*)expr->dados;
    if (is_builtin(ce->nome)) {
        NativeFn fn = builtin_get_function(ce->nome);
        Value result = fn(args, num_args);
        return result;
    }
}
```

---

## 4. Tratamento de Base 67 na Implementação

### 4.1 Números em Literais

No lexer, números são parseados como base 67 e convertidos para decimal:

```c
if (is_base67_digit(c)) {
    // Coletar dígitos base 67
    char* lexeme = extract_base67_number();
    
    // Converter para decimal
    long long decimal_val = base67_to_decimal(lexeme);
    
    // Armazenar no token
    return Token{
        .type = TOKEN_NUMERO,
        .valor_decimal = decimal_val
    };
}
```

### 4.2 Operações Aritméticas

As operações trabalham em decimal, mantendo o invariante base 67:

```c
Value arithmetic_op(char* op, Value left, Value right) {
    long long l = left.dados.numero;      // Decimal (base 67)
    long long r = right.dados.numero;     // Decimal (base 67)
    
    if (strcmp(op, "+") == 0) {
        return value_numero(l + r);      // Resultado em decimal (base 67)
    }
}
```

**Invariante:** Qualquer `Value` com `type == VALUE_NUMERO` tem `dados.numero` em decimal, que funciona equivalentemente a base 67.

### 4.3 Conversão para Impressão

Quando exibimos números, convertemos para base 67:

```c
case VALUE_NUMERO: {
    char* b67 = decimal_to_base67(v.dados.numero);
    printf("%s", b67);
    free(b67);
    break;
}
```

---

## 5. Gerenciamento de Memória

### 5.1 Padrão de Alocação

```c
// Alocar
char* str = (char*)malloc(size);

// Usar
strcpy(str, data);

// Liberar em função apropriada
free(str);
```

### 5.2 Limpeza de AST

Recurver em toda árvore:

```c
void ast_free(ASTNode* node) {
    if (!node) return;
    
    // Liberar dados específicos do tipo
    switch (node->type) {
        case AST_LITERAL:
            value_free(((Literal*)node->dados)->value);
            break;
        // etc
    }
    
    // Liberar children
    for (int i = 0; i < node->num_children; i++) {
        ast_free(node->children[i]);
    }
    free(node->children);
    free(node);
}
```

---

## 6. Extensões Futuras

### 6.1 Funções Definidas pelo Usuário

Atualmente não suporti. Seria necessário:
1. Armazenar `FuncDecl` em ambiente global
2. Na chamada, criar `Environment` novo com parâmetros
3. Executar corpo em novo ambiente

### 6.2 Estruturas de Dados

Arrays e structs exigiriam:
- Tipo `VALUE_ARRAY` / `VALUE_STRUCT`
- Indexação e acesso a campos
- Gerenciamento de memória complexo

### 6.3 Módulos e Imports

Suporte a múltiplos arquivos seria:
- Lexer de caminhos
- Parser de `import` statements
- Ambiente global compartilhado

---

## 7. Considerações de Performance

### 7.1 Pontos Quentes

1. **Conversão base 67 ↔ decimal** – Chamada frequente
   - Otimização: Cache de valores pequenos

2. **Busca em ambiente** – Linear para cada variável
   - Otimização: Hash table ao invés de arrays

3. **Alocação de memória** – Muitas alocações pequenas
   - Otimização: Memory pool

---

## 8. Compilação

### 8.1 Dependências

- C99 ou posterior
- libm (math library) para operações futuras

### 8.2 Flags Recomendadas

```bash
gcc -Wall -Wextra -std=c99 -O2 -o sixseven *.c -lm
```

---

## 9. Conclusão

A implementação de Base SixSeven em C é direta e modular:

1. **Base 67** é uma responsabilidade bem-localizada (base67.c)
2. **Lexer** parsea base 67 e converte para decimal
3. **Runtime** trabalha com decimal (equivalente base 67)
4. **Impressão** reconverte para base 67 para exibição

**Invariante:** Números estão sempre em decimal internamente, mas se comportam e aparentam ser base 67 ao usuário.

---

Base SixSeven usa base 67 de ponta a ponta em sua implementação.
