#include "minishell.h"

int	skip_quotes(char *input, int *index)
{
	char	quote;

	quote = input[*index];
	(*index)++;
	while (input[*index] && input[*index] != quote)
		(*index)++;
	if (!input[*index])
	{
		 exit_parsing(NULL, "unexpected EOF while looking for matching `%c'", quote);
		 return (0);
	}
	return (1);
}

char	*remove_quotes(char *str)
{
	int	i;
	int	j;
	char	quote;
	char	*cleaned;

	cleaned = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!cleaned)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_quote_char(str[i]))
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				cleaned[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			cleaned[j++] = str[i++];
	}
	cleaned[j] = '\0';
	free(str);
	return (cleaned);
}
