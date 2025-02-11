#include "minishell.h"

static char	*dup_name(char *var, int equal_sign_index)
{
    char	*name;

    name = ft_substr(var, 0, equal_sign_index);
    //if (!name) TODO:
    return (name);
}

static char	*dup_value(char *var, int equal_sign_index)
{
    char    *value;

    value = ft_substr(var, equal_sign_index + 1, ft_strlen(var));
	//if (!value) TODO:
	return (value);
}

static t_envvar	*envvar_new(char *var)
{
	t_envvar	*node;
    int			equal_sign_index;

	node = malloc(sizeof(t_envvar));
    if (!node)
		return (NULL); //TODO:
	equal_sign_index = ft_strchri(var, '=');
	if (equal_sign_index < 0)
		return (NULL); //TODO:
	node->name = dup_name(var, equal_sign_index);
	if (!node->name)
		return (NULL); //TODO:
	node->value = dup_value(var, equal_sign_index);
	if (!node->value)
		return (NULL); //TODO:
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

t_envvar	*init_envvars(char **envp)
{
	t_envvar	*lst;
    t_envvar	*node;

	node = NULL;
	lst = node;
    while (*envp)
    {
		node = envvar_new(*envp++);
		envvar_addone(&lst, node); //TODO: check if failure?
    }
	return (lst);
}
