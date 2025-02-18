#include "minishell.h"
/* 
 * Creates a new token with the given value and type.
 * Returns: A new token or NULL if allocation fails.
 */
t_token	*token_new(char *value, int type)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
        token->value = value;
        token->type = type;
        token->next = NULL;
        return (token);
}
/* 
 * Determines the token type based on the character at position `i`.
 * Returns: The token type (e.g., TOKEN_PIPE, TOKEN_REDIR_IN).
 */
// TODO (A): implement heredoc and append logic
int	get_token_type(char *input, int i)
{
	if (input[i] == '|')
		return (TOKEN_PIPE);
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (TOKEN_HEREDOC);
		return (TOKEN_REDIR_IN);
	}
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (TOKEN_APPEND);
		return (TOKEN_REDIR_OUT);
	}
	return (TOKEN_WORD);
}
/* 
 * Creates a word token from the input string starting at `index`.
 * Loops inside the input string and checks for quote chars.
 * Returns: A new word token or NULL if allocation fails.
 */
t_token	*create_word_token(char *input, int *index, char *unmatched_quote)
{
	int     start;
	char    *word;
	t_token	*token;

	start = *index;
	while (input[*index] && is_word_char(input[*index]))
	{
		if (is_quote_char(input[*index]))
		{
			if (!skip_quotes(input, index, unmatched_quote))
			return (NULL);
		}
		(*index)++;
	}
	word = ft_substr(input, start, *index - start);
	word = remove_quotes(word);
	if (!word)
		return (NULL);
	token = token_new(word, TOKEN_WORD);
	if (!token)
		free(word);
	return (token);
}
/* 
 * Adds a new token to the end of the token list.
 */
void	token_addback(t_token **tokens, t_token *new)
{
	t_token *tmp;

	if (!*tokens)
		*tokens= new;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
