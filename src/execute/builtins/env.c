/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:39:21 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:27 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Implementation of the env builtin, with no option or argument.
 *
 * @param args Array of arguments passed to env.
 * @param minishell Struct containing global Minishell data, including the
 * 	environment variables list (`envvar_lst`).
 * @return EXIT_SUCCESS on success. EXIT_FAILURE on failure.
 * @note The quotes around args are removed during tokenization.
 */
int	do_env(char **args, t_minishell *minishell)
{
	int			exit_code;
	t_envvar	*current;

	exit_code = error_if_wrong_args(args, "env", 1);
	if (exit_code)
		return (exit_code);
	current = minishell->envvar_lst;
	while (current)
	{
		if (printf("%s=%s\n", current->name, current->value) < 0)
			return (put_error("env: printf"), EXIT_FAILURE);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
