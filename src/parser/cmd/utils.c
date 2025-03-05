#include "minishell.h"

/*
* Adds an argument to the command's arguments list.
*/
void	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int		i;
	int		count;
	char	**new_args;

	count = 0;
	while (cmd->args && cmd->args[count])
		count++;
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return ;
	i = -1;
	while (++i < count)
		new_args[i] = cmd->args[i];
	new_args[count] = arg;
	new_args[count + 1] = NULL;
	ft_free(1, &cmd->args);
	cmd->args = new_args;
}
