#include "minishell.h"

char	**tokenizer(char *input)
{
	char	**tokens;

	if (!input)
		return (NULL);
	tokens = ft_split(input, ' ');
	if (!tokens)
		return (NULL);
	return (tokens);
}

