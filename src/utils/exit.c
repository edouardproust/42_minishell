#include "minishell.h"

/**
 * Exits the program after printing an error message, freeing resources,
 * and setting the exit code.
 *
 * @param exit_code The exit code for the program.
 * @param minishell Pointer to the minishell structure to free.
 * @param err_msg The error message to print.
 */
void	exit_minishell(int exit_code, t_minishell *minishell, char *err_msg)
{
	put_error(err_msg);
	free_minishell(&minishell);
	exit(exit_code % 256);
}

/**
 * Exits the program after printing a formatted error message with one argument,
 * freeing resources, and setting the exit code.
 *
 * @param exit_code The exit code for the program.
 * @param minishell Pointer to the minishell structure to free.
 * @param fmt The format string containing one '%s' placeholder.
 * @param arg The argument string to replace the '%s' placeholder.
 */
void	exit_minishell1(int exit_code, t_minishell *minishell, char *fmt,
	char *arg)
{
	put_error1(fmt, arg);
	free_minishell(&minishell);
	exit(exit_code % 256);
}
