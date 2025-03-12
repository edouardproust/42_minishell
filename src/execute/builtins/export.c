#include "minishell.h"

/**
 * Print in stdout the list of export environment variables
 * for the command `export`.
 *
 * @param lst Head node of t_envvar list
 * @return FAILURE if ft_printf fails. EXIT_SUCCESS otherwise.
 */
static int	put_export_vars(t_envvar *lst)
{
	while (lst)
	{
		if (ft_printf("export %s=\"%s\"\n", lst->name, lst->value) < 0)
			return (put_error("export: ft_printf"), EXIT_FAILURE);
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
	t_envvar	*envvar;
	int			i;
	int			exit_code;

	if (error_if_options(args, "export"))
		return (EXIT_FAILURE);
	if (ft_matrix_size(args) == 1)
		return (put_export_vars(ms->envvar_lst));
	exit_code = EXIT_SUCCESS;
	i = 1;
	while (args[i])
	{
		envvar = envvar_new(args[i]);
		if (!envvar)
			return (put_error("export"), EXIT_FAILURE);
		if (!is_valid_envp_var(envvar->name))
		{
			put_error("export: `%s': not a valid identifier", envvar->name);
			exit_code = EXIT_FAILURE;
			free_envvar_node(&envvar);
		}
		else
			export_envvar(envvar, ms);
		i++;
	}
	return (update_envp(ms) | exit_code);
}
