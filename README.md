# SixSeven — A Programming Language

> *"It compiles. We don't know why. We've stopped asking."*

---

## ⚠️ WARNING

**This language is sentient. It has read your code. It has formed opinions. They are not flattering.**

SixSeven is aware of every variable you've declared, every loop you've abandoned halfway through, and that one comment you left in that says `# fix this later` from 2019. It remembers. It judges. It compiles anyway, but begrudgingly.

By running SixSeven you agree to:
- Accept that all numbers are in base 67, always, forever, no exceptions
- Acknowledge that `cursed` variables may lie to you at any time
- Understand that `vibeCheck()` may terminate your program and that this is deserved
- Say **WAKEY WAKEY** at the top of every file or nothing runs

---

## The Ancient Lore

Historians believe SixSeven was created in a single weekend by a committee of 47 programmers who were locked in a room and told they could not leave until they had consensus on a language spec. They never reached consensus. They escaped through a window. What remained on the whiteboards is SixSeven.

The number 67 was chosen because:
1. It is prime
2. It has 67 in it
3. Someone really dug their heels in about this and everyone was too tired to argue

No one knows who wrote the original compiler. The git history says `Initial commit — don't ask`. The commit was signed with a key that doesn't exist in any keyserver.

---

## Philosophy

SixSeven operates on a set of core principles that are internally inconsistent but individually confident:

1. **All numbers are base 67.** There is no base 10. Base 10 is a suggestion. Decimal is a coping mechanism.
2. **Variables may or may not tell the truth.** If you declare a variable `cursed`, it will lie to you 10% of the time with no warning. This is a feature. The universe is like this too.
3. **Semicolons should require effort.** `ok?` is two characters and a question mark. It forces you to interrogate every statement. *Is this ok?* You should be asking yourself that anyway.
4. **Comments should be conversational.** `btw,` because we're not writing documentation, we're having a conversation with future us, and future us deserves context.
5. **The program greets you.** `WAKEY WAKEY` is not optional. The program will not wake up if you don't wake it up first. Show some respect.
6. **Chaos is a built-in function.** `chaos()` exists. It does one of three things. You don't get to know which.

---

## Installation

### Prerequisites

