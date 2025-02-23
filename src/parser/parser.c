#include "minishell.h"
/* 
 * Parses a list of tokens and converts them into a linked list of commands.
 *
 * - Initializes the parsing process by setting up the necessary variables.
 * - Creates a new command structure to hold the parsed tokens.
 * - Iterates over the tokens, processing them according to their type.
 * - Links the new commands to the command list.
 * 
 * Returns: A linked list of parsed t_cmd structures, or NULL if parsing fails.
 */
//TODO (A) Implement append and heredoc logic types.
t_cmd	*parse_tokens(t_token *tokens_head)
{
	t_parse	parse;
	t_cmd	*cmd_list;

	cmd_list = NULL;
	parse = (t_parse){&cmd_list, NULL, tokens_head, tokens_head};
	if (!parse.current_token)
		return (NULL);
	*parse.cmd_list_head = cmd_new(NULL);
	parse.current_cmd = *parse.cmd_list_head;
	if (!parse.current_cmd)
		exit_parsing(&parse, NULL);
	handle_token_type(&parse);
	return (cmd_list);
}