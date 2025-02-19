#include "minishell.h"
/* 
 * Tokenizes the input string into individual tokens.
 *
 * - Calls skip_whitespace in order to skip over spaces in the input string.
 * - For each special character (e.g., `|`, `<`, `>`), it creates a token and adds it to the token list.
 * - Uses `ft_substr` to create substrings of special characters and `create_word_token` to create tokens for words.
 * - For special characters, the token type is determined using `get_token_type`.
 * - Tokens are added to the token list using `token_addback`.
 * - If memory allocation fails, the token list is freed and the function returns NULL.
 *
 * Returns:
 * - A list of tokens (`t_token` linked list), or NULL if an error occurs during tokenization.
 */
//TODO (A) : Divide it in more funtions and keep 't_token *tokenizer' as a high-end function
t_token	*tokenizer(char *input)
{
	t_token	*tokens;
	t_token	*new_token;
	char	unmatched_quote;
	int	i;

	tokens  = NULL;
	i = 0;
	unmatched_quote = 0;
	while (input[i])
	{
		skip_whitespaces(input, &i);
		if (is_special_char(input[i]))
			new_token = handle_special_char(input, &i);
		else
			new_token = handle_word_token(input, &i, &unmatched_quote);
		if (!new_token)
		{
			free_token_lst(&tokens);
			if (unmatched_quote)
				exit_parsing(NULL, "unexpected EOF while looking for matching `%c'", unmatched_quote);
			else
				exit_parsing(NULL, NULL);
			return (NULL);
		}
			token_addback(&tokens, new_token);
	}
	return (tokens);
}
