#include "minishell.h"

/**
 * Retrieve the t_builtin of the given builtin name.
 *
 * @param progname Name of the builtin
 * @return ptr to the matching t_builtin, NULL if no match
 */
t_builtin	*get_builtin(char *progname)
{
	static t_builtin	builtins[] = {
	{"echo", do_echo, FALSE},
	{"cd", do_cd, TRUE},
	{"pwd", do_pwd, FALSE},
	{"export", do_export, TRUE},
	{"unset", do_unset, TRUE},
	{"env", do_env, FALSE},
	{"exit", do_exit, TRUE}
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
 * @param in_child_proc Is the builtin ran inside a child process?
 * @param builtin Struct containing data on the builtin
 * @param args The args of the command to execute
 * @param minishell Struct containing global Minishell data, including the 
 * 	environment variables list (`envvar_lst`) and the environment array (`envp`).
 * @note Exit on: ran in child process, callback failure
 */
void	run_builtin(t_bool in_child_proc, t_builtin *builtin, char **args,
	t_minishell *ms)
{
	ms->exit_code = builtin->fn(args, ms);
	if (in_child_proc)
		exit_minishell(ms->exit_code, ms, NULL);
}
