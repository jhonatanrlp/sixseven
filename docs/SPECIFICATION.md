# Base SixSeven - Especificação Técnica Completa

**Versão: 1.0**  
**Status: Base 67 - Linguagem Real**

---

## 1. Introdução

**Base SixSeven** é uma linguagem de programação real, implementada em C, onde **TODA operação numérica ocorre em base 67**.

Esta não é uma piada. Esta não é uma excentricidade sintática. **Base 67 é a regra estrutural incontestável da linguagem.**

Quando você escreve `10` em Base SixSeven, você está escrevendo o número em base 67. Isso equivale a $1 \times 67 + 0 = 67$ em decimal.

---

## 2. Representação em Base 67

### 2.1 Alfabeto

Base 67 usa 67 símbolos distintos para representar valores:

```
Posição  Símbolo   Intervalo
0-9      0-9       (dígitos decimais)
10-35    a-z       (26 minúsculas)
36-61    A-Z       (26 maiúsculas)
62-66    !@#$%     (5 símbolos especiais)
```

**Tabela completa:**

| Valor | Símbolo | Valor | Símbolo | Valor | Símbolo | Valor | Símbolo |
|-------|---------|-------|---------|-------|---------|-------|---------|
| 0     | 0       | 17    | h       | 34    | y       | 51    | P       |
| 1     | 1       | 18    | i       | 35    | z       | 52    | Q       |
| 2     | 2       | 19    | j       | 36    | A       | 53    | R       |
| 3     | 3       | 20    | k       | 37    | B       | 54    | S       |
| 4     | 4       | 21    | l       | 38    | C       | 55    | T       |
| 5     | 5       | 22    | m       | 39    | D       | 56    | U       |
| 6     | 6       | 23    | n       | 40    | E       | 57    | V       |
| 7     | 7       | 24    | o       | 41    | F       | 58    | W       |
| 8     | 8       | 25    | p       | 42    | G       | 59    | X       |
| 9     | 9       | 26    | q       | 43    | H       | 60    | Y       |
| 10    | a       | 27    | r       | 44    | I       | 61    | Z       |
| 11    | b       | 28    | s       | 45    | J       | 62    | !       |
| 12    | c       | 29    | t       | 46    | K       | 63    | @       |
| 13    | d       | 30    | u       | 47    | L       | 64    | #       |
| 14    | e       | 31    | v       | 48    | M       | 65    | $       |
| 15    | f       | 32    | w       | 49    | N       | 66    | %       |
| 16    | g       | 33    | x       | 50    | O       |       |         |

### 2.2 Conversão: Base 67 → Decimal

Para converter número em base 67 para decimal, use a série polinomial:

$$\text{decimal} = \sum_{i=0}^{n} d_i \times 67^i$$

Onde $d_i$ é o valor do i-ésimo dígito.

**Exemplos:**

| Base 67 | Cálculo | Decimal |
|---------|---------|---------|
| 0 | 0 | 0 |
| 9 | 9 | 9 |
| 10 | $1 \times 67 + 0$ | 67 |
| 11 | $1 \times 67 + 1$ | 68 |
| 1a | $1 \times 67 + 10$ | 77 |
| Z | 61 | 61 |
| 1Z | $1 \times 67 + 61$ | 128 |
| 20 | $2 \times 67 + 0$ | 134 |
| aa | $10 \times 67 + 10$ | 680 |

### 2.3 Conversão: Decimal → Base 67

Algoritmo de divisão repetida:

```
valor = valor_decimal
resultado = ""

enquanto valor > 0:
    resto = valor mod 67
    resultado = alfabeto[resto] + resultado
    valor = valor / 67

retornar resultado
```

**Exemplos:**

| Decimal | Divisões | Base 67 |
|---------|----------|---------|
| 67 | 67 ÷ 67 = 1 r 0 | 10 |
| 77 | 77 ÷ 67 = 1 r 10 | 1a |
| 134 | 134 ÷ 67 = 2 r 0 | 20 |
| 680 | 680 ÷ 67 = 10 r 10 | aa |

---

## 3. Especificação Léxica

### 3.1 Tokens

#### Literais

- **Número em Base 67**: Sequência de um ou mais caracteres do alfabeto base 67. **SEMPRE interpretado como base 67**.
  - Exemplo: `10`, `1a`, `Z`, `aa`
  
- **String**: Sequência de caracteres entre aspas duplas.
  - Exemplo: `"olá mundo"`

#### Palavras-chave

