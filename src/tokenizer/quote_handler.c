#include "minishell.h"

int	skip_quotes(char *input, int *index, char *unmatched_quote)
{
	char	quote;

	quote = input[*index];
	(*index)++;
	while (input[*index] && input[*index] != quote)
		(*index)++;
	if (!input[*index])
	{
		*unmatched_quote = quote;
		return (0);
	}
	(*index)++;
	return (1);
}

static void	process_char(char c, char *in_quote, char *cleaned, int *j)
{
	if (*in_quote)
	{
		if (c == *in_quote)
			*in_quote = 0;
		else
			cleaned[(*j)++] = c;
	}
	else
	{
		if (is_quote_char(c))
			*in_quote = c;
		else
			cleaned[(*j)++] = c;
	}
}

char	*remove_quotes(char *str)
{
	char	*cleaned;
	char	in_quote;
	int		i;
	int		j;

	cleaned = malloc(ft_strlen(str) + 1);
	if (!cleaned)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	j = 0;
	in_quote = 0;
	while (str[i])
	{
		process_char(str[i], &in_quote, cleaned, &j);
		i++;
	}
	cleaned[j] = '\0';
	free(str);
	return (cleaned);
}
