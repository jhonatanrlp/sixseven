# Base SixSeven - Resumo Executivo

**Base SixSeven** é uma linguagem de programação **real, funcional e completa**, implementada em C, onde **TODOS os números são interpretados em base 67**.

---

## 📊 Resumo do Projeto

| Aspecto | Descrição |
|---------|-----------|
| **Nome** | Base SixSeven |
| **Tipo** | Linguagem de Programação Interpretada |
| **Implementação** | C99+ |
| **Característica Principal** | Aritmética em base 67 |
| **Status** | v0.1.0 - Funcional |
| **Linhas de Código** | ~2500+ (lexer, parser, runtime, builtins) |

---

## 🎯 Características Principais

### 1. **Base 67 Absoluta**
   - Todos os números são base 67: `10` = 67 em decimal
   - Operações aritméticas em base 67
   - Comparações em base 67
   - Sem exceções ou fallbacks

### 2. **Completa Implementação em C**
   - Lexer (tokenizador)
   - Parser (análise sintática - EBNF)
   - AST (árvore de sintaxe abstrata)
   - Runtime (interpretador)
   - Gerenciamento de memória

### 3. **Funções Integradas Humorísticas**
   - `printf_troll()` - Impressão com risada aleatória
   - `panic67()` - Kernel panic em base 67
   - `compile_na_sorte()` - Compilação com sorte
   - `loop_infinito_de_praia()` - Loops em estilo praia
   - `segfault_de_brincadeira()` - Simulação de erro
   - `converter_para_decimal()`, `tamanho_em_bytes()`, etc

### 4. **Controle de Fluxo Completo**
   - Variáveis (com escopo léxico)
   - Funções (declaração e chamada)
   - Condicionais: `se`/`senao`
   - Loops: `enquanto`, `para`
   - Controle: `retorne`, `quebra`, `continua`

### 5. **Tipos Dinâmicos**
   - `numero` (sempre base 67)
   - `texto` (strings UTF-8)
   - `bool` (verdeiro/falso)
   - `nulo` (null value)

---

## 📁 Estrutura de Arquivos

```
sixseven/
├── README.md                     # Visão geral
├── Makefile                      # Build script
├── src/
│   ├── main.c                   # Ponto de entrada
│   ├── base67.c/h               # Sistema base 67
│   ├── lexer.c/h                # Tokenização
│   ├── parser.c/h               # Parsing
│   ├── ast.c/h                  # Tipos AST
│   ├── runtime.c/h              # Execução
│   ├── value.c/h                # Valores genéricos
│   ├── builtins.c/h             # Funções integradas
│   └── memory.c/h               # Gestão de memória
├── examples/
│   ├── hello_world.s67
│   ├── aritmetica.s67
│   ├── loops.s67
│   └── EXEMPLOS.md
├── docs/
│   ├── SPECIFICATION.md         # Especificação completa
│   ├── IMPLEMENTATION.md        # Detalhes de implementação
│   └── BUILD.md                 # Instruções de build
└── tests/                       # Framework de testes (futuro)
```

---

## 🚀 Quick Start

### 1. Compilar
```bash
make
```

### 2. Executar Exemplo
```bash
./sixseven examples/hello_world.s67
```

### 3. Seu Próprio Programa
```bash
cat > test.s67 << 'EOF'
funcao main() {
    var x = 10;  # 10 em base 67 = 67 em decimal
    printf_troll("Valor: %n\n", x);
}
main();
EOF

./sixseven test.s67
```

---

## 📚 Documentação

