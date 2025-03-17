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

