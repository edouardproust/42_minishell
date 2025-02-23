#include "minishell.h"

/**
 * Add a token for an operator at the end of the t_token list.
 * 
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
static int	operator_token_addback(t_token **tokens, char *input, int i)
{
	t_token	*new_token;
	char	*substr;
	int		type;

	substr = ft_substr(input, i, 1);
	if (!substr)
		return (EXIT_FAILURE);
	type = get_token_type(input, i);
	new_token = token_new(substr, type);
	if (!new_token)
	{
		ft_free_ptrs(1, &substr);
		return (EXIT_FAILURE);
	}
	token_addback(tokens, new_token);
	return (EXIT_SUCCESS);
}

/**
 * Add a aord token add the end of the t_token list.
 * 
 * @return EXIT_SUCCESS or EXIT_FAILURE
 * @note Increment i by the length of the word
 */
static int	word_token_addback(t_token **tokens, char *input, int *i)
{
	t_token	*new_token;

	new_token = create_word_token(input, i);
	if (!new_token)
		return (EXIT_FAILURE);
	token_addback(tokens, new_token);
	return (EXIT_SUCCESS);
}

/** 
 * Tokenizes the input string into individual tokens.
 *
 * - Skips over spaces in the input string.
 * - For each special character (e.g., `|`, `<`, `>`), it creates a token and
 *   adds it to the token list.
 * - Uses `ft_substr` to create substrings of special characters and
 *   `create_word_token` to create tokens for words.
 * - For special characters, the token type is determined using `get_token_type`.
 * - Tokens are added to the token list using `token_addback`.
 * - If memory allocation fails, the token list is freed and the function
 *   returns NULL.
 *
 * @return A list of tokens (`t_token` linked list), or NULL if an error
 *  occurs during tokenization.
 */
t_token	*tokenizer(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (is_special_char(input[i]))
		{
			if (operator_token_addback(&tokens, input, i) == EXIT_FAILURE)
				return (NULL);
			i++;
		}
		else
		{
			if (word_token_addback(&tokens, input, &i) == EXIT_FAILURE)
				return (NULL);
		}
	}
	return (tokens);
}
