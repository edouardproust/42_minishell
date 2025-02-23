#include "minishell.h"

/**
 * Add a token for an operator at the end of the t_token list.
 * 
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
/*atic int	operator_token_addback(t_token **tokens, char *input, int i)
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
/*c int	word_token_addback(t_token **tokens, char *input, int *i)
{
	t_token	*new_token;

	new_token = create_word_token(input, i);
	if (!new_token)
		return (EXIT_FAILURE);
	token_addback(tokens, new_token);
	return (EXIT_SUCCESS);
}*/

/** 
 * Tokenizes the input string into individual tokens.
 *
 * - Calls skip_whitespace in order to skip over spaces in the input string.
 * - For each special character (e.g., `|`, `<`, `>`), it creates a token and adds it to the token list.
 * - Uses `ft_substr` to create substrings of special characters and `create_word_token` to create tokens for words.
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
	int	i;

	minishell->token_lst = NULL;
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
			free_token_lst(&minishell->token_lst);
			if (unmatched_quote)
				exit_parsing(NULL, "unexpected EOF while looking for matching `%c'", unmatched_quote);
			else
				exit_parsing(NULL, NULL);
			return (NULL);
		}
			token_addback(&minishell->token_lst, new_token);
	}
	return (minishell->token_lst);
}