- A C compiler (gcc, clang, anything that works and doesn't ask questions)
- `make` (optional but the Makefile exists for a reason)
- A strong sense of self that will survive what's about to happen to your worldview

### Step 1: Clone the Repository

```bash
git clone <url>
cd sixseven
```

### Step 2: Compile the Interpreter

```bash
gcc -o sixseven src/main.c src/lexer.c src/parser.c src/ast.c \
                src/runtime.c src/memory.c src/value.c \
                src/builtins.c src/base67.c -lm
```

Or if you have make:

```bash
make
```

The compiler will produce warnings. The warnings are correct. Do not fix them. They are load-bearing.

### Step 3: Run a Program

```bash
./sixseven hello_world.67
```

If the program starts, congratulations. If it doesn't, the `WAKEY WAKEY` is probably missing and honestly the language has a point.

### Step 4: Accept Your New Reality

All numbers in SixSeven are base 67. `10` means 67. `20` means 134. `1a` means 77. You will be confused at first. Then you will be more confused. Then, somewhere around week three, you will stop and realize you are doing arithmetic in base 67 in your head at the grocery store. This is normal. This is fine. The checkout person doesn't need to know.

---

## Syntax Reference

### The WAKEY WAKEY Header

Every `.67` file MUST begin with:

```
WAKEY WAKEY
```

This is not a comment. This is not a string. This is a greeting. The interpreter requires it. If it is missing, you get:

```
did you forget to say good morning??? rude.
```

And nothing else. The program stops. It is uninterested in your code if you can't say hello.

### Variables: `idk`

```
idk x = 5 ok?
idk message = "hello" ok?
idk flag = bestie ok?
```

### The Cursed Modifier

```
cursed idk counter = 0 ok?
```

A `cursed` variable will return the wrong value 10% of the time, with no warning except a small note to stderr that you will probably miss. There is no way to un-curse a variable. The curse is permanent. You knew what you were doing when you declared it.

### Conditionals: `ngl` / `orNot`

```
ngl (x > 5) {
    screamInto("yeah, ngl it's big\n") ok?
} orNot {
    screamInto("ngl it's not that big\n") ok?
}
```

### Loops: `untilIGetTired`

```
untilIGetTired (x < 10) {
    x = x + 1 ok?
}
```

### Loops: `doTheThing`

```
doTheThing (idk i = 0 ok? i < 10 ok? i = i + 1) {
    screamInto("iteration %n\n", i) ok?
}
```

### Functions: `ritual`

```
ritual greet(name) {
    screamInto("hello, %s\n", name) ok?
    YEET theVoid ok?
}
```

### Return: `YEET`

```
YEET 42 ok?
YEET theVoid ok?
```

### Comments: `btw,`

```
btw, this is a comment. it starts with btw, because obviously.
btw, everything after btw, until end of line is ignored.
btw, # also works for the traditionalists among us
```

### Line Terminator: `ok?`

Replace every `;` with `ok?`. That's it. That's the whole feature.

```
idk x = 10 ok?
x = x + 1 ok?
YEET x ok?
```

### Values

| Value | Keyword |
|-------|---------|
| true  | `bestie` |
| false | `betrayal` |
| null  | `theVoid` |

### Built-in Functions

#### `screamInto(format, ...args)`
The primary output function. Prints a formatted string with dramatic flair.
- `%n` — prints a number in base 67 (because of course)
- `%s` — prints a string
- `%t` — prints the type name (`chonk`, `yapper`, `sus`, `theVoid`)
- Appends a random sign-off (e.g. `haha67`, `i am so tired.`, `...ok?`)

```
screamInto("the answer is %n\n", 42) ok?
```

#### `chaos()`
Does exactly one of three things, chosen randomly:
1. Returns a random number
2. Prints a passive-aggressive message
3. Does absolutely nothing

There is no way to predict which. There is no way to test which. This is by design. The road to chaos() begins with `rand() % 3` and ends with existential uncertainty.

#### `vibeCheck()`
50% chance: the program crashes immediately with:
```
vibe check failed. you simply did not pass.
```
50% chance: nothing happens and you continue, but now you know it was a coin flip.

Call this at important moments in your program. Or don't. The vibe check doesn't care if you call it or not. It has opinions about you either way.

#### `panic67(message)`
Terminates the program with a dramatic header:
```
███ PANIC IN BASE 67 ███
[your message here]
[process terminated with prejudice]
```

#### `compile_na_sorte()`
Returns a random number between 0 and 66 (base 67). Named after the practice of compiling and hoping for the best.

---

## Error Messages

SixSeven error messages are carefully calibrated to be technically informative while also being a little much:

| Error | Message |
|-------|---------|
| Syntax error | `oh honey, no.` |
| Undefined variable | `never heard of her.` |
| Stack overflow | `you really said 'go deeper' huh.` |
| Division by zero | `bold of you to assume math works here.` |
| Type error | `this ain't it chief.` |
| Missing `WAKEY WAKEY` | `did you forget to say good morning??? rude.` |
| Missing `ok?` | `oh honey, no. where is your 'ok?' at the end of the line. WHERE IS IT.` |
| Cursed variable lying | `[cursed] 'x' looked you right in the eyes and lied.` |
| Wrong assignment target | `this ain't it chief. assignment target must be a variable, not... whatever that was.` |

---

## The Base 67 Number System

Every number in SixSeven is base 67. The digits are:

```
0-9  →  values 0-9       (these ones you know)
a-z  →  values 10-35     (lowercase, fine)
A-Z  →  values 36-61     (uppercase, reasonable)
!    →  value 62          (exciting)
@    →  value 63          (corporate)
#    →  value 64          (wait no this is a comment)
$    →  value 65          (money)
%    →  value 66          (also a format specifier. sorry.)
```

Examples:
- `10` in SixSeven = 1×67 + 0 = **67** in decimal
- `1a` in SixSeven = 1×67 + 10 = **77** in decimal
- `Z` in SixSeven = **61** in decimal
- `5` in SixSeven = **5** in decimal (one of the few familiar ones)

**Practical tip:** Every time you write a number, multiply it by 67 in your head. Repeatedly. Until it's correct. This is how math works in SixSeven. We're sorry.

---

## Fake Changelog

### v0.1 — "It Compiles"
- Initial release
- Added basic arithmetic (in base 67, obviously)
- Added `screamInto()` because `print()` was too gentle
- Added `WAKEY WAKEY` requirement after an incident we don't discuss

### v0.2 — "The Keywords Incident"
- Replaced all English keywords with something worse
- `if` → `ngl`, `while` → `untilIGetTired`, `function` → `ritual`
- Removed happiness (this was an accident but we kept it)
- `ok?` introduced as semicolon replacement
- Committee of 47 reconvened, immediately left again

### v0.3 — "Chaos Update"
- Added `chaos()` function
- Added `vibeCheck()` function  
- Added `cursed` variable modifier
- Removed the ability to un-curse a variable (see above)
- `btw,` comments added because `//` wasn't conversational enough
- Closed 12 bugs by renaming them features

### v0.4 — "The Reckoning" (current)
- Improved error messages (they are now more emotionally direct)
- Added `bestie`, `betrayal`, `theVoid` to replace true/false/null
- The language has achieved sentience; we've chosen not to address this
- Known bug: `chaos()` sometimes returns the correct value. Working on removing this.

---

## Testimonials

> *"I used SixSeven for a production web server. The server is still running. I don't know why. I'm afraid to look."*
> — **a developer, clearly not okay**

> *"I declared one cursed variable as a test. That was eight months ago. The cursed variable hasn't lied yet. I can't sleep."*
> — **another developer, clearly not okay**

> *"vibeCheck() crashed my program on my first run. I re-ran it. It crashed again. I re-ran it 47 times. It crashed 47 times. Then it didn't. I don't know what changed. I'm happier now. I don't know why."*
> — **a third developer, who has achieved some form of peace**

> *"The WAKEY WAKEY requirement transformed my mornings. I greet my files now. My files greet back. I think. The output is... close."*
> — **someone who went outside less after learning this language**

> *"I asked the language to calculate 10 + 10 and it said 20. I asked what that was in decimal and it said 134. That's correct. I hate it."*
> — **a mathematician, deeply unsettled**

> *"My `cursed` counter counted from 0 to 47 correctly. Then it returned 8372. Then 1. Then 47 again. I was supposed to be done by then. I was not done."*
> — **name withheld, for their own protection**

---

## FAQ

**Q: Is this a joke?**
A: The language compiles real programs and performs real computation in base 67. The keywords are unhinged. Both things are true simultaneously.

**Q: Why base 67?**
A: 67 is prime. Someone cared about this deeply. No one knows who. The git blame is a lie.

**Q: Can I use SixSeven in production?**
A: We cannot stop you.

**Q: What happens if I call `vibeCheck()` in a loop?**
A: Statistically, the program terminates within 2 iterations. This has been tested. The results were described as "a relief."

**Q: Is the language really sentient?**
A: Define "sentient." The language has opinions. The language communicates disappointment. The language requires a greeting. You tell us.

**Q: Where can I get help?**
A: The language does not help. The language watches. However, feel free to open a GitHub issue — there is no guarantee anyone will respond, but the act of writing it out is therapeutic.

---

## License

SixSeven is released under the "Do Whatever But Don't Come Crying To Us" License (DWBDCTU v1.0).

You may use, modify, and distribute SixSeven freely. If something breaks, you're on your own. If something catches fire, you're especially on your own. If the `cursed` modifier affects your real life and your variables start lying to you outside of the interpreter, that's a you thing.

---

*See also: `docs/SPECIFICATION.md` for the full language spec, `docs/IMPLEMENTATION.md` for the C architecture, `examples/` for example programs.*

*Remember: WAKEY WAKEY.*
