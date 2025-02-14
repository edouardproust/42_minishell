#include "minishell.h"

/**
 * Check that the exit code is correct and exit the program.
 */
static void	exit_with_code(int exit_code)
{
	if (exit_code > E_ERRMAX)
		exit_code = E_ERRMAX;
	exit(exit_code);
}

/**
 * Exit safely the program at any point of its execution.
 * - print an error message
 * - free all the allocated memory
 * - exit the program with the given
 */
void	exit_minishell(int exit_code, t_minishell **minishell, char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	put_error_va(fmt, args);
	free_minishell(minishell);
	exit_with_code(exit_code);
}