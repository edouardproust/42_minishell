#include "minishell.h"

/**
 * Creates a list of commands from the input string.
 *
 * - Tokenizes the input string using the `tokenizer()` function.
 * - Initializes a command list.
 * - If tokenization fails (for eg, returns NULL), the function returns NULL.
 * - Calls `parse_tokens()` to parse the tokens into commands.
 * - Frees the token list to avoid memory leaks.
 *
 * @return A pointer to the head of the command list (`cmd_lst`), or NULL if
 * tokenization failed.
 * @TODO Check error messages
 */
void	init_cmd_lst(t_minishell *minishell)
{
	t_token	*tokens;

	tokens = tokenizer(minishell);
	ft_free(&minishell->input);
	if (!tokens)
		return ;
	minishell->token_lst = tokens;
	if (parse_tokens(minishell) == EXIT_FAILURE)
	{
		free_token_lst(&minishell->token_lst);
		minishell->cmd_lst = NULL;
	}
	else
		free_token_lst(&minishell->token_lst);
}
