#include "minishell.h"

static int	envvar_lstsize(t_envvar *head)
{
	int		count;
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

char	**update_envp(t_minishell **minishell)
{
	t_envvar	*current;
	char		**envp;
	int			i;
	char		**err_msg = "failed to update environment";

	ft_free_split(&(*minishell)->envp);
	current = (*minishell)->envvar_lst;
	(*minishell)->envp = malloc(sizeof(char *) * (envvar_lstsize(current) + 1));
	if (!envp)
		exit_minishell(1, minishell, err_msg);
	i = 0;
	while (current)
	{
		envp[i] = ft_strglue(current->name, "=", current->value);
		if (!envp[i])
		{
			// TODO: free partial allocation of up to i (do a generic fonction 
			// ft_free_matrix(char *matrix, int end_index))
			// And use it here + in ft_split.c + ft_matrix_dup (fn below)
			exit_minishell(1, minishell, err_msg);
		}
		current = current->next;
		i++;
	}

	return (envp)
}

char	**ft_matrix_dup(char **matrix)
{
	char	**dup;
	int		count;
	int		i;

	count = 0;
	while (matrix[count])
		count++;
	dup = malloc(sizeof(char *) * (count + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < count)
	{
		dup[i] = ft_strdup(matrix[i]);
		if (!dup[i])
		{
			write(1, "[1]\n", 4);
			while (--i >= 0)
				ft_free_ptrs(1, &dup[i]);
			return (ft_free_ptrs(1, &dup), NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
