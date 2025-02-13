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
 * If an error occures after the env. variables list has been built:
 * - print an error message
 * - free the list of t_envvar nodes
 * - exit the program with the given exit code
 */
void	exit_envvar(int exit_code, t_envvar **envvar_lst, char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	put_error_va(fmt, args);
	free_envvar_lst(envvar_lst);
	exit_with_code(exit_code);
}

/**
 * If an error occures during execution:
 * - prints an error message
 * - free allocated data
 * - close any file descriptor above STDERR_FILENO
 * - exit the program with the given exit_code
 */
void	exit_exec(int exit_code, t_cmd **cmd_lst, char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	put_error_va(fmt, args);
	free_cmd_lst(cmd_lst);
	flush_fds();
	exit_with_code(exit_code);
}