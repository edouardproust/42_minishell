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
 * Writes a formatted error message to the error buffer using the provided
 * arguments.
 */
static void	put_error_with_args(char *fmt, char **args, int arg_count)
{
	int		i;
	int		arg_index;
	char	c;

	append_to_error_buffer("minishell: ");
	i = 0;
	arg_index = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%' && fmt[i + 1] == 's')
		{
			if (arg_index < arg_count && args[arg_index])
				append_to_error_buffer(args[arg_index]);
			arg_index++;
			i++;
		}
		else
		{
			c = fmt[i];
			append_to_error_buffer(&c);
		}
		i++;
	}
	if (errno)
	{
		append_to_error_buffer(": ");
		append_to_error_buffer(strerror(errno));
	}
	append_to_error_buffer("\n");
	flush_error_buffer();
}

/**
 * Prints a simple error message to the error buffer.
 */
void	put_error(char *err_msg)
{
	if (!err_msg || !err_msg[0])
		return ;
	append_to_error_buffer("minishell: ");
	append_to_error_buffer(err_msg);
	if (errno)
	{
		append_to_error_buffer(": ");
		append_to_error_buffer(strerror(errno));
	}
	append_to_error_buffer("\n");
	flush_error_buffer();
}

/**
 * Prints a formatted error message with one argument to the error buffer.
 */
void	put_error1(char *fmt, char *arg)
{
	char	*args[1];

	args[0] = arg;
	put_error_with_args(fmt, args, 1);
}

/**
 * Prints a formatted error message with two arguments to the error buffer.
 */
void	put_error2(char *fmt, char *arg1, char *arg2)
{
	char	*args[2];

	args[0] = arg1;
	args[1] = arg2;
	put_error_with_args(fmt, args, 2);
}
