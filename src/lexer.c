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
		printf("Processing char: '%c' at index: %d\n", input[i], i);
		while (input[i] == ' ')
			i++;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			substr = ft_substr(input, i, 1);
			type = get_token_type(input, i);
			token_addback(&tokens, token_new(substr, type));
			printf("Token added: '%s' (Type: %d)\n", substr, type);
			i++;
		}
		else
		{
			new_token = create_word_token(input, &i);
			if (!new_token)
				return (NULL);
			token_addback(&tokens, new_token);
			printf("Word token added: '%s' (Type: %d)\n", new_token->value, new_token->type);
		}
	}
	printf("---- Tokenization completed ----\n");
	return (tokens);
}
