/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:39:21 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:27 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Print in stdout the list of export environment variables
 * for the command `export`.
 *
 * @param lst Head node of t_envvar list
 * @return FAILURE if printf fails. EXIT_SUCCESS otherwise.
 */
static int	put_export_vars(t_envvar *lst)
{
	while (lst)
	{
		if (printf("export %s=\"%s\"\n", lst->name, lst->value) < 0)
			return (put_error("export: printf"), EXIT_FAILURE);
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}

static void	export_envvar(t_envvar *envvar, t_minishell *minishell)
{
	t_envvar	*found_node;

	found_node = envvar_findbyname(minishell->envvar_lst, envvar->name);
	if (found_node)
	{
		if (envvar_updateone(found_node, envvar->value) != EXIT_SUCCESS)
			return (put_error("export"));
		free_envvar_node(&envvar);
	}
	else
		envvar_addoneback(&minishell->envvar_lst, envvar);
}

/**
 * Implementation of the export builtin, with no options.
 *
 * @param args Array of arguments passed to export.
 * @param ms Struct containing global Minishell data, including the
 * 	environment variables list (`envvar_lst`) and the environment array
 * (`envp`).
 * @return EXIT_SUCCESS on success. EXIT_FAILURE on failure.
 * @note The quotes around args are removed during tokenization.
 */
int	do_export(char **args, t_minishell *ms)
{
	int			exit_code;
	t_envvar	*envvar;
	int			i;

	exit_code = error_if_options(args, "export");
	if (exit_code)
		return (exit_code);
	if (ft_matrix_size(args) == 1)
		return (put_export_vars(ms->envvar_lst));
	exit_code = EXIT_SUCCESS;
	i = -1;
	while (args[++i])
	{
		envvar = envvar_new(args[i]);
		if (!envvar)
			return (put_error("export"), EXIT_FAILURE);
		if (!is_valid_envp_var(envvar->name))
		{
			put_error1("export: `%s': not a valid identifier", envvar->name);
			exit_code = (free_envvar_node(&envvar), EXIT_FAILURE);
		}
		else
			export_envvar(envvar, ms);
	}
	return (update_envp(ms) | exit_code);
}
