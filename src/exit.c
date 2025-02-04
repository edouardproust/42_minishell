#include "minishell.h"

/*
 * Prints an error in stderr.
 *
 * Output format: "minishell: <source>: <strerror(errno)>\n"
 * If 'fmt' is NULL, then nothing is printed.
 * If 'errno' is on 'Success' (code 0), it is not printed,
 * else ': ' followed by the error string is printed
 */
static void	print_error(char *fmt, va_list args)
{
	int		fdout;
	int		chars_printed;

	if (fmt != NULL && fmt[0] != '\0')
	{
		fdout = STDERR_FILENO;
		ft_fprintf(fdout, "minishell: ");
		chars_printed = ft_vfprintf(fdout, fmt, args);
		if (errno != 0)
		{
			if (chars_printed > 0)
				ft_fprintf(fdout, ": ");
			ft_fprintf(fdout, strerror(errno));
		}
		ft_fprintf(fdout, "\n");
	}
}

/* 
 * If an error occures during parsing:
 * - prints an error message
 * - frees allocated data
 * - exits the program (error code 1)
 *
 * TODO (Ava) Update function signature (foo) + add the freeing logic in the function
 */
void	exit_parsing(t_cmd **foo, char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	print_error(fmt, args);
	va_end(args);

	// Add freeing logic here
	// (add functions in free.c and in header if necessary)
	(void)foo;

	exit(EXIT_FAILURE);
}

/*
 * If an error occures during execution:
 * - prints an error message
 * - frees allocated data
 * - close any file descriptor above 2
 * - exits the program (error code 1)
 */
void	exit_exec(t_cmd **cmd_lst, char *fmt, ...)
{
	va_list	args;
	int		fd;

	va_start(args, fmt);
	print_error(fmt, args);
	va_end(args);
	free_cmd_lst(cmd_lst);
	fd = 3;
	while (fd < 1024)
		close(fd++);
	exit(EXIT_FAILURE);
}
