# minishell

**The "Minishell" project from 42 School recreates a simple Unix shell, featuring command parsing, execution, environment management, and basic built-ins in C, showcasing expertise in system calls and Unix process control.**

- **Subject:** [English](subject/en.subject.pdf) / [Spanish](subject/es.subject.pdf)
- **Location:** 42 School Barcelona
- **Validation:** March 2025

## TODO

### Features
- Variables expansion
- Browse commands history (arrows up and down)
- Deal with non-interactive mode (in main.c)
- (optional) Bonus:
	- && and || with parenthesis for priorities
	- Wildcards * should work for the current working directory.

### Fix
- `$ export ""`, should print: ``minishell: export: `': not a valid identifier`` + exit_code 1
- `$ cd <directory>` should update `PWD` and `OLDPWD` env. vars
- `add_history` add leaks? (Did i forget a `rl_clear_history` somewhere?)
- Don't print `exit` in this case: `$ sleep 3000 | exit`
- Deal with more than 1 outfile or infile in a t_cmd (eg. `$ echo hello > out1 >> out2`)
- Run ./minishell inside ./minishell
- (optional) "Zombie-process" architecture

### Final checks
- Remove any `.bak` file, `debug.c` and `debug.h` + clean all reference to them in the code
- Memory leaks (in all case senarios)
- Fds leaks (in all case senarios)
- exit codes (in all case senarios)
- error messages (in all case senarios)
- Search for any "TODO" and "DEBUG" and fix / remove them
- Do a .gitignore file that excludes `test/`, `.gitguardian.yaml`, etc.

## How to use?

// TODO

## Overview

**Features:**
	
- Display a prompt when waiting for a new command.
- Have a working history.
- Execute commands with arguments.
- Handle environment variables ($ followed by a sequence of characters).
- Manage signals (Ctrl+C, Ctrl+D, Ctrl+\).
- Redirections (>, <, <<, >>).
- Pipes (|).
- Built-ins (echo, cd, export, unset, env, exit).

## Requirements

### Allowed functions:
					
**Readline Library Functions**
- `readline(prompt)`: Displays a prompt (e.g., minishell> ) and waits for user input. Returns the input string (dynamically allocated).
- `rl_clear_history()`: Clears the history of commands entered via readline.
- `rl_on_new_line()`: Notifies the readline library that the cursor is on a new line (used after signals like CTRL+C).
- `rl_replace_line(new_line, clear_undo)`: Replaces the current input line with new_line. The clear_undo parameter specifies whether to reset undo history.
- `rl_redisplay()`: Refreshes and redraws the current line in the terminal.
- `add_history(line)`: Adds the given line to the command history.

**Standard C Library Functions**
- `malloc(size)`: Allocates size bytes of memory and returns a pointer to it.
- `free(ptr)`: Frees memory previously allocated with malloc.
- `write(fd, buffer, count)`: Writes count bytes from buffer to the file descriptor fd.

**File and Directory Management**
- `access(path, mode)`: Checks if the path exists and if the program has the specified mode (e.g., read/write).
- `open(path, flags)`: Opens a file at path with the specified flags (e.g., O_RDONLY for read-only).
- `read(fd, buffer, count)`: Reads up to count bytes from file descriptor fd into buffer.
- `close(fd)`: Closes the file descriptor fd.

**Process Management**
- `fork()`: Creates a new process by duplicating the current one (parent and child).
- `wait(status)`: Waits for any child process to finish and stores its exit status.
- `waitpid(pid, status, options)`: Waits for a specific child process (pid) to finish.
- `wait3(status, options, usage)`: Like wait, but also returns resource usage.
- `wait4(pid, status, options, usage)`: Like waitpid, but also returns resource usage.

**Signal Handling**
- `signal(signum, handler)`: Sets a handler function for the signal signum.
- `sigaction(signum, act, oldact)`: Sets signal behavior with more options than signal.
- `sigemptyset(set)`: Initializes a signal set to be empty.
- `sigaddset(set, signum)`: Adds a signal signum to the set.
- `kill(pid, sig)`: Sends the signal sig to the process with ID pid.

**Exit and Environment**
- `exit(status)`: Terminates the current process with the given status.
- `getcwd(buffer, size)`: Gets the current working directory and stores it in buffer.
- `chdir(path)`: Changes the current working directory to path.

**File Information**
- `stat(path, buf)`: Retrieves information about a file or directory (buf).
- `lstat(path, buf)`: Like stat, but retrieves info about symbolic links instead of the target file.
- `fstat(fd, buf)`: Like stat, but works with an open file descriptor fd.

**File Operations**
- `unlink(path)`: Deletes a file or symbolic link at path.
- `execve(path, argv, envp)`: Replaces the current process with a new program specified by path.

**I/O and Piping**
- `dup(fd)`: Duplicates a file descriptor fd.
- `dup2(oldfd, newfd)`: Duplicates oldfd to newfd, closing newfd first if necessary.
- `pipe(fds)`: Creates a pipe (a pair of file descriptors for inter-process communication).

**Directory Operations**
- `opendir(path)`: Opens a directory stream for the directory at path.
- `readdir(dir)`: Reads the next entry in the directory stream dir.
- `closedir(dir)`: Closes the directory stream dir.

**Error Handling**
- `strerror(errno)`: Returns a string describing the error corresponding to errno.
- `perror(message)`: Prints a custom message followed by the last error.

**Terminal Handling**
- `isatty(fd)`: Checks if the file descriptor fd refers to a terminal.
- `ttyname(fd)`: Returns the name of the terminal associated with fd.
- `ttyslot()`: Returns the slot number of the terminal in /etc/ttys.
- `ioctl(fd, request, ...)`: Sends a control request to the terminal or device fd.

**Environment Variables**
- `getenv(name)`: Returns the value of the environment variable name.

**Terminal Capabilities (Termcap)**
- `tcsetattr(fd, termios)`: Sets terminal attributes for fd.
- `tcgetattr(fd, termios)`: Gets terminal attributes for fd.
- `tgetent(buffer, termtype)`: Loads terminal capabilities for termtype.
- `tgetflag(capname)`: Checks if a terminal capability (capname) is available.
- `tgetnum(capname)`: Gets the numeric value of a terminal capability (capname).
- `tgetstr(capname, buffer)`: Gets the string value of a terminal capability (capname).
- `tgoto(capname, col, row)`: Computes a cursor movement string to position (col, row).
- `tputs(string, affcnt, putc)`: Outputs a terminal capability string (string) with the given number of affected lines (affcnt). Behaviour : Should match Bash as close as possible.

## Features/Implementation Details
				
**Command Execution**

    How execve is used to run commands.
    Handling paths and PATH variable.
    Error handling for invalid commands.

**Pipes (|)**

    How pipes connect the output of one command to the input of another.
    Use of pipe() and dup2().

**Redirections (>, <, >>)**

    File handling with open(), dup2(), and close().
    Managing multiple redirections in a single command.

**Signals**

    How signals like Ctrl+C (SIGINT) and Ctrl+D (EOF) are managed.

**Environment Variables**

    Using getenv to handle environment variables.
    Built-ins like export and unset.

**Built-in Commands**

Details of the implementation of each built-in:

    cd, echo, exit, export, unset, etc.
    
## Error Handling

// TODO: Description of how errors are handled. Mention where and how error messages are displayed.

## External references:

- https://medium.com/@WinnieNgina/guide-to-code-a-simple-shell-in-c-bd4a3a4c41cd
- https://www.rozmichelle.com/pipes-forks-dups/
- https://medium.com/@mostafa.omrane/mes-conseils-si-je-devais-recommencer-minishell-a9783c51ba1b
