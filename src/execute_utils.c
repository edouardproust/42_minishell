#include "minishell.h"

void	free_parsed_input(t_node **pinput)
{
	t_node *next;

	while (*pinput)
	{
		ft_free_split(&(*pinput)->cmd->args);
		ft_free_ptrs(2, &(*pinput)->cmd->infile, &(*pinput)->cmd->outfile);
		next = (*pinput)->next;
		ft_free_ptrs(2, &(*pinput)->cmd, pinput);
		*pinput = next;
	}
}

#include <stdio.h>
void	exit_exec(t_node **parsed_input, char *fmt, ...)
{
	va_list	args;

	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
	{
		free_parsed_input(parsed_input);
		ft_pexit("dup2 (error_exit)");
	}	
	va_start(args, fmt);
	ft_printf("minishell: ");
	if (ft_vprintf(fmt, args) > 0)
		ft_printf(": ");
	va_end(args);
	perror("");
	(void)parsed_input; // TODO remove
	free_parsed_input(parsed_input);
	exit(EXIT_FAILURE);
}
