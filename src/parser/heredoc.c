#include "minishell.h"

/*
 * Deletes heredoc_tmpfile and cleans up the relevant resources.
 */
void	cleanup_heredoc(t_minishell *ms)
{
	t_cmd	*cmd;

	cmd = ms->cmd_lst;
	while (cmd)
	{
		if (cmd->heredoc_tmpfile)
		{
			unlink(cmd->heredoc_tmpfile);
			free(cmd->heredoc_tmpfile);
			cmd->heredoc_tmpfile = NULL;
		}
		cmd = cmd->next;
	}
}