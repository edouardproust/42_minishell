#include "minishell.h"

/**
 * Adds an argument to the command's arguments list.
 *
 * @param cmd The command structure to which the argument will
 * be added.
 * @param arg The argument to add to the command's arguments list.
 * @note If malloc fails, the function returns without modifying
 * the command.
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
