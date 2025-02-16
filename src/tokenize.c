#include "minishell.h"
/* 
 * Tokenizes the input string into individual tokens.
 *
 * - Skips over spaces in the input string.
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
	char	*substr;
	int	type;
	int	i;

	tokens  = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (is_special_char(input[i]))
		{
			substr = ft_substr(input, i, 1);
			if (!substr)
				return (free_token_lst(&tokens), NULL);
			type = get_token_type(input, i);
			token_addback(&tokens, token_new(substr, type));
			if (!tokens)
				return (free(substr), NULL);
			i++;
		}
		else
		{
			new_token = create_word_token(input, &i);
			if (!new_token)
				return(free_token_lst(&tokens), NULL);
			token_addback(&tokens, new_token);
		}
	}
	return (tokens);
}