```
var         Declaração de variável
funcao      Declaração de função
se          Condicional if
senao       Else
enquanto    While loop
para        For loop
retorne     Return statement
quebra      Break
continua    Continue
verdeiro    Literal true (booleano)
falso       Literal false (booleano)
nulo        Literal null/nil
```

#### Operadores

**Aritméticos (todos em base 67):**
- `+` adição
- `-` subtração
- `*` multiplicação
- `/` divisão inteira
- `%` módulo

**Relacionais (comparação em base 67):**
- `<` menor que
- `>` maior que
- `<=` menor ou igual
- `>=` maior ou igual
- `==` igual
- `!=` diferente

**Lógicos:**
- `&&` AND
- `||` OR
- `!` NOT

**Atribuição:**
- `=` atribuição

#### Delimitadores

- `(` `)` parênteses
- `{` `}` chaves
- `,` vírgula
- `;` ponto-e-vírgula

### 3.2 Comentários

Comentários começam com `#` e vão até o fim da linha:

```base67
# Este é um comentário
var x = 5;  # Comentário inline
```

---

## 4. Especificação Sintática (EBNF)

```ebnf
program         = statement* ;

statement       = var_declaration
                | function_declaration
                | if_statement
                | while_statement
                | for_statement
                | return_statement
                | break_statement
                | continue_statement
                | block
                | expression_statement
                ;

var_declaration = "var" IDENTIFIER "=" expression ";" ;

function_declaration = "funcao" IDENTIFIER "(" parameter_list? ")" block ;

parameter_list  = IDENTIFIER ("," IDENTIFIER)* ;

if_statement    = "se" "(" expression ")" block ("senao" block)? ;

while_statement = "enquanto" "(" expression ")" block ;

for_statement   = "para" "(" expression? ";" expression? ";" expression? ")" block ;

return_statement = "retorne" expression? ";" ;

break_statement = "quebra" ";" ;

continue_statement = "continua" ";" ;

block           = "{" statement* "}" ;

expression_statement = expression ";" ;

expression      = assignment ;

assignment      = IDENTIFIER "=" assignment
                | logical_or
                ;

logical_or      = logical_and ("||" logical_and)* ;

logical_and     = equality ("&&" equality)* ;

equality        = relational (("==" | "!=") relational)* ;

relational      = additive (("<" | ">" | "<=" | ">=") additive)* ;

additive        = multiplicative (("+" | "-") multiplicative)* ;

multiplicative  = unary (("*" | "/" | "%") unary)* ;

unary           = ("!" | "-") unary | postfix ;

postfix         = primary ("(" argument_list? ")")* ;

argument_list   = expression ("," expression)* ;

primary         = NUMBER
                | STRING
                | IDENTIFIER
                | "verdeiro"
                | "falso"
                | "nulo"
                | "(" expression ")"
                ;

IDENTIFIER      = [a-zA-Z_][a-zA-Z0-9_]* ;

NUMBER          = [0-9a-zA-Z!@#$%^&]+ ;  # Base 67 alphabet

STRING          = '"' (~[\\"])* '"' ;
```

### 4.1 Precedência de Operadores

(Do menor para maior precedência)

1. `=` (atribuição)
2. `||` (OR lógico)
3. `&&` (AND lógico)
4. `==`, `!=` (igualdade)
5. `<`, `>`, `<=`, `>=` (relacional)
6. `+`, `-` (aditivo)
7. `*`, `/`, `%` (multiplicativo)
8. `!`, `-` (unário)
9. `()` (chamada de função, primária)

---

## 5. Tipo de Dados

Base SixSeven usa tipagem dinâmica. Cada valor tem um tipo em tempo de execução:

### 5.1 Número (num)

- Armazenado internamente como `long long` (decimal)
- Sempre interpretado como base 67 em literais e operações
- Suporta: adição, subtração, multiplicação, divisão inteira, módulo

### 5.2 Texto (string)

- Sequência de caracteres UTF-8
- Operações: impressão, concatenação (via funções)

### 5.3 Booleano (bool)

- `verdeiro` ou `falso`
- Usado em condicionais
- Operadores: `&&`, `||`, `!`

### 5.4 Nulo (null)

- Valor `nulo`
- Representa ausência de valor

---

## 6. Scopings e Ambiente

### 6.1 Escopo Léxico

Base SixSeven segue escopo léxico aninhado com blocos `{}`:

```base67
var global = 5;

funcao exemplo() {
    var local = 10;
    
    se (verdeiro) {
        var bloco_local = 15;
        # bloco_local é visível aqui
        # local e global também
    }
    
    # bloco_local NÃO é visível aqui
    # local e global são visíveis
}
```

