#include "minishell.h"

void	init_expansion(t_expansion *exp, char *str)
{
	exp->cleaned = malloc(ft_strlen(str) * 2 + 1);
	exp->buf_size = ft_strlen(str) * 2 + 1;
	exp->input_pos = 0;
	exp->output_pos = 0;
	exp->in_quote = 0;
}

void	ensure_buffer_space(t_expansion *exp, int space_needed)
{
	char	*new;

	if (exp->output_pos + space_needed < exp->buf_size)
		return ;
	exp->buf_size = exp->buf_size * 2;
	new = ft_realloc(exp->cleaned, exp->buf_size);
	if (new)
		exp->cleaned = new;
}

