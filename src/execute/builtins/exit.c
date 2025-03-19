/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:39:21 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:27 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Check if the string is a valid number.
 */
static t_bool	is_valid_number(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

/**
 * Implementation of the exit builtin, with no option.
 * 
 * @param args Array of arguments passed to exit.
 * @param minishell Struct containing global Minishell data.
 * @return EXIT_SUCCESS on success. EXIT_FAILURE on failure.
 * @note The quotes around args are removed during tokenization.
 * 	check at school: minishell->exit_code or EXIT_SUCCESS ?
 */
int	do_exit(char **args, t_minishell *minishell)
{
	size_t	arg_count;
	int		exit_code;

	printf("exit\n");
	arg_count = ft_matrix_size(args);
	if (arg_count == 1)
		exit_code = minishell->exit_code;
	else
	{
		if (!is_valid_number(args[1]))
		{
			exit_code = E_CMDWRONGARG;
			put_error1("exit: %s: numeric argument required", args[1]);
		}
		else if (arg_count > 2)
			return (put_error("exit: too many arguments"), EXIT_FAILURE);
		else
			exit_code = ft_atoi(args[1]);
	}
	exit_minishell(exit_code, minishell, NULL);
	return (EXIT_SUCCESS);
}
