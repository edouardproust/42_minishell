#include "minishell.h"

/**
 * Resolves the execution path of a program from its name.
 *
 * Searches for the program in the directories specified by the PATH environment
 * variable and returns its absolute path. If an absolute path is provided as input,
 * the function returns this path after testing its validity.
 *
 * @cmd_name: The name of the program to resolve.
 * 
 * Return: The full path of the program, or NULL if not found or an error occurs.
 */
static char	*get_exec_path(char *arg)
{
	char	*path;
	//char	*path_tmp;
	char	*path_env;
	char	**dirs;
	char	**dirs_start;
	//char	*dir;

	path = NULL;
	if (arg == NULL || arg[0] == '\0')
		ft_error("Error: get_exex_path: Arg is empty"); // TODO leaks
	if (arg[0] == '/')
	{
		if (access(arg, X_OK) == 0)
		{
			path = ft_strdup(arg);
			if (path == NULL)
				ft_error("Error: get_exec_path::strdup"); // TODO leaks
		}
	}
	else
	{
		path_env = getenv("PATH");
		ft_printf("[%s]\n", path_env); // TODO DEBUG
		if (path_env == NULL)
			ft_perror("getenv"); // TODO leaks
		dirs = ft_split(path_env, ':');
		if (dirs == NULL)
			ft_error("Error: get_exec_path::ft_split(path_env)"); // TODO leaks
		dirs_start = dirs;
  		while (*dirs != NULL)
		{
			ft_printf("[%s]\n", *dirs); // TODO DEBUG
		/*	dir = ft_strjoin(*dirs, "/");
			if (dir == NULL)
			{
				ft_free_split(&dirs_start);
				ft_error("Error: get_exec_path::ft_strjoin(*dirs, \"/\")"); // TODO leaks
			}
			path_tmp = ft_strjoin(dir, arg);
			if (path_tmp ==  NULL)
			{
				ft_free_ptrs(1, dir);
				ft_free_split(&dirs_start);
				ft_error("Error: get_exec_path::ft_strjoin(dir, arg)"); // TODO leaks
			}
    		ft_free_ptrs(1, dir);
    		if (access(path_tmp, X_OK) == 0)
			{
				path = path_tmp;
				break ;
			}
			ft_free_ptrs(1, path_tmp);
			*/
    		dirs++;
		}
		ft_free_split(&dirs_start);
	}
	if (path == NULL)
		ft_error("Error: get_exec_path: No executable file found"); // TODO leaks
	return (path);
}

void	execute_input(t_node *lst)
{
	ft_printf("[%s]\n", get_exec_path(lst->cmd->args[0]));

/*	int		fds[2];
	char	*exec_path;

	while (lst)
	{
		t_cmd *cmd = lst->cmd;

		if (cmd->pipe_after) {
			pipe(fds);
			cmd->fdout = fds[1];
			lst->next->cmd->fdin = fds[0];
		}
		pid = fork();
		if (pid < 0)
			ft_perror("fork");
		if (pid == 0) {
			if (cmd->pipe_after)
				close(fds[0]);	
			if (cmd->infile) {
				cmd->fdin = open(cmd->infile, O_RDONLY);
				if (cmd->fdin == -1)
					ft_perror("open infile");
				if (dup2(cmd->fdin, STDIN_FILENO) == -1)
					ft_perror("dup2 infile");
			}
			if (cmd->outfile) {
				cmd->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (cmd->fdout == -1)
					ft_perror("open outfile");
				if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
					ft_perror("dup2 outfile");
			}
			if (cmd->fdin != -1 && cmd->fdin != STDIN_FILENO) {
				close(cmd->fdin);
				cmd->fdin = -1;
			}
			if (cmd->fdout != -1 && cmd->fdout != STDOUT_FILENO) {
				close(cmd->fdout);
				cmd->fdout = -1;
			}
			exec_path = get_exec_path(cmd->args[0]);
			execve(executable_path, cmd->args, envp);
			ft_perror("execve");
		}
		if (cmd->pipe_after)
			close(fds[1]);
		waitpid(pid, &status, 0);
		lst = lst->next;
	}
*/
}
