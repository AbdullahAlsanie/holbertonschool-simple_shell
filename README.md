# Simple Shell

A simple UNIX command line interpreter.

## Description

This is a simple shell program that can execute commands just like a regular shell. It was created as part of a system programming project to understand how shells work.

## How to compile

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## How to use

### Interactive mode
```bash
$ ./hsh
($) ls
file1 file2 file3
($) pwd
/home/user
($) exit
$
```

### Non-interactive mode
```bash
$ echo "ls" | ./hsh
file1 file2 file3
$
```

## What it can do

- Execute commands like `ls`, `pwd`, `cat`, etc.
- Handle commands with arguments: `ls -l`, `cat file.txt`
- Find programs using the PATH environment variable
- Built-in commands: `exit` and `env`
- Handle errors when commands don't exist

## Built-in commands

- `exit` - Exit the shell
- `env` - Print environment variables

## Examples

```bash
$ ./hsh
($) ls -l
total 8
-rw-r--r-- 1 user user 1234 Dec  5 10:00 file.txt
($) cat file.txt
Hello World
($) env
PATH=/usr/bin:/bin
HOME=/home/user
($) nonexistent
./hsh: 1: nonexistent: not found
($) exit
$
```

## Files

- `shell.c` - Main program
- `shell.h` - Header file
- `shell_func.c` - Shell utility functions
- `print_env.c` - Built-in env command
- `find_path.c` - PATH handling and resolution
- `execute.c` - Command execution functions
- `README.md` - This file
- `AUTHORS` - List of contributors

## Authors

[See AUTHORS file.](AUTHORS)
