#include "minishell.h"
/* 
 * Creates a list of commands from the input string.
 *
 * - Tokenizes the input string using the `tokenizer()` function.
 * - Initializes a command list.
 * - If tokenization fails (for eg, returns NULL), the function returns NULL.
 * - Calls `parse_tokens()` to parse the tokens into commands.
 * - Frees the token list to avoid memory leaks.
 *
 * Returns:
 * - A pointer to the head of the command list (`cmd_lst`), or NULL if tokenization failed.
 */
t_cmd	*init_cmd_lst(char *input)
{
        t_token	*tokens;
        t_token	*tokens_head;
        t_cmd	*cmd_lst;

	tokens = tokenizer(input);
	tokens_head = tokens;
	cmd_lst = NULL;
	if (!tokens)
		return (NULL);
	cmd_lst = parse_tokens(tokens_head);
	free_token_lst(&tokens_head);
	return (cmd_lst);
}
