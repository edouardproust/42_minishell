#include "minishell.h"

/**
 * Set errno to the given value.
 */
void	set_errno(int err_no)
{
	if (err_no > 0)
		errno = err_no;
}

/**
 * Prints an error in stderr. Takes a va_list argument.
 *
 * Output format: "minishell: <source>: <strerror(errno)>\n"
 * If 'fmt' is NULL, then nothing is printed.
 * If 'errno' is on 'Success' (code 0), it is not printed,
 * else ': ' followed by the error string is printed
 */
void	put_error_va(char *fmt, va_list args)
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
	va_end(args);
}

/**
 * Print an error in stderr. Takes a variadic argument.
 */
void	put_error(char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	put_error_va(fmt, args);
}
