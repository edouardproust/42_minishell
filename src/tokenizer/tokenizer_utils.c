#include "minishell.h"

t_tokenize_op	*get_tokenize_ops(void)
{
	static	t_tokenize_op	tokenize_ops[] = {
//	{"<<", TOKEN_HEREDOC},
//  {">>", TOKEN_APPEND},
	{"<", TOKEN_REDIR_IN},
	{">", TOKEN_REDIR_OUT},
	{"|", TOKEN_PIPE},
	{NULL, TOKEN_WORD}
	};

	return (tokenize_ops);
}

t_token	*handle_special_char(char *input, int *i)
{
	t_tokenize_op	*ops;
	char			*value;
	int				j;
	int				len;

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

t_token	*handle_token_creation(char *input, int *i, char *unmatched_quote)
{
	if (is_special_char(input[*i]))
		return (handle_special_char(input, i));
	return (create_word_token(input, i, unmatched_quote));
}

int	handle_token_error(t_token **token_lst, char unmatched_quote,
	t_minishell *minishell)
{
	free_token_lst(token_lst);
	if (unmatched_quote)
		exit_minishell(EXIT_FAILURE, minishell,
			"unexpected EOF while looking for matching `%c'");
	else
		exit_minishell(EXIT_FAILURE, minishell, NULL);
	return (0);
}
