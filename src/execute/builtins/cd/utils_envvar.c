#include "minishell.h"

static int	create_missing_node(char *identifier, char **path, t_minishell *ms)
{
	char		*var_str;
	t_envvar	*new_node;

	var_str = ft_strglue(identifier, "=", *path);
	ft_free(1, path);
	if (!var_str)
		return (put_error1("cd: strjoin %s", identifier), EXIT_FAILURE);
	new_node = envvar_new(var_str);
	if (envvar_addoneback(&ms->envvar_lst, new_node) == EXIT_FAILURE)
	{
		ft_free(2, &var_str, &new_node);
		return (put_error1("cd: create var %s", identifier), EXIT_FAILURE);
	}
	ft_free(1, &var_str);
	return (EXIT_SUCCESS);
}

static int	update_or_create_node(char *identifier, char **path, t_minishell *ms)
{
	t_envvar	*found_node;

	found_node = envvar_findbyname(ms->envvar_lst, identifier);
	if (!found_node)
	{
		if (create_missing_node(identifier, path, ms) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		if (envvar_updateone(found_node, *path) == EXIT_FAILURE)
		{
			ft_free(1, path);
			return (put_error1("cd: update %s", identifier), EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	update_envvars(char **pwd, char **new_pwd, t_minishell *ms)
{
	if (update_or_create_node("OLDPWD", pwd, ms) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_free(1, pwd);
	if (update_or_create_node("PWD", new_pwd, ms) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_free(1, new_pwd);
	return (EXIT_SUCCESS);
}
