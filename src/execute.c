/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:41:36 by eproust           #+#    #+#             */
/*   Updated: 2025/01/27 16:14:04 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO Remove (created for test purpose)
t_node *init_struct(void)
{
	t_cmd cmd1 = {
        .args = (char *[]){"grep", "test", NULL},
        .infile = (char *[]){"test/infile", NULL},
        .outfile = NULL
    };
    t_cmd cmd2 = {
        .args = (char *[]){"uniq", "-c", NULL},
        .infile = NULL,
        .outfile = NULL
    };
    t_cmd cmd3 = {
        .args = (char *[]){"sort", NULL},
        .infile = NULL,
        .outfile = NULL
    };
    t_cmd cmd4 = {
        .args = (char *[]){"head", "-n", "3", NULL},
        .infile = NULL,
        .outfile = (char *[]){"test/outfile", NULL}
    };
    t_node node4 = { &cmd4, NULL };
    t_node node3 = { &cmd3, &node4 };
    t_node node2 = { &cmd2, &node3 };
    t_node node1 = { &cmd1, &node2 };	
    
	return (node1);
}

// TODO: Remove (created for testing purpose)
int	debug_cmd_input(t_node *cmd)
{
	int	i = 1;
	while (cmd != NULL)
	{
		ft_printf("cmd %d:\n", i);
		ft_printf(" args: ");
		int	j = 0;
		while (cmd->args[j] != NULL)
		{
			ft_printf("%s", cmd->args[j]);
			if (cmd->args[j + 1] != NULL)
				ft_printf(", ");
			j++;
		}
		ft_printf("\n");
		ft_printf("  infile: %s\n", cmd->infile);
		ft_printf("  outfile: %s\n", cmd->outfile);
		cmd = cmd->next;
		i++;
	}
	return (EXIT_SUCCESS);
}

execute_command(t_cmd *cmd)
{
	debug_cmd_input(cmd); // TODO remove (created for testing purpose)
}
