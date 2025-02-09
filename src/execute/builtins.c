#include "minishell.h"

/*
 * Retrieve the t_builtin for the given builtin name
 * 
 * Return: ptr to the matching t_builtin, NULL if no match
 */
t_builtin	*get_builtin(char *progname)
{
	static t_builtin	builtins[] = {
		{"echo", do_echo, 0},
		{"cd", do_cd, 1},
		{"pwd", do_pwd, 0},
		{"export", do_export, 1},
		{"unset", do_unset, 1},
		{"env", do_env, 0},
		{"exit", do_exit, 1}
	};
	size_t				len;
	size_t				i;

	len = sizeof(builtins) / sizeof(builtins[0]);
	i = 0;
	while (i < len)
	{
		if (ft_strncmp(builtins[i].name, progname, ft_strlen(progname)) == 0)
			return (&builtins[i]);
		i++;
	}
	return (NULL);
}

/*
 * Run the given t_builtin.
 *
 * Exit on:
 * - In parent proc (affects_state): called fn error
 * - In child proc: exit 0 if called fn success, exit 1 if fn error
 */
void	run_builtin(t_builtin *builtin, char** args, t_cmd **cmd_lst)
{
	int	res;

	res = builtin->fn(args);
	if (!builtin->affects_state)
	{
		if (res != EXIT_SUCCESS)
			exit_exec(cmd_lst, builtin->name);
		exit(EXIT_SUCCESS);
	}
	else if (res != EXIT_SUCCESS)
		exit_exec(cmd_lst, builtin->name);
}
