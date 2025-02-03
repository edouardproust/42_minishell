#include "minishell.h"

void	free_pinput(t_node **pinput)
{
	t_node *next;

	while (*pinput)
	{
		ft_free_split(&(*pinput)->cmd->args);
		ft_free_ptrs(3, &(*pinput)->cmd->infile, &(*pinput)->cmd->outfile,
			&(*pinput)->cmd->fds);
		next = (*pinput)->next;
		ft_free_ptrs(2, &(*pinput)->cmd, pinput);
		*pinput = next;
	}
}

#include <stdio.h>
void	exit_exec(t_node **parsed_input, char *fmt, ...)
{
	va_list	args;
	int		fdout;

	fdout = STDERR_FILENO;
	va_start(args, fmt);
	ft_fprintf(fdout, "minishell: ");
	if (ft_vfprintf(fdout, fmt, args) > 0 && errno != 0)
		ft_fprintf(fdout, ": %s", strerror(errno));
	ft_fprintf(fdout, "\n");
	va_end(args);
	free_pinput(parsed_input);
	exit(EXIT_FAILURE);
}
