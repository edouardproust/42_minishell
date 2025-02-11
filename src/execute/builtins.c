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
	{">>", TOKEN_APPEND, handle_append, ...}
	size_t				len;
	size_t				i;

	len = sizeof(builtins) / sizeof(builtins[0]);
	i = 0;
	// TODO: name_len = ft_strlen(progname)
	while (i < len)
	{
		if (ft_strncmp(builtins[i].name, progname, ft_strlen(progname)) == 0) // TODO: update above
			return (&builtins[i]);
		i++;
	}
	return (NULL);
}

/*
 * Run the given t_builtin.
 *
 * Exit on: ran in chaild process, callback failure
 */
void	run_builtin(int in_child_proc, t_builtin *builtin, char** args, t_cmd **cmd_lst)
{
	int	exit_code;

	exit_code = builtin->fn(args);
	if (in_child_proc || exit_code != EXIT_SUCCESS)
		exit_exec(exit_code, cmd_lst, NULL);
}
