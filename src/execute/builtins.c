#include "minishell.h"

/**
 * Retrieve the t_builtin for the given builtin name
 *
 * @return ptr to the matching t_builtin, NULL if no match
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
	size_t				lst_size;
	size_t				progname_len;
	size_t				i;

	lst_size = sizeof(builtins) / sizeof(builtins[0]);
	progname_len = ft_strlen(progname);
	i = 0;
	while (i < lst_size)
	{
		if (ft_strncmp(builtins[i].name, progname, progname_len) == 0)
			return (&builtins[i]);
		i++;
	}
	return (NULL);
}

/**
 * Run the given t_builtin.
 *
 * @note Exit on: ran in chaild process, callback failure
 */
void	run_builtin(int in_child_proc, t_builtin *builtin, char **args,
	t_minishell **minishell)
{
	int		exit_code;

	exit_code = builtin->fn(args, *minishell);
	if (in_child_proc || exit_code != EXIT_SUCCESS)
		exit_minishell(exit_code, minishell, NULL);
}
