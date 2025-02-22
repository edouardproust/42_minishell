#include "minishell.h"

t_token_op *get_token_op_for_tokenization(char *input_start)
{
	t_token_op	*token_ops;
	int	i;
	int	pattern_len;

	token_ops = get_token_ops();
	i = 0;
	while (token_ops[i].pattern)
	{
		pattern_len = ft_strlen(token_ops[i].pattern);
		if (ft_strncmp(input_start, token_ops[i].pattern, pattern_len) == 0)
			return (&token_ops[i]);
		i++;
	}
	return &token_ops[i];
}

t_token	*handle_special_char(char *input, int *i)
{
	t_token_op	*op;
	char	*value;
	int	len;

	op = get_token_op_for_tokenization(&input[*i]);
	len = ft_strlen(op->pattern);
	value = ft_substr(input, *i, len);
	if (!value)
		return (NULL);
	*i = *i + len;
	return (token_new(value, op->type));
}

t_token	*handle_word_token(char *input, int *i, char *unmatched_quote)
{
	return (create_word_token(input, i, unmatched_quote));
}
