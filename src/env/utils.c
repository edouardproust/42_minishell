#include "minishell.h"

char	*get_env_value(char *var_name, t_minishell *minishell)
{
	t_envvar	*var;

	var = envvar_findbyname(minishell->envvar_lst, var_name);
	if (!var)
		return (NULL);
	return (var->value);
}

static int	envvar_lstsize(t_envvar *head)
{
	int			count;
	t_envvar	*current;

	if (!head)
		return (0);
	current = head;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	update_envp(t_minishell *minishell)
{
	t_envvar	*current;
	char		**envp;
	int			i;

	ft_free_split(&minishell->envp);
	current = minishell->envvar_lst;
	envp = malloc(sizeof(char *) * (envvar_lstsize(current) + 1));
	if (!envp)
		return (EXIT_FAILURE);
	i = 0;
	while (current)
	{
		envp[i] = ft_strglue(current->name, "=", current->value);
		if (!envp[i])
			return (ft_free_splitn(&envp, i), EXIT_FAILURE);
		current = current->next;
		i++;
	}
	envp[i] = NULL;
	minishell->envp = envp;
	return (EXIT_SUCCESS);
}
