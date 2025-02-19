#include "minishell.h"

int	skip_quotes(char *input, int *index, char *unmatched_quote)
{
	char	quote;
	int	start;

	quote = input[*index];
	start = *index;
	(*index)++;
	while (input[*index] && input[*index] != quote)
		(*index)++;
	if (!input[*index])
	{
		*unmatched_quote = quote;
		return (0);
	}
	(*index)++;
	if (start == 0 && input[*index] == '\0') 
		return (1);
	return (1);
}

char	*remove_quotes(char *str)
{
	size_t	len;
	char	*cleaned;
	char	first;
	char	last;

	len = ft_strlen(str);
	first = str[0];
	last = str[len - 1];
	if (len < 2)
		return (str);
	if ((first == '\'' || first == '"') && first == last)
	{
		if (ft_strchr(str + 1, first))
			return (str);
		cleaned = ft_substr(str, 1, len - 2);
		free(str);
		return (cleaned);
	}
	return (str);
}
