#include "minishell.h"
/*
 * Tokenizes the input string into individual tokens.
 *
 * - Calls skip_whitespace in order to skip over spaces in the input string.
 * - For each special character (e.g., `|`, `<`, `>`),
 *		it creates a token and adds it to the token list.
 * - Uses `ft_substr` to create substrings of special characters 
 *   and `create_word_token` to create tokens for words.
 * - For special characters, the token type is determined using `get_token_type`.
 * - Tokens are added to the token list using `token_addback`.
 * - If memory allocation fails, the token list is freed and the function
 *   returns NULL.
 *
 * @return A list of tokens (`t_token` linked list), or NULL if an error
 *  occurs during tokenization.
 */
t_token	*tokenizer(char *input, t_minishell *minishell)
{
	t_token	*new_token;
	char	unmatched_quote;
	int		i;

	minishell->token_lst = NULL;
	i = 0;
	unmatched_quote = 0;
	while (input[i])
	{
		skip_whitespaces(input, &i);
		new_token = handle_token_creation(input, &i, &unmatched_quote);
		if (!new_token)
			return (handle_token_error(&minishell->token_lst,
					unmatched_quote, minishell), NULL);
		token_addback(&minishell->token_lst, new_token);
	}
	return (minishell->token_lst);
}
