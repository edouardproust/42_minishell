#include "minishell.h"

t_builtin	*get_builtin(char *progname)
{
	static t_builtin	builtins[] = {
		{"echo", execute_echo, 0},
		{"cd", execute_cd, 1},
		{"pwd", execute_pwd, 0},
		{"export", execute_export, 1},
		{"unset", execute_unset, 1},
		{"env", execute_env, 0},
		{"exit", execute_exit, 1},
		{NULL, NULL, 0}
	};
	size_t				len;
	size_t				i;

	len = sizeof(builtins) / sizeof(builtins[0]);
	i = 0;
	while (i < len)
	{
		ft_printf("{%s, %s}\n", builtins[i].name, progname);
		if (ft_strncmp(builtins[i].name, progname, ft_strlen(progname)) == 0)
			return (&builtins[i]);
		i++;
	}
	return (NULL);
}

void	execute_builtin(t_builtin *builtin, char** args, t_cmd **cmd_lst)
{
	int	res;

	res = builtin->fn(args);
	if (res != EXIT_SUCCESS)
		exit_exec(cmd_lst, builtin->name); // TODO check bash error and adapt
}
