#include "minishell.h"

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
				return (NULL);
			type = get_token_type(input, i);
			token_addback(&tokens, token_new(substr, type));
			i++;
		}
		else
		{
			new_token = create_word_token(input, &i);
			if (!new_token)
				return (NULL);
			token_addback(&tokens, new_token);
		}
	}
	return (tokens);
}
