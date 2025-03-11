#include "minishell.h"

void	init_expansion(t_expansion *exp, char *str)
{
	size_t	initial_size;

	initial_size = ft_strlen(str) * 2 + 1;
	if (initial_size < 1024)
		initial_size = 1024;
	exp->cleaned = malloc(initial_size);
	exp->buf_size = initial_size;
	exp->input_pos = 0;
	exp->output_pos = 0;
	exp->in_quote = 0;
}

void	ensure_buffer_space(t_expansion *exp, int space_needed)
{
	char	*new;
	int		new_size;

	if (exp->output_pos + space_needed < exp->buf_size)
		return ;
	new_size = exp->buf_size * 2;
	while (exp->output_pos + space_needed >= new_size)
		new_size = new_size * 2;
	new = ft_realloc(exp->cleaned, new_size);
	if (new)
	{
		exp->cleaned = new;
		exp->buf_size = new_size;
	}
}
