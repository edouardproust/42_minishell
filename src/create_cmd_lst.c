#include "minishell.h"

t_cmd	*create_cmd_lst(char *input)
{
        t_token	*tokens;
        t_token	*tokens_head;
        t_cmd	*cmd_lst;

	tokens = tokenizer(input);
	tokens_head = tokens;
	cmd_lst = NULL;
	if (!tokens)
		return (NULL);
	debug_tokens(tokens);
	cmd_lst = parse_tokens(tokens_head);
	free_token_lst(&tokens_head);
	debug_cmds(cmd_lst);
	return (cmd_lst);
}
