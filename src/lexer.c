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
int	get_token_type(char *input, int i)
{
	if (input[i] == '|')
		return (TOKEN_PIPE);
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (TOKEN_HEREDOC);
	}
		return (TOKEN_REDIR_IN);
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (TOKEN_APPEND);
		return (TOKEN_REDIR_OUT);
	}
	return (TOKEN_WORD);
}

t_token	*create_word_token(char *input, int *index)
{
	int	start;
	char	*word;

	start = *index;
	while (input[*index] && input[*index] != ' ' &&
			input[*index] != '|' && input[*index] != '<' && input[*index] != '>')
		(*index)++;
	word = ft_substr(input, start, *index - start);
	return (token_new(word, TOKEN_WORD));
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
	t_token	*new_tokens;
	int	i;

	tokens  = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			token_addback(&tokens, token_new(ft_substr(input, i, 1), get_token_type(input, i)));
			i++;
		}
		else
		{
			new_token = create_word_token(input, &i);
			if (!new_token)
				return (NULL):
			token_addback(&tokens, new_token);
		}
	}
	return (tokens);
}
