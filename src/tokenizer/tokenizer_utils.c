#include "minishell.h"
/**
 * Returns a static list of tokenization operators and their corresponding types.
 * 
 * Used in `handle_special_char()` to identify and categorize operators.
 * 
 * @return Pointer to a static array of `t_tokenize_op` structures.
 */
t_tokenize_op	*get_tokenize_ops(void)
{
	static t_tokenize_op	tokenize_ops[] = {
	{"<<", TOKEN_HEREDOC},
	{">>", TOKEN_APPEND},
	{"<", TOKEN_REDIR_IN},
	{">", TOKEN_REDIR_OUT},
	{"|", TOKEN_PIPE},
	{NULL, TOKEN_WORD}
	};

	return (tokenize_ops);
}

/**
 * Handles special characters (`|`, `<`, `>`, `<<`, `>>`).
 *
 * - Compares the input string with predefined token patterns.
 * - Creates a token of the corresponding type if a match is found.
 * - Updates the input index accordingly.
 * 
 * @param input The input string to parse.
 * @param i Pointer to the current index in the input string.
 * @returns New token (`t_token *`) or NULL if no match is found.
 */
t_token	*handle_special_char(char *input, int *i)
{
	t_tokenize_op	*ops;
	char			*value;
	int				j;
	int				len;

	ops = get_tokenize_ops();
	j = 0;
	while (ops[j].pattern)
	{
		len = ft_strlen(ops[j].pattern);
		if (ft_strncmp(input + *i, ops[j].pattern, len) == 0)
		{
			value = ft_substr(input, *i, len);
			*i = *i + len;
			return (token_new(value, ops[j].type));
		}
		j++;
	}
	return (NULL);
}

/**
 * Determines whether the next token is a special character or a word.
 *
 * - Calls `handle_special_char()` if the character is a special token.
 * - Calls `create_word_token()` otherwise.
 * 
 * @param input The input string to parse.
 * @param i Pointer to the current index in the input string.
 * @param unmatched_quote Pointer to the unmatched quote character, if any.
 * @returns Newly allocated token (`t_token *`).
 */
t_token	*handle_token_creation(char *input, int *i, char *unmatched_quote,
		t_minishell *minishell)
{
	t_token	*token;

	if (is_special_char(input[*i]))
		return (handle_special_char(input, i));
	token = create_word_token(input, i, unmatched_quote, minishell);
	if (!token)
	{
		if (*unmatched_quote == 0)
			minishell->exit_code = 1;
		return (NULL);
	}
	return (token);
}

/**
 * Handles tokenization errors, such as unmatched quotes.
 *
 * - Frees the token list if an error is encountered.
 * - Exits the minishell with an appropriate error message.
 *
 * @param token_lst Pointer to the list of tokens to free.
 * @param unmatched_quote The unmatched quote character, if any.
 * @param minishell Pointer to the minishell data structure.
 * @return Always returns EXIT_SUCCESS.
 */
int	handle_token_error(t_token **token_lst, char unmatched_quote,
	t_minishell *minishell)
{
	free_token_lst(token_lst);
	if (unmatched_quote)
	{
		put_error1("unexpected EOF while looking for matching `%c'",
			char_to_str(unmatched_quote));
		minishell->exit_code = E_CRITICAL;
		return (EXIT_FAILURE);
	}
	else
		minishell->exit_code = 1;
	return (EXIT_SUCCESS);
}
