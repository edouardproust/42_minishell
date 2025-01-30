#include "minishell.h"

void	execute_input(t_node **lst)
{
	(void)lst;	// TODO remove

	char	*execpath;
	execpath = get_exec_path("lsi", lst);
	ft_printf("[%s]\n", execpath);
	ft_free_ptrs(1, &execpath);	

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
