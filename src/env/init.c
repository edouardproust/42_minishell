#include "minishell.h"

/**
 * Initialize environment variables list from envp.
 * 
 * @param envp Array of environment variable strings.
 * @return Pointer to the head of the initialized list.
 * 
 * @note Exits program on memory allocation failure.
 */
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
				exit_envvar(1, &envvar_lst, "malloc");
		}
		if (envvar_addoneback(&envvar_lst, node) == EXIT_FAILURE)
			exit_envvar(1, &envvar_lst, "envvar_addoneback");
    }
	return (envvar_lst);
}
