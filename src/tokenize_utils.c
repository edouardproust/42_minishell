#include "minishell.h"

t_token	*handle_special_char(char *input, int *i)
{
	char	*substr;
	int	type;

	substr = ft_substr(input, *i, 1);
	if (!substr)
		return (NULL);
	type = get_token_type(input, *i);
	(*i)++;
	return (token_new(substr, type));
}

t_token	*handle_word_token(char *input, int *i, char *unmatched_quote)
{
	return (create_word_token(input, i, unmatched_quote));
}