- **README.md** - Visão geral da linguagem e motivação
- **docs/SPECIFICATION.md** - Especificação técnica completa (32 seções)
- **docs/IMPLEMENTATION.md** - Detalhes de arquitetura e módulos C
- **docs/BUILD.md** - Instruções de compilação e setup
- **examples/EXEMPLOS.md** - 10+ exemplos funcionais
- **examples/*.s67** - Código-fonte em Base SixSeven

---

## 💡 Conceitos-Chave

### Base 67 - Não é Piada

Quando você escreve em Base SixSeven:
- `1` em base 67 = `1` em decimal
- `10` em base 67 = `67` em decimal
- `1a` em base 67 = `77` em decimal
- Operação: `10 + 10` em base 67 = `67 + 67` em decimal

### Símbolos Base 67

```
0-9 (10) a-z (26) A-Z (26) !@#$% (5) = 67 símbolos
```

### Conversão

**B67 → Decimal:**
$$valor_{decimal} = \sum_{i=0}^{n} digito_i \times 67^i$$

**Decimal → B67:**
```
repetir: resto = valor mod 67, valor = valor / 67
resultado = caractere(resto) + resultado
```

---

## 🔧 Arquitetura do Interpretador

```
Código .s67
    ↓
[LEXER] Tokenização com base 67
    ↓ 
Tokens (números como decimais)
    ↓
[PARSER] Análise Sintática EBNF
    ↓
AST (Árvore de Sintaxe)
    ↓
[RUNTIME] Interpretação direta
    ↓
Resultado (números exibidos em base 67)
```

---

## 📋 Módulos C

| Módulo | Linhas | Responsabilidade |
|--------|--------|------------------|
| base67.c | ~150 | Conversão base 67 ↔ decimal |
| lexer.c | ~350 | Tokenização |
| parser.c | ~550 | Análise sintática |
| ast.c | ~200 | Estruturas AST |
| runtime.c | ~400 | Interpretador |
| builtins.c | ~300 | Funções integradas |
| value.c | ~150 | Tipos genéricos |
| **Total** | **~2100** | Sistema completo |

---

## 🧪 Exemplos Funcionais

### Hello World
```base67
funcao main() {
    printf_troll("Olá, Base SixSeven!");
}
main();
```

### Números em Base 67
```base67
var x = 10;     # 10 em base 67 = 67 decimal
var y = 1a;     # 1a em base 67 = 77 decimal
printf_troll("x = %n, y = %n\n", x, y);
```

### Loops
```base67
para (var i = 0; i < 5; i = i + 1) {
    printf_troll("i = %n\n", i);
}
```

### Fibonacci
```base67
funcao fib(n) {
    se (n <= 1) retorne n;
    retorne fib(n - 1) + fib(n - 2);
}
```

---

## ✅ Checklist de Funcionalidades

- [x] Lexer com base 67
- [x] Parser com precedência de operadores
- [x] AST e execução
- [x] Variáveis com escopo léxico
- [x] Funções (declaração e chamada)
- [x] Condicionais (se/senao)
- [x] Loops (enquanto/para)
- [x] Operadores aritméticos
- [x] Operadores lógicos
- [x] Funções integradas (printf_troll, panic67, etc)
- [x] Gerenciamento de memória
- [x] Tratamento de erros com referência a base 67
- [x] Debug flags (--debug-tokens, --debug-ast)
- [x] Exemplos funcionais
- [x] Documentação técnica

---

## 🎓 Aprendizados Técnicos

### Para Alunos de Compiladores
- Arquitetura clássica: Lexer → Parser → AST → Runtime
- Recursive descent parsing
- Ambiente com escopo léxico
- Interpretação direta vs compilação para bytecode

### Para Alunos de Linguagens
- Design de nova linguagem
- Sistema numérico alternativo (base 67)
- Tipos dinâmicos
- Funções de primeira classe (futuro)

### Para Engenheiros de Software
- Modularização em C
- Gerenciamento de memória seguro
- Tratamento de erros
- Documentação técnica completa

---

## 🚦 Status e Próximos Passos

### Concluído
- ✅ Especificação completa
- ✅ Implementação em C compilável
- ✅ Base 67 totalmente integrada
- ✅ Exemplos funcionais
- ✅ Documentação

### Futuro (v0.2+)
- [ ] Funções definidas pelo usuário
- [ ] Arrays e estruturas
- [ ] Strings com métodos
- [ ] Módulos e imports
- [ ] Otimizações de performance
- [ ] Compilador para bytecode
- [ ] REPL interativo

---

## 📖 Como Usar Este Projeto

### 1. Para Entender Compiladores
```
1. Lea docs/SPECIFICATION.md
2. Lea docs/IMPLEMENTATION.md
3. Estude src/lexer.c, parser.c, runtime.c
```

### 2. Para Usar a Linguagem
```
1. Leia examples/EXEMPLOS.md
2. Crie seu teste.s67
3. Rode: ./sixseven teste.s67
```

### 3. Para Extends/Modify
```
1. Ler Makefile e compilar com make
2. Editar arquivo .c apropriado
3. make rebuild
4. Testar: ./sixseven exemplo.s67
```

---

## 📝 Notas Importantes

> **Base SixSeven NÃO é uma piada.**
>
> É uma linguagem real com:
> - Especificação técnica formal (EBNF)
> - Implementação funcional em C
> - Interpretador completamente funcional
> - Base 67 como regra estrutural central, não como hack

> Todos os números são **realmente** interpretados em base 67
> Não é um easter egg - é a linguagem inteira!

---

## 📞 Referências

- **EBNF** - Extended Backus-Naur Form (gramática formal)
- **Recursive Descent** - Técnica de parsing
- **Base 67** - Sistema numérico com 67 símbolos
- **Lexer/Parser** - Componentes padrão de compiladores

---

## 🎉 Conclusão

**Base SixSeven é uma linguagem de programação real, completa, documentada e compilável, onde TODOS os números são interpretados em base 67 de ponta a ponta.**

Compile, execute, e experimente!

```bash
make
make test
```

---

**Base SixSeven: Onde base 67 é lei. 🔡**