### 6.2 Sombreamento

Variáveis locais sombreiam variáveis globais com mesmo nome:

```base67
var x = 10;

funcao teste() {
    var x = 20;  # Sombra o x global
    printf_troll("x = %n\n", x);  # Imprime 20
}
```

---

## 7. Funções Integradas (Builtins)

### 7.1 printf_troll(formato, ...)

Função de impressão formatada com risada troll.

**Uso:**
```base67
printf_troll("Mensagem com valor %n\n", valor);
```

**Especificadores:**
- `%n` → número em base 67
- `%s` → string
- `%t` → tipo do valor
- `\n` → nova linha
- `\t` → tabulação

**Comportamento:** Imprime mensagem formatada e adiciona risada aleatória ao final.

### 7.2 panic67(mensagem)

Imprime mensagem de pânico e encerra programa.

**Uso:**
```base67
panic67("Algo deu errado!");
```

**Saída:**
```
███ PANIC NA BASE 67: Algo deu errado!
[processo terminado com código 1]
```

### 7.3 compile_na_sorte()

Retorna número aleatório entre 0 e 66 em base 67.

**Uso:**
```base67
var numero = compile_na_sorte();
```

### 7.4 loop_infinito_de_praia(segundos)

Executa loop por N segundos, emitindo ondas do mar.

**Uso:**
```base67
loop_infinito_de_praia(3);  # Executa por 3 segundos
```

### 7.5 segfault_de_brincadeira()

Simula segmentation fault (mas não causa real).

**Uso:**
```base67
segfault_de_brincadeira();
# Saída: Segmentation Fault (simulado, não te preocupa 67)
```

### 7.6 converter_para_decimal(valor_base67)

Converte número em base 67 para decimal (retorna como base 67).

**Uso:**
```base67
var resultado = converter_para_decimal(10);
# 10 em base 67 = 67 em decimal = 10 em base 67 novamente
```

### 7.7 tamanho_em_bytes(valor)

Retorna tamanho em bytes do valor.

**Uso:**
```base67
var tam = tamanho_em_bytes(numero);
```

### 7.8 imprimir_base67(valor)

Imprime valor em base 67 (conveniente).

**Uso:**
```base67
imprimir_base67(100);
```

---

## 8. Tratamento de Erros

Todos os erros em Base SixSeven mencionam explicitamente base 67:

### 8.1 Erros Léxicos

```
Erro léxico: Símbolo '§' não é válido em base 67 (linha 5, coluna 12)
```

### 8.2 Erros de Parsing

```
Erro de parsing: Esperado ';' no final da declaração (linha 3)
```

### 8.3 Erros de Runtime

```
Erro: Divisão por zero em operação base 67
Erro: Operação aritmética '+' requer dois números em base 67
```

---

## 9. Exemplo Completo: Fibonacci

```base67
funcao fib(n) {
    se (n <= 1) {
        retorne n;
    }
    retorne fib(n - 1) + fib(n - 2);
}

funcao main() {
    # Calcular Fibonacci até 6 (em base 67)
    para (var i = 0; i < 6; i = i + 1) {
        var resultado = fib(i);
        printf_troll("fib(%n) = %n\n", i, resultado);
    }
    retorne 0;
}

main();
```

**Saída (com valores em base 67):**
```
fib(0) = 0
fib(1) = 1
fib(2) = 1
fib(3) = 2
fib(4) = 3
fib(5) = 5
```

---

## 10. Modo Debug

O interpretador suporta modo debug:

```bash
./sixseven programa.s67 --debug-tokens  # Mostra tokens gerados
./sixseven programa.s67 --debug-ast     # Mostra AST gerada
```

---

## 11. Limitações e Considerações

1. **Sem funções aninhadas**: Funções só podem ser declaradas globalmente
2. **Sem closures explícitas**: Mas há lexical scoping
3. **Sem tipos complexos**: Apenas primitivos
4. **Sem ponteiros**: Mascaradas (apenas valores)
5. **Sem classes/objetos**: Apenas funções e valores

---

## 12. Conclusão

**Base SixSeven é uma linguagem de programação real e completa onde TODA aritmética ocorre em base 67.**

Este não é um easter egg. Este não é um hack. Esta é a característica central e incontestável da linguagem.

Quando você programa em Base SixSeven, **você está programando em base 67 de ponta a ponta**.

---

**Versão 1.0 - Base 67 é responsabilidade do programador.**
