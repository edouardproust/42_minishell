#include "minishell.h"

t_builtin	*get_builtin(char *progname)
{
	static t_builtin	builtins[] = {
		{"echo", exec_echo, 0},
		{"cd", exec_cd, 1},
		{"pwd", exec_pwd, 0},
		{"export", exec_export, 1},
		{"unset", exec_unset, 1},
		{"env", exec_env, 0},
		{"exit", exec_exit, 1},
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

	res = builtin.fn(args);
	if (res != EXIT_SUCCESS)
		exit_exec(cmd_lst, );
		
}
