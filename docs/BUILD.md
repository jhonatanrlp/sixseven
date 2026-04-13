# Base SixSeven - Instruções de Construção e Instalação

**Versão: 1.0**

---

## 1. Requisitos do Sistema

### Linux/macOS
- GCC ou Clang C99-compatible
- Make (opcional, mas recomendado)
- ~50MB disco (incluindo exemplos e documentação)

### Windows
- MinGW ou MSVC
- Make para Windows ou usar comandos diretos
- ~50MB disco

---

## 2. Compilação Rápida

### Opção 1: Usando Makefile (Recomendado)

```bash
cd sixseven
make
```

Isso:
1. Compila todos os módulos C
2. Liga em executável `sixseven`
3. Exibe mensagem de sucesso

Para testes, use:
```bash
make test
```

### Opção 2: Compilação Manual

Linux/macOS:
```bash
gcc -Wall -Wextra -std=c99 -O2 -o sixseven \
    src/main.c src/base67.c src/lexer.c src/parser.c \
    src/ast.c src/runtime.c src/memory.c src/value.c \
    src/builtins.c -lm
```

Windows (MinGW):
```bash
gcc -Wall -Wextra -std=c99 -O2 -o sixseven.exe ^
    src/main.c src/base67.c src/lexer.c src/parser.c ^
    src/ast.c src/runtime.c src/memory.c src/value.c ^
    src/builtins.c -lm
```

---

## 3. Estrutura do Projeto

```
sixseven/
├── README.md                  # Visão geral da linguagem
├── Makefile                   # Script de compilação
├── src/                       # Código-fonte C
│   ├── main.c                # Ponto de entrada
│   ├── base67.c/h            # Conversão base 67
│   ├── lexer.c/h             # Tokenizador
│   ├── parser.c/h            # Analisador sintático
│   ├── ast.c/h               # Árvore de sintaxe
│   ├── runtime.c/h           # Interpretador
│   ├── value.c/h             # Tipo genérico
│   ├── builtins.c/h          # Funções integradas
│   └── memory.c/h            # Gerenciamento de mem
├── examples/                 # Exemplos de programas
│   ├── EXEMPLOS.md           # Documentação de exemplos
│   ├── hello_world.s67
│   ├── aritmetica.s67
│   └── loops.s67
├── docs/                     # Documentação técnica
│   ├── SPECIFICATION.md      # Especificação da linguagem
│   ├── IMPLEMENTATION.md     # Detalhes de implementação
│   └── BUILD.md              # Este arquivo
└── tests/                    # Testes (futuro)
```

---

## 4. Primeiros Passos

### Passo 1: Clonar ou Extrair

```bash
cd sixseven
ls  # Verificar estrutura
```

### Passo 2: Compilar

```bash
make
```

Saída esperada:
```
Compilando src/base67.c...
Compilando src/lexer.c...
Compilando src/parser.c...
Compilando src/ast.c...
Compilando src/runtime.c...
Compilando src/memory.c...
Compilando src/value.c...
Compilando src/builtins.c...
Compilando src/main.c...
Linkando ./sixseven...
✓ Compilação concluída com sucesso!

Executar exemplos:
  ./sixseven examples/hello_world.s67
  ./sixseven examples/aritmetica.s67
  ./sixseven examples/loops.s67
```

### Passo 3: Testar

```bash
./sixseven examples/hello_world.s67
```

Saída esperada:
```
╔════════════════════════════════════════════════════════════╗
║         Base SixSeven - Interpretador v0.1.0              ║
║        Linguagem Real com Aritmética em Base 67           ║
╚════════════════════════════════════════════════════════════╝

Arquivo: examples/hello_world.s67
Tamanho: XX bytes

Fase 1: Tokenização (Base 67)...
✓ XX tokens gerados

Fase 2: Análise Sintática (EBNF)...
✓ AST gerada com sucesso

Fase 3: Interpretação (Base 67)...
════════════════════════════════════════════════════════════

Olá, Base SixSeven!
haha67

════════════════════════════════════════════════════════════
✓ Interpretação concluída com sucesso

Base SixSeven usa base 67 de ponta a ponta.
```

---

## 5. Uso do Interpretador

### Sintaxe Básica

```bash
./sixseven <arquivo.s67> [opções]
```

### Opções de Debug

```bash
./sixseven programa.s67 --debug-tokens  # Mostra tokens
./sixseven programa.s67 --debug-ast     # Mostra AST
```

