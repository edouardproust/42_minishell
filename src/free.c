#include "minishell.h"

/*
 * Frees one command (t_cmd).
 * Return: pointer to the next cmd in the list
 */
t_cmd	*free_cmd(t_cmd **cmd)
{
	t_cmd	*cur_cmd;
	t_cmd	*nxt_cmd;

	if (!cmd || !*cmd)
		return (NULL);
	cur_cmd = *cmd;
	ft_free_split(&cur_cmd->args);
	ft_free_ptrs(3, &cur_cmd->infile, &cur_cmd->outfile,
			&cur_cmd->pipe);
	nxt_cmd = cur_cmd->next;
	ft_free_ptrs(1, &cur_cmd);
	return (nxt_cmd);
}

/*
 * Frees all the tokens' value and structure in the token list.
 */
void	free_token_lst(t_token **tokens)
{
	t_token	*cur_token;
	t_token	*nxt_token;

	if (!tokens || !*tokens)
		return ;
	cur_token = *tokens;
	while (cur_token)
	{
		nxt_token = cur_token->next;
		if (cur_token->value)
			ft_free_ptrs(1, &cur_token->value);
		free(cur_token);
		cur_token = nxt_token;
	}
	*tokens = NULL;
}
/*
 * Frees all the commands in the list (starting by 'cmd_list' node).
 */
void	free_cmd_lst(t_cmd **cmd_lst)
{
	t_cmd	*cur_cmd;
	t_cmd	*nxt_cmd;

	if (!cmd_lst || !*cmd_lst)
		return ;
	cur_cmd = *cmd_lst;
	while (cur_cmd)
	{
		nxt_cmd = cur_cmd->next;
		if (cur_cmd->pipe)
			free(cur_cmd->pipe);
		if (cur_cmd->args)
			free(cur_cmd->args);
		if (cur_cmd->infile)
			free(cur_cmd->infile);
		if (cur_cmd->outfile)
			free(cur_cmd->outfile);
		free(cur_cmd);
		cur_cmd = nxt_cmd;
	}
	*cmd_lst = NULL;
}

/*
 * Closes any fd up to FD_LIMIT, except standard ones.
 */
void	flush_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < FD_LIMIT)
		close(fd++);
}
