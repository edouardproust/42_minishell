#include "minishell.h"

//create a new token + allocate memory for it
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
//added conditions for token types heredoc + append, TB implemented
int	get_token_type(char c)
{
	if (c == '|')
		return (TOKEN_PIPE);
	if (c == '<')
	{
		if (c + 1 == '<')
		{
			c++;
			return (TOKEN_HEREDOC);
		}
	}
		return (TOKEN_REDIR_IN);
	if (c == '>')
	{
		if (c + 1 == '>')
		{
			c++;
			return (TOKEN_APPEND);
		}
	}
		return (TOKEN_REDIR_OUT);
	return (TOKEN_WORD);
}

t_token	*create_word_token(char *input, int *index)
{
	int	start;

	start = *index;
	while (input[*index] && input[*index] != ' ' &&
			input[*index] != '|' && input[*index] != '<' && input[*index] != '>')
		(*index)++;
	return token_new(ft_substr(input, start, *index - start), TOKEN_WORD);
}
//adds a new token to the list
void 	token_addback(t_token **tokens, t_token *new)
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

t_token	*tokenizer(char *input)
{
	t_token	*tokens;
	int	i;

	tokens  = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
//		if (input[i] == '\0')
//			break ;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			token_addback(&tokens, token_new(ft_substr(input, i, 1), get_token_type(input[i])));
		else
			token_addback(&tokens, create_word_token(input, &i));
		i++;
	}
	return (tokens);
}
