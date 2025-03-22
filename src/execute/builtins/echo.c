/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:39:21 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:27 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Defines if the option -n is active for this command or not.
 * Increments index of the first arg to print if the -n option is present.
 *
 * @param args Array of args (strings) of the current t_cmd
 * @param i Pointer to the args index
 * @return boolean TRUE if option -n is activated. FALSE if not.
 */
t_bool	handle_option_n(char **args, int *i)
{
	t_bool	option_n;

	option_n = FALSE;
	if (args[*i] && ft_strncmp(args[*i], "-n", 3) == 0)
	{
		option_n = TRUE;
		(*i)++;
		while (args[*i] && ft_strncmp(args[*i], "-n", 3) == 0)
			(*i)++;
	}
	return (option_n);
}

/**
 * Implementation of the echo builtin, with option -n.
 *
 * @param args Array of arguments passed to echo.
 * @param minishell (not used) Struct containing global Minishell data.
 * @return EXIT_SUCCESS on success. EXIT_FAILURE on failure.
 * @note The quotes around args are removed during tokenization.
 */
int	do_echo(char **args, t_minishell *minishell)
{
	t_bool	option_n;
	int		i;

	(void)minishell;
	i = 1;
	option_n = handle_option_n(args, &i);
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (option_n == FALSE)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
