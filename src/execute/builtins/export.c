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

/**
 * Implementation of the export builtin, with no options.
 * 
 * @param args Array of arguments passed to export.
 * @param minishell Struct containing global Minishell data, including the 
 * 	environment variables list (`envvar_lst`) and the environment array (`envp`).
 * @return EXIT_SUCCESS on success. EXIT_FAILURE on failure.
 * @note The syntax of the args is checked during tokenization. //TODO:
	if (ft_isdigit(*name))
		exit_tokenizer(1, tokens, "export: `%s': not a valid identifier", name);
	while (*name)
    {
        if (!ft_isalnum(*name) && *name != '_')
			exit_tokenizer(1, tokens, "export: `%s': not a valid identifier",
				name);
        name++;
    }
 * @note The quotes around args are removed during tokenization.
 */
int	do_export(char **args, t_minishell *minishell)
{
	t_envvar	*data;
	t_envvar	*found_node;
	int			i;

	if (ft_matrix_size(args) == 1)
		return (put_export_vars(minishell->envvar_lst));
	i = 1;
	while (args[i])
	{
		data = envvar_new(args[i]);
		if (!data)
			return (EXIT_FAILURE);
		found_node = envvar_findbyname(minishell->envvar_lst, data->name);
		if (found_node)
		{
			envvar_updateone(found_node, data->value);
			free_envvar_node(&data);
		}
		else
			envvar_addoneback(&minishell->envvar_lst, data);
		i++;
	}
	return (update_envp(minishell));
}