### Exemplo: Debug

```bash
./sixseven examples/hello_world.s67 --debug-tokens
```

Saída parcial:
```
=== TOKENS ===
[0] FUNCAO: 'funcao' (linha 1, coluna 1)
[1] IDENT: 'main' (linha 1, coluna 8)
[2] LPAREN: '(' (linha 1, coluna 12)
...
```

---

## 6. Criando Seus Próprios Programas

### Passo 1: Criar Arquivo

```bash
cat > meu_programa.s67 << 'EOF'
funcao main() {
    var x = 5;
    printf_troll("Resultado: %n\n", x);
}

main();
EOF
```

### Passo 2: Executar

```bash
./sixseven meu_programa.s67
```

---

## 7. Troubleshooting

### Problema: "command not found: gcc"

**Solução (Ubuntu/Debian):**
```bash
sudo apt-get install build-essential
```

**Solução (macOS):**
```bash
xcode-select --install
```

**Solução (Windows):**
- Instale MinGW de http://www.mingw.org/
- Adicione `C:\MinGW\bin` ao PATH

### Problema: "Arquivo não encontrado"

**Verificar:**
```bash
ls -la sixseven  # Verificar se executável existe
ls -la examples/ # Verificar se exemplos existem
```

### Problema: Erro de Compilação

**Ver detalhes:**
```bash
make clean
make    # Mostra erros detalhados
```

### Problema: "Permission denied"

**Solução (Linux/macOS):**
```bash
chmod +x sixseven
./sixseven examples/hello_world.s67
```

---

## 8. Limpeza

### Remover Compilados

```bash
make clean
```

### Remover Tudo (incluindo executável)

```bash
make clean
rm sixseven
```

---

## 9. Integração em Seu Sistema

### Linux

**Instalação global (opcional):**
```bash
# Copiar executável para /usr/local/bin
sudo cp sixseven /usr/local/bin/

# Agora pode usar de qualquer lugar
sixseven programa.s67
```

**Desinstalação:**
```bash
sudo rm /usr/local/bin/sixseven
```

### macOS

Mesmo que Linux acima.

### Windows

**Adicionar ao PATH:**
1. Copie `sixseven.exe` para pasta fixa, ex: `C:\Tools\`
2. Adicione `C:\Tools\` ao variável de ambiente PATH
3. Reinicie terminal

---

## 10. Desenvolvimento Futuro

### Estrutura para Compatibilidade com Mudanças

Se precisar modificar o código:

```bash
# Sempre faça backup
cp src/arquivo.c src/arquivo.c.bak

# Faça suas alterações
# ... editar ...

# Recompile
make rebuild
```

### Adicionando Novos Módulos

1. Crie `src/novo_modulo.c` e `src/novo_modulo.h`
2. Atualize `Makefile` (adicione ao SOURCES)
3. `make rebuild`

---

## 11. Performance

### Otimizações Aplicadas

- `-O2` flag de compilação (otimização moderada)
- cache-friendly data structures (arrays vs listas ligadas)
- minimal allocations no hot path

### Benchmarks

Teste com:
```bash
time ./sixseven examples/loops.s67
```

---

## 12. Validação

### Verificar Compilação Bem-Sucedida

```bash
./sixseven
# Deve mostrar uso e versão
```

### Executar Todos os Testes

```bash
make test
```

Deve rodar 3 exemplos sem erros.

---

## 13. Próximas Etapas

1. **Ler documentação:** `docs/SPECIFICATION.md`
2. **Estudar exemplos:** `examples/EXEMPLOS.md`
3. **Explorar código:** `src/*.c`
4. **Criar seus programas:** Use `.s67` extension
5. **Conhecer base 67:** Experimente com números em base 67

---

## 14. Suporte e Documentação

- **Especificação:** [SPECIFICATION.md](docs/SPECIFICATION.md)
- **Implementação:** [IMPLEMENTATION.md](docs/IMPLEMENTATION.md)
- **Exemplos:** [EXEMPLOS.md](examples/EXEMPLOS.md)
- **README:** [README.md](../README.md)

---

## 15. Conclusão

Você agora tem um interpretador **real** de **Base SixSeven** onde **todos os números são interpretados em base 67**.

Compile, execute, e explore a linguagem!

```bash
make test
```

---

**Base SixSeven: Base 67 de ponta a ponta. 🎉**
