#include "minishell.h"

t_envvar	*init_envvars(char **envp)
{
	t_envvar	*envvar_lst;
    t_envvar	*node;

	envvar_lst = NULL;
	node = NULL;
    while (*envp)
    {
		node = envvar_new(*envp++);
		if (!node)
		{
			if (errno == EINVAL)
				continue;
			else
				return (free_envvar_lst(&envvar_lst), NULL);
		}
		if (envvar_addoneback(&envvar_lst, node) == EXIT_FAILURE)
				return (free_envvar_lst(&envvar_lst), NULL);
    }
	return (envvar_lst);
}
