#include "minishell.h"

t_token_op *get_token_ops(void)
{
    static t_tokenize_op tokenize_ops[] =
    {
        {"|", TOKEN_PIPE},
//      {"<<", TOKEN_HEREDOC},
//      {">>", TOKEN_APPEND},
 		{"<", TOKEN_REDIR_IN},
        {">", TOKEN_REDIR_OUT},
        {NULL, TOKEN_WORD}
    };
    return (tokeninze_ops);
}

t_token	*handle_special_char(char *input, int *i)
{
	t_tokenize_op	*ops;
	char	*value;
	int	j;
	int	len;

	ops = get_tokenize_ops(); 
	j = 0;
	while (ops[j].pattern)
	{
		len = ft_strlen(ops[j].pattern);
		if (ft_strncmp(input + *i, ops[j].pattern, len) == 0)
		{
			value = ft_substr(input, *i, len);
			*i = *i + len;
			return (token_new(value, ops[j].type));
		}
		j++;
	}
	return (NULL);
}

t_token	*handle_word_token(char *input, int *i, char *unmatched_quote)
{
	return (create_word_token(input, i, unmatched_quote));
}