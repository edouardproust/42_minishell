#include "minishell.h"

t_builtin	*get_builtin(char *progname)
{
	static t_builtin	*builins[] = {
		{"echo", exec_echo, 0},
		{"cd", exec_cd, 1},
		{"pwd", exec_pwd, 0},
		{"export", exec_export, 1},
		{"unset", exec_unset, 1},
		{"env", exec_env, 0},
		{"exit", exec_exit, 1},
		NULL
	};

	(void)progname;
	return (&builtins[0]);	
}
