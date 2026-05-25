*This project has been created as part of the 42 curriculum by gusilva.*

# Minishell

## Description

Minishell is a simple Unix shell written in C — a small reimplementation
of the core features of `bash`. It reads command lines from the user,
parses them, handles quoting and environment-variable expansion, sets up
redirections and pipelines, and finally launches the requested programs
through `fork`/`execve`. Built-in commands (`cd`, `echo`, `env`,
`export`, `exit`, `pwd`, `unset`) are implemented directly in the shell.

The goal of the project is to gain a deep, practical understanding of:

- How a shell parses and tokenizes input
- How processes are created, chained with pipes, and reaped
- How standard input/output are redirected via `dup2`
- How signals (SIGINT, SIGQUIT, EOF) integrate with an interactive program
- How environment variables are stored and propagated to child processes
- Memory management in a long-running, user-driven program

### Features

- Interactive prompt with **command history** (via `readline`)
- Execution of binaries found in `PATH`, or via relative/absolute path
- **Single quotes** `'...'` — no expansion inside
- **Double quotes** `"..."` — variable expansion (`$VAR`, `$?`) but no
  word splitting
- **Redirections**: `<`, `>`, `>>`, and **heredoc** `<<` (with
  expansion when the delimiter is unquoted)
- **Pipelines** of arbitrary length with `|`
- **Environment variable expansion**: `$VAR`, `$?`
- **Signals** behave like `bash`:
  - `Ctrl-C`: new prompt on a new line
  - `Ctrl-D`: exits the shell
  - `Ctrl-\`: ignored at the prompt; default behavior in a child
- **Built-ins**: `echo` (with `-n`), `cd` (relative/absolute, `-`, `HOME`),
  `pwd`, `export`, `unset`, `env`, `exit` (with proper numeric arg
  validation and overflow detection)
- Per-subject: unclosed quotes are rejected with a syntax error;
  unrequired special characters (`\`, `;`) are not interpreted

## Instructions

### Requirements

- A POSIX-compatible system (developed and tested on Linux / WSL Ubuntu)
- `gcc` or `cc`
- `make`
- `libreadline` development headers

On Debian / Ubuntu / WSL you can install everything with:

```bash
sudo apt update
sudo apt install -y build-essential libreadline-dev
```

### Clone

```bash
git clone https://github.com/<your-github-username>/minishell.git
cd minishell
```

### Build

From the project root:

```bash
make
```

This compiles every source file with `cc -Wall -Wextra -Werror -I includes`,
places the object files into `obj/`, links them with `-lreadline`,
and produces the executable `./minishell`.

The build supports incremental compilation: running `make` again when
nothing has changed will print `make: Nothing to be done for 'all'.`

Other Makefile rules:

```bash
make clean    # remove object files (obj/)
make fclean   # remove object files AND the minishell binary
make re       # equivalent to: make fclean && make
```

### Run

```bash
./minishell
```

You will get a `minishell$ ` prompt. Interact with it as you would
with `bash` — try the following to confirm everything works:

```bash
minishell$ echo hello world
minishell$ pwd
minishell$ env | grep PATH
minishell$ echo "user is $USER"
minishell$ ls -l | grep minishell | wc -l
minishell$ echo failing > /tmp/test && cat < /tmp/test
minishell$ cat << EOF
> heredoc line
> EOF
minishell$ false
minishell$ echo $?
1
minishell$ export GREETING=hi
minishell$ echo $GREETING
hi
minishell$ unset GREETING
minishell$ exit
```

Press `Ctrl-C` at any time to abort the current line and get a fresh
prompt. Press `Ctrl-D` on an empty line (or type `exit`) to quit.

### Project layout

```
minishell/
├── Makefile
├── README.md
├── includes/
│   └── minishell.h
└── src/
    ├── main.c
    ├── init_shell.c
    ├── 1.lexer/           # tokenizer
    ├── 2.Syntax_check/    # syntax validation
    ├── 3.Expansion/       # $VAR / $? expansion, quote stripping
    ├── 4. Parser/         # token list → command list
    ├── 5. Heredoc/        # << handling (forked, signal-safe)
    ├── 6. Execution/      # fork/exec, pipes, redirections, PATH lookup
    ├── 7. Free/           # memory cleanup
    ├── builtins/          # echo, cd, pwd, env, export, unset, exit
    ├── read/              # get_next_line (non-interactive input)
    ├── signals/           # SIGINT, SIGQUIT, EOF handling
    └── utils/             # string helpers, malloc-friendly utilities
```

The pipeline is straightforward:

```
input → tokenize → validate → expand → parse → execute → cleanup
```

## Resources

### Documentation and references

- `bash` reference manual — https://www.gnu.org/software/bash/manual/
- GNU `readline` documentation —
  https://tiswww.case.edu/php/chet/readline/readline.html
- POSIX.1-2017 — the man pages for `fork`, `execve`, `pipe`, `dup2`,
  `waitpid`, `signal`, `sigaction`
- "Advanced Programming in the Unix Environment" by W. Richard Stevens
  (process control and signals chapters)
- `man 7 signal-safety` — for safe operations inside signal handlers

### Use of AI

AI tooling (Claude, via Claude Code) was used as a focused assistant
**after** an initial working implementation was already written.
Specifically:

- **Code review and refactoring** — identifying dead code, stale
  prototypes in the header, and duplicated free paths; consolidating
  them.
- **42 Norm compliance** — splitting long functions (e.g. `main`,
  `execute_pipe`, `builtin_cd`, `parser`, `get_cmd_path`) so each
  function fits within 25 lines, no function exceeds 4 parameters,
  and no file exceeds 5 functions; flagging lines over 80 columns.
- **Forbidden function audit** — locating and replacing calls to libc
  functions that are not in the subject's allowed list (`atoi`,
  `strlen`, `fflush`), and replacing them with project equivalents
  (`parse_exit_arg` with overflow detection, `ft_strlen`,
  `write`-based output paths).
- **Bug fixes** — pinpointing a stdout-buffering issue that caused
  doubled output after `fork`, and proposing the `write()`-based fix
  for builtins so that no buffer flush is needed in the parent before
  forking; improving `exit` to match `bash` semantics for non-numeric
  arguments, "too many arguments", and overflow.
- **Makefile design** — drafting a Makefile that handles directory
  names containing spaces (using `vpath` for unproblematic directories
  and explicit rules with quoted paths for the others), produces
  objects in a flat `obj/` directory, and avoids relinking.
- **Behavioral verification** — designing regression scripts to compare
  outputs against `bash` for redirections, pipes, quote handling, `$?`
  propagation, and exit-code semantics.

All AI-generated suggestions were reviewed, tested, and edited before
being committed. No part of this project was accepted blindly: every
function I keep is one I can explain and defend during evaluation.
