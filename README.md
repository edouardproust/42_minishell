# minishell

**The "Minishell" project from 42 School recreates a simple Unix shell, featuring command parsing, execution, environment management, and basic built-ins in C, showcasing expertise in system calls and Unix process control.**

- **Subject:** [English](subject/en.subject.pdf) / [Spanish](subject/es.subject.pdf)
- **Location:** 42 School Barcelona
- **Validation:** March 2025

## How to use?

// TODO

## Overview

**Features:**
	
	Display a prompt when waiting for a new command.
	Have a working history.
	Execute commands with arguments.
	Handle environment variables ($ followed by a sequence of characters).
	Manage signals (Ctrl+C, Ctrl+D, Ctrl+\).
	Redirections (>, <, <<, >>).
	Pipes (|).
	Built-ins (echo, cd, export, unset, env, exit).

**Collaborative notes:**
    (eg how the collaborating will be, who handles which feature)

## Requirements
					
**Mandatory:**
    Allowed functions : ~/minishell/functions
    Behaviour : Should match Bash as close as possible
**Bonus:**
    && and || with parenthesis for priorities
    Wildcards * should work for the current working directory.

## Architecture

**Modules (eg module names)**

    -main.c -> Entry point.
    -parser.c -> Tokenize and parses input commands.
    -executor.c -> Executes commands and handles built-ins.
    -redirections.c -> Manages I/O redirections.
    -signals.c -> Handles signal management.

**Data structures:** 

    Here we can describe key data structures  (e.g., a structure for the command tree, a linked list  for tokens).

Flow Diagram about how input will move through:
    **Input -> Lexer -> Parser -> Executor -> Output

## Functions
					
    Name: Function name.
    Purpose: Brief description of what it does.
    Input/Output: Parameters and return values.
    Example: Usage example if applicable.
    Key Notes: Caveats or special handling.

## Features/Implementation Details
				
**Command Execution

    How execve is used to run commands.
    Handling paths and PATH variable.
    Error handling for invalid commands.

Pipes (|)

    How pipes connect the output of one command to the input of another.
    Use of pipe() and dup2().

Redirections (>, <, >>)

    File handling with open(), dup2(), and close().
    Managing multiple redirections in a single command.

Signals

    How signals like Ctrl+C (SIGINT) and Ctrl+D (EOF) are managed.

Environment Variables

    Using getenv to handle environment variables.
    Built-ins like export and unset.

Built-in Commands

Details of the implementation of each built-in:

    cd, echo, exit, export, unset, etc.
    
## Error Handling
				
Description of how errors are handled.
Mention where and how error messages are displayed.

## Testing
					
Test Plan :

    Single commands.
    Multiple commands with pipes.
    Edge cases (empty commands, invalid paths).
    Signals and redirections.

Manual Testing: Commands to test in minishell and expected behaviour.
*Automated Testing: Mention in case we use scripts.

## External references:

https://medium.com/@WinnieNgina/guide-to-code-a-simple-shell-in-c-bd4a3a4c41cd
https://www.rozmichelle.com/pipes-forks-dups/
