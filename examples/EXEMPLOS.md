# SixSeven — Example Programs

> btw, all numbers in SixSeven are base 67. `10` means 67. always. forever.

---

## Quick Reference: New Syntax

| Old (boring) | New (correct) |
|-------------|---------------|
| `var`       | `idk`         |
| `function`  | `ritual`      |
| `if`        | `ngl`         |
| `else`      | `orNot`       |
| `while`     | `untilIGetTired` |
| `for`       | `doTheThing`  |
| `return`    | `YEET`        |
| `true`      | `bestie`      |
| `false`     | `betrayal`    |
| `null`      | `theVoid`     |
| `print()`   | `screamInto()` |
| `;`         | `ok?`         |
| `// comment`| `btw, comment` |

Every file MUST start with `WAKEY WAKEY`. This is not optional.

---

## Example 1: Hello World

**file: hello_world.67**

```
WAKEY WAKEY

ritual main() {
    screamInto("Hello, World!\n") ok?
    YEET theVoid ok?
}

main() ok?
```

**output:**
```
Hello, World!
haha67
```

---

## Example 2: Base 67 Numbers

All number literals are base 67:

```
WAKEY WAKEY

ritual show_numbers() {
    btw, 10 in base67 = 67 in decimal
    btw, 1a in base67 = 77 in decimal
    btw, Z  in base67 = 61 in decimal
    btw, 5  in base67 = 5  in decimal (lucky you)

    idk z = 10 ok?
    screamInto("z = %n (this is 67 in your base 10 world)\n", z) ok?
}

show_numbers() ok?
```

---

## Example 3: Arithmetic

```
WAKEY WAKEY

ritual main() {
    idk x = 5 ok?
    idk y = 3 ok?

    screamInto("x + y = %n\n", x + y) ok?
    screamInto("x * y = %n\n", x * y) ok?
    screamInto("x - y = %n\n", x - y) ok?

    YEET theVoid ok?
}

main() ok?
```

---

## Example 4: Conditionals

```
WAKEY WAKEY

ritual check(value) {
    ngl (value < 5) {
        screamInto("less than 5\n") ok?
    } orNot {
        screamInto("5 or more\n") ok?
    }
    YEET theVoid ok?
}

check(3) ok?
check(7) ok?
```

---

## Example 5: Loops

### untilIGetTired (while):

```
WAKEY WAKEY

idk i = 0 ok?
untilIGetTired (i < 5) {
    screamInto("i = %n\n", i) ok?
    i = i + 1 ok?
}
```

### doTheThing (for):

```
WAKEY WAKEY

doTheThing (idk j = 0 ok? j < 5 ok? j = j + 1) {
    screamInto("j = %n\n", j) ok?
}
```

---

## Example 6: Cursed Variables

A `cursed` variable lies to you 10% of the time. No warning. No refunds.

```
WAKEY WAKEY

cursed idk count = 0 ok?

untilIGetTired (count < 5) {
    screamInto("count is: %n\n", count) ok?
    count = count + 1 ok?
}
btw, some of those values were lies. we don't know which.
```

---

## Example 7: chaos() and vibeCheck()

```
WAKEY WAKEY

btw, chaos() does one of three things. you'll find out which.
idk x = chaos() ok?
screamInto("chaos gave us: %n\n", x) ok?

btw, vibeCheck() either crashes the program or does nothing
btw, 50/50. coin flip. farewell.
vibeCheck() ok?

screamInto("survived the vibe check.\n") ok?
```

---

## Example 8: Full Program — Factorial

```
WAKEY WAKEY

ritual factorial(n) {
    ngl (n <= 1) {
        YEET 1 ok?
    }
    YEET n * factorial(n - 1) ok?
}

ritual main() {
    btw, factorial(5) = 120 decimal = 1O in base67
    btw, (1*67 + 53 = 120, O = value 53)
    idk result = factorial(5) ok?
    screamInto("factorial(5) = %n (in base67)\n", result) ok?
    YEET theVoid ok?
}

main() ok?
```

---

## Built-in Functions Reference

| Function | What it does |
|----------|-------------|
| `screamInto(fmt, ...)` | Print with drama. `%n`=base67 number, `%s`=string, `%t`=type |
| `chaos()` | Randomly: returns number, prints message, or does nothing |
| `vibeCheck()` | 50% crash. 50% survival. no in-between. |
| `panic67(msg)` | Terminate with a dramatic banner |
| `compile_na_sorte()` | Random number 0-66 |
| `segfault_de_brincadeira()` | Fake segfault (therapeutic) |
| `converter_para_decimal(n)` | Convert base67 to decimal |
| `tamanho_em_bytes(v)` | Size of value in bytes |
| `imprimir_base67(n)` | Print number as base67 string |

---

## Running Examples

```bash
btw, compile the interpreter first:
gcc -o sixseven src/main.c src/lexer.c src/parser.c src/ast.c \
                src/runtime.c src/memory.c src/value.c \
                src/builtins.c src/base67.c -lm

btw, then run:
./sixseven examples/hello_world.67
./sixseven examples/fibonacci.67
./sixseven examples/sort.67
./sixseven examples/cursed_counter.67

btw, debug options:
./sixseven file.67 --debug-tokens
./sixseven file.67 --debug-ast
```

---

*Base 67 from start to finish. WAKEY WAKEY.*
