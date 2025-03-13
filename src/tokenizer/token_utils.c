#include "minishell.h"
/**
 * Allocates and initializes a new token structure.
 * 
 * @param value Processed/expanded token value
 * @param type Token type (TOKEN_WORD, TOKEN_PIPE, etc.)
 * @return Initialized token with:
 *         - NULL-terminated linked list
 *         - was_quoted=0 default
 *         - original_value=NULL
 */
t_token	*token_new(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->original_value = NULL;
	token->type = type;
	token->was_quoted = 0;
	token->next = NULL;
	return (token);
}

/**
 * Creates a token with both original and expanded values, tracking quote status.
 * 
 * @param original The original string from input (with quotes).
 * @param expanded The expanded string after quote removal and var expansion.
 * @param was_quoted Flag indicating if the token was originally quoted or not.
 * @return t_token* New word token, or NULL on allocation failure.
 */
static t_token	*create_token_with_values(char *original, char *expanded,
	int was_quoted)
{
	t_token	*token;

	token = token_new(expanded, TOKEN_WORD);
	if (!token)
		return (free(original), free(expanded), NULL);
	token->original_value = original;
	token->was_quoted = was_quoted;
	return (token);
}

/**
 * Processes characters for a word token, handling quotes and special characters.
 * 
 * @param input The input string being parsed.
 * @param index Current parsing position (updated during processing).
 * @param unmatched_quote Tracks unmatched quote state across parsing.
 * @return int 1 if quotes were present, 0 if not, -1 on unmatched quote error.
 * @note Advances index past quoted sections and normal word characters.
 */
static int	process_word(char *input, int *index, char *unmatched_quote)
{
	int	has_quotes;

	has_quotes = 0;
	while (input[*index] && !is_special_char(input[*index])
		&& !is_space_char(input[*index]))
	{
		if (is_quote_char(input[*index]))
		{
			has_quotes = 1;
			if (!skip_quotes(input, index, unmatched_quote))
				return (-1);
		}
		else
			(*index)++;
	}
	return (has_quotes);
}

/**
 * Creates a word token by processing input from current index position.
 * 
 * @param input The full input string being parsed.
 * @param index Current parsing position (updated during processing).
 * @param unmatched_quote Tracks quote matching state between tokens.
 * @param minishell Shell context for environment expansion.
 * @return t_token* Complete word token, or NULL on error.
 * @note Handles three main stages: character processing, string extraction,
 *       and expansion/quote removal before final token creation.
 */
t_token	*create_word_token(char *input, int *index, char *unmatched_quote,
		t_minishell *minishell)
{
	int		start;
	int		has_quotes;
	char	*original_word;
	char	*expanded_word;

	start = *index;
	has_quotes = process_word(input, index, unmatched_quote);
	if (has_quotes == -1)
		return (NULL);
	original_word = ft_substr(input, start, *index - start);
	if (!original_word)
		return (NULL);
	expanded_word = remove_quotes_and_expand(original_word, minishell);
	if (!expanded_word)
		return (free(original_word), minishell->exit_code = 1, NULL);
	return (create_token_with_values(original_word, expanded_word, has_quotes));
}

/*
 * Adds a new token to the end of the token list.
 */
void	token_addback(t_token **tokens, t_token *new)
{
	t_token	*tmp;

	if (!*tokens)
		*tokens = new;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
