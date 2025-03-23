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

static void	put_error_format(char *fmt, char **args, int arg_count)
{
	int		i;
	int		arg_index;
	char	ch[2];

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
			ch[0] = fmt[i];
			ch[1] = '\0';
			append_to_error_buffer(ch);
		}
		i++;
	}
}

/**
 * Writes a formatted error message to the error buffer using the provided
 * arguments.
 */
static void	do_put_error(char *fmt, char **args, int arg_count)
{
	static t_bool	locked = FALSE;

	while (locked)
		;
	locked = TRUE;
	append_to_error_buffer("minishell: ");
	put_error_format(fmt, args, arg_count);
	if (errno)
	{
		append_to_error_buffer(": ");
		append_to_error_buffer(strerror(errno));
	}
	append_to_error_buffer("\n");
	flush_error_buffer();
	locked = FALSE;
}

/**
 * Prints a simple error message to the error buffer.
 */
void	put_error(char *err_msg)
{
	char	*args[1];

	if (!err_msg || !err_msg[0])
		return ;
	args[0] = err_msg;
	do_put_error("%s", args, 1);
}

/**
 * Prints a formatted error message with one argument to the error buffer.
 */
void	put_error1(char *fmt, char *arg)
{
	char	*args[1];

	args[0] = arg;
	do_put_error(fmt, args, 1);
}

/**
 * Prints a formatted error message with two arguments to the error buffer.
 */
void	put_error2(char *fmt, char *arg1, char *arg2)
{
	char	*args[2];

	args[0] = arg1;
	args[1] = arg2;
	do_put_error(fmt, args, 2);
}
