#include "minishell.h"

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
	exit(exit_code % 256);
}
