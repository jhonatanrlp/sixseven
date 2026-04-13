# Base SixSeven - Índice de Documentação

**Versão: 1.0**  
**Status: Completo e Compilável**

---

## 📚 Guia de Leitura

### 1️⃣ Começar Aqui

**Para entender o que é Base SixSeven:**
- [README.md](../README.md) - Visão geral, motivação e características

### 2️⃣ Aprender a Linguagem

**Para aprender a programar em Base SixSeven:**
1. [SPECIFICATION.md](SPECIFICATION.md) - Sintaxe completa e semântica
2. [examples/EXEMPLOS.md](../examples/EXEMPLOS.md) - Exemplos funcionais comentados
3. [examples/*.s67](../examples/) - Código-fonte em Base SixSeven

### 3️⃣ Compilar e Rodar

**Para compilar e usar o interpretador:**
1. [BUILD.md](BUILD.md) - Instruções de compilação
2. Execute: `make test`
3. Rode seus programas: `./sixseven programa.s67`

### 4️⃣ Entender a Implementação

**Para aprender como funciona internamente:**
1. [IMPLEMENTATION.md](IMPLEMENTATION.md) - Arquitetura em C
2. [Código-fonte em src/](../src/) - Módulos principais
3. Comece por: `src/base67.c` → `src/lexer.c` → `src/parser.c` → `src/runtime.c`

### 5️⃣ Aprofundar (Dev)

**Para estender ou modificar a linguagem:**
1. Ler comentários no código
2. Executar com `--debug-tokens` e `--debug-ast`
3. Estudar módulos em ordem: base67 → lexer → parser → runtime

---

## 📂 Estrutura de Arquivos

```
sixseven/
│
├── 📄 README.md
│   └─ Visão geral, características, exemplo completo
│
├── 🔧 Makefile
│   └─ Build automation (make, make test, make clean)
│
├── 📁 src/
│   ├─ main.c              Ponto de entrada
│   ├─ base67.c/h          Sistema numérico (67 símbolos)
│   ├─ lexer.c/h           Tokenizador (converte base 67 → decimal)
│   ├─ parser.c/h          Análise sintática (EBNF)
│   ├─ ast.c/h             Árvore de sintaxe abstrata
│   ├─ runtime.c/h         Interpretador (executa AST)
│   ├─ value.c/h           Tipo genérico para valores
│   ├─ builtins.c/h        Funções integradas (meme)
│   └─ memory.c/h          Gerenciamento de memória
│
├── 📁 docs/
│   ├─ INDEX.md            Este arquivo
│   ├─ RESUMO.md           Resumo executivo
│   ├─ SPECIFICATION.md    Especificação formal (v1.0)
│   ├─ IMPLEMENTATION.md   Desenho arquitetural
│   └─ BUILD.md            Instruções de build
│
├── 📁 examples/
│   ├─ EXEMPLOS.md         Documentação de exemplos
│   ├─ hello_world.s67     Hello World simples
│   ├─ aritmetica.s67      Operações em base 67
│   ├─ loops.s67           For e while loops
│   └─ [mais exemplos...]
│
└── 📁 tests/
    └─ (framework futuro)
```

---

## 🎯 Fluxo de Aprendizado Recomendado

### 👶 Iniciante (Quero usar Base SixSeven)

```
1. Ler: README.md
2. Ler: SPECIFICATION.md (seção 3 - Especificação da Linguagem)
3. Rodar: make test
4. Explorar: examples/EXEMPLOS.md
5. Criar: Seus próprios programas .s67
```

### 👨‍💻 Desenvolvedor (Quero entender implementação)

```
1. Ler: README.md + SPECIFICATION.md
2. Ler: IMPLEMENTATION.md (arquitetura)
3. Ler: Código em order:: base67.c → lexer.c → parser.c → runtime.c
4. Rodar: make test com --debug-tokens e --debug-ast
5. Modificar: Pequenas mudanças, recompilar, testar
```

### 🔬 Pesquisador (Quero estudar compiladores)

```
1. Estude: Toda SPECIFICATION.md (inclui EBNF)
2. Estude: IMPLEMENTATION.md (escopamento, ambiente)
3. Analise: Código de parser.c (recursive descent)
4. Analise: Código de runtime.c (interpretação)
5. Experimente: Adicionar novas funcionalidades
```

---

## 🔑 Conceitos-Chave

### Base 67

| Conceito | Descrição |
|----------|-----------|
| **Alfabeto** | 0-9, a-z, A-Z, !@#$% (67 símbolos) |
| **Conversão** | B67 → Decimal via série polinomial |
| **Invariante** | Números **sempre** são base 67 |
| **Sem exceções** | Não existe fallback para base 10 |

### Arquitetura

```
Arquivo .s67 
    → LEXER (Tokenização em base 67)
    → PARSER (Análise sintática EBNF)
    → AST (Árvore de sintaxe abstrata)
    → RUNTIME (Interpretação)
    → Output (números em base 67)
```

### Modules Principais

- **base67** - Conversão B67 ↔ Decimal
- **lexer** - Tokenização com reconhecimento B67
- **parser** - Recursive descent com precedência
- **runtime** - Ambiente, escopo, execução
- **builtins** - Funções padrão (printf_troll, panic67, etc)

---

## 💻 Compilação Rápida

### Linux/macOS
```bash
cd sixseven
make           # Compila
make test      # Testa
```

### Windows (MinGW)
```bash
cd sixseven
gcc -o sixseven src/*.c -lm   # Compila
sixseven examples/hello_world.s67  # Executa
```

---

## 🧪 Testar Funcionalidades

### Teste 1: Base 67 Funciona
```bash
./sixseven examples/aritmetica.s67
# Deve mostrar: x = 5, y = 3, x + y = 8, etc
```

### Teste 2: Loops Funcionam
```bash
./sixseven examples/loops.s67
# Deve contar de 0 a 4 duas vezes
```

### Teste 3: Debug
```bash
./sixseven examples/hello_world.s67 --debug-tokens
# Deve listar tokens com conversão base 67
```

---

## 📖 Referências Rápidas

### Sintaxe Base SixSeven

```base67
# Declaração de variável (base 67)
var x = 10;        # x recebe 10 em base 67 (67 decimal)

# Função
funcao sum(a, b) {
    retorne a + b;
}

# Condicional
se (x > 5) {
    printf_troll("Maior que 5\n");
} senao {
    printf_troll("Menor ou igual a 5\n");
}

# Loop
enquanto (i < 10) {
    i = i + 1;
}

para (var j = 0; j < 5; j = j + 1) {
    printf_troll("j = %n\n", j);
}
```

### Funções Integradas

```base67
printf_troll("Valor: %n\n", valor);    # Imprime
panic67("Erro!");                        # Pânico
compile_na_sorte();                      # Aleatório
imprimir_base67(numero);                 # Print B67
converter_para_decimal(B67_valor);       # Converter
```

---

## 🚀 Próximos Passos

### Beginner
1. [x] Compilar com `make`
2. [x] Rodar exemplos `make test`
3. [x] Ler SPECIFICATION.md
4. [ ] Criar seu primeiro programa .s67
5. [ ] Explorar funções integradas

### Intermediate
1. [ ] Estudar IMPLEMENTATION.md
2. [ ] Entenda fluxo lexer → parser → runtime
3. [ ] Execute com --debug-tokens
4. [ ] Modifique um exemplo existente
5. [ ] Adicione nova função builtin

### Advanced
1. [ ] Estude código C linha por linha
2. [ ] Implemente nova feature
3. [ ] Otimize performance
4. [ ] Estenda com novos tipos
5. [ ] Compile para bytecode (futuro)

---

## 📞 FAQ Rápido

### P: "O que é Base SixSeven?"
**R:** Uma linguagem real onde **todos** os números são base 67. Não piada!

### P: "Como 10 = 67?"
**R:** `10` em base 67 = 1×67¹ + 0×67⁰ = 67 em decimal

### P: "Como compilar?"
**R:** `make` na raiz do projeto

### P: "Como rodar um programa?"
**R:** `./sixseven programa.s67`

### P: "Posso modificar a linguagem?"
**R:** Sim! Estude src/ e recompile com `make rebuild`

---

## 📚 Documentação Adicional

- [SPECIFICATION.md](SPECIFICATION.md) - 12 seções, 40+ páginas
- [IMPLEMENTATION.md](IMPLEMENTATION.md) - Arquitetura, C, optimizations
- [BUILD.md](BUILD.md) - Passo a passo de compilation
- [RESUMO.md](RESUMO.md) - Executive summary

---

## ✅ Validação

Para verificar se tudo está funcionando:

```bash
make clean          # Limpa
make                # Compila
make test           # Executa testes

# Teste manual
./sixseven examples/hello_world.s67 --debug-tokens
```

---

## 🎓 Referências Técnicas

- **EBNF Grammar** - Veja SPECIFICATION.md seção 5
- **Recursive Descent** - Veja parser.c
- **Environment/Scope** - Veja runtime.c, environment structs
- **Base 67 Conversion** - Veja base67.c

---

## 📝 Histórico de Versões

| Versão | Status | Data | Notas |
|--------|--------|------|-------|
| 0.1.0 | Alpha | 2026-04 |  Funcionalidade completa, compilável |
| 0.2.0 | Planned | TBD | User-defined functions |
| 0.3.0 | Planned | TBD | Arrays and structures |
| 1.0.0 | Planned | TBD | Release candidty |

---

## 🏁 Conclusão

**Base SixSeven é uma linguagem real, documentada, compilável e totalmente funcional baseada em base 67.**

Comece por **README.md**, depois progra para **SPECIFICATION.md**, e finalmente explored **implementation.md**.

---

**Base SixSeven: Base 67 em tudo. 🔡67**

Versão 1.0 - Documentação Índice Completa
