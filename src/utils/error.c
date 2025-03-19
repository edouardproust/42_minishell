/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:39:21 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:27 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Set errno to the given value.
 *
 * @param err_no Value for errno
 * @return void
 */
void	set_errno(int err_no)
{
	if (err_no >= 0)
		errno = err_no;
}

/**
 * Writes a formatted error message to stderr using the provided arguments.
 *
 * @param fmt The format string containing '%s' placeholders.
 * @param args Array of argument strings to replace the '%s' placeholders.
 * @param arg_count Number of arguments provided in the args array.
 */
static void	put_error_with_args(char *fmt, char **args, int arg_count)
{
	int	i;
	int	arg_index;

	ft_putstr_fd("minishell: ", STDERR_FILENO);
	arg_index = 0;
	i = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%' && fmt[i + 1] == 's')
		{
			if (arg_index < arg_count && args[arg_index])
				ft_putstr_fd(args[arg_index], STDERR_FILENO);
			arg_index++;
			i++;
		}
		else
			ft_putchar_fd(fmt[i], STDERR_FILENO);
		i++;
	}
	if (errno)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}

/**
 * Prints a simple error message to stderr.
 *
 * @param err_msg The error message string to print.
 */
void	put_error(char *err_msg)
{
	if (!err_msg || !err_msg[0])
		return ;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	if (errno)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}

/**
 * Prints a formatted error message with one argument to stderr.
 *
 * @param fmt The format string containing one '%s' placeholder.
 * @param arg The argument string to replace the '%s' placeholder.
 */
void	put_error1(char *fmt, char *arg)
{
	char	*args[1];

	args[0] = arg;
	put_error_with_args(fmt, args, 1);
}

/**
 * Prints a formatted error message with two arguments to stderr.
 *
 * @param fmt The format string containing two '%s' placeholders.
 * @param arg1 The first argument string to replace the first '%s' placeholder.
 * @param arg2 The second argument string to replace the second '%s' placeholder.
 */
void	put_error2(char *fmt, char *arg1, char *arg2)
{
	char	*args[2];

	args[0] = arg1;
	args[1] = arg2;
	put_error_with_args(fmt, args, 2);
}
