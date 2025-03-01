#include "minishell.h"

/**
 * Inititalise the builtins list and return it.
 * 
 * @param void
 * @return The initialized builtins list
 */
static t_builtin	*get_builtin_lst(void)
{
	static t_builtin	builtin_lst[] = {
	{"echo", do_echo},
	{"cd", do_cd},
	{"pwd", do_pwd},
	{"export", do_export},
	{"unset", do_unset},
	{"env", do_env},
	{"exit", do_exit},
	{NULL, NULL}
	};

	return (builtin_lst);
}

/**
 * Retrieve the t_builtin of the given builtin name.
 *
 * @param progname Name of the builtin
 * @return ptr to the matching t_builtin, NULL if no match
 */
t_builtin	*get_builtin(t_cmd *cmd)
{
	t_builtin	*builtin_lst;
	char		*progname;
	size_t		progname_len;
	size_t		i;

	if (ft_matrix_size(cmd->args) == 0)
		return (NULL);
	progname = cmd->args[0];
	progname_len = ft_strlen(progname);
	builtin_lst = get_builtin_lst();
	i = 0;
	while (builtin_lst[i].name)
	{
		if (ft_strncmp(builtin_lst[i].name, progname, progname_len + 1) == 0)
			return (&builtin_lst[i]);
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
