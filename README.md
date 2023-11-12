# 0x16. C - Simple Shell

**Project Name:** 0x16. C - Simple Shell

**Project Manipulated and Analyzed by:**
By: **Julien Barbier**

**Project Team:**
- **Zerihun Shiferaw**

## General

### Learning Objectives
- Learn who designed and implemented the original Unix operating system.
- Discover who wrote the first version of the UNIX shell.
- Understand who invented the B programming language (the direct predecessor to the C programming language).
- Get to know Ken Thompson.
- Gain knowledge about how a shell works.
- Understand what a PID and a PPID are.
- Learn how to manipulate the environment of the current process.
- Differentiate between a function and a system call.
- Discover how to create processes.
- Understand the three prototypes of the `main` function.
- Learn how the shell uses the PATH to find programs.
- Discover how to execute another program with the `execve` system call.
- Learn how to suspend the execution of a process until one of its children terminates.
- Understand what EOF (end-of-file) is.

## Requirements

### General
- Allowed editors: vi, vim, emacs.
- All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89.
- All your files should end with a new line.
- A `README.md` file, at the root of the folder of the project, is mandatory.
- Your code should use the Betty style. It will be checked using `betty-style.pl` and `betty-doc.pl`.
- Your shell should not have any memory leaks.
- No more than 5 functions per file.
- All your header files should be include guarded.
- Use system calls only when you need to (why?).
- Write a README with the description of your project.
- You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository (see Docker).

### GitHub
- There should be one project repository per group. If you and your partner have a repository with the same name in both your accounts, you risk a 0% score. Add your partner as a collaborator.

## Output
Unless specified otherwise, your program must have the exact same output as `sh` (`/bin/sh`) as well as the exact same error output. The only difference is when you print an error, the name of the program must be equivalent to your `argv[0]`.

### Example of error with `sh`:
```
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
```

### Same error with your program `hsh`:
```
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
```

---
### List of allowed Functions in the **Table**



| Left Side                                  | Right Side                                   |
|-------------------------------------------|---------------------------------------------|
| access (man 2 access)                     | execve (man 2 execve)                       |
| chdir (man 2 chdir)                       | exit (man 3 exit)                            |
| close (man 2 close)                       | _exit (man 2 _exit)                          |
| closedir (man 3 closedir)                 | fflush (man 3 fflush)                        |
| fork (man 2 fork)                         | free (man 3 free)                            |
| getcwd (man 3 getcwd)                     | getline (man 3 getline)                      |
| getpid (man 2 getpid)                     | isatty (man 3 isatty)                        |
| kill (man 2 kill)                         | malloc (man 3 malloc)                        |
| open (man 2 open)                         | opendir (man 3 opendir)                      |
| perror (man 3 perror)                     | read (man 2 read)                            |
| readdir (man 3 readdir)                   | signal (man 2 signal)                        |
| stat (__xstat) (man 2 stat)               | lstat (__lxstat) (man 2 lstat)                |
| fstat (__fxstat) (man 2 fstat)            | strtok (man 3 strtok)                        |
| wait (man 2 wait)                         | waitpid (man 2 waitpid)                      |
| wait3 (man 2 wait3)                       | wait4 (man 2 wait4)                          |
| write (man 2 write)                       |                                            |



## The of shell work
- **pwd:** This command prints the current working directory of the shell

- **cp:** This command copies files or directories1

- **echo:** This command prints a message or a variable value to the standard output

- **LS:**  List all content of directory
## Acknowledgment
I, highly thank `ALX_Software` Engineering Company, the creator of **BETTY** Linter for C programming, for their invaluable contribution to the programming community. I also extend my gratitude to the pioneers of C programming and C language standard libraries, who laid the foundation for the world of programming.



