// TODO (E) Delete file (created for test purpose)
// TODO (E) Remove file from makefile SRCS

#include "minishell.h"

t_node	*exec_init_struct(void)
{
    t_cmd *cmd0 = malloc(sizeof(t_cmd));
	cmd0->args = ft_split("grep test", ' ');
	cmd0->infile = ft_strdup("test/infile");
	cmd0->outfile = NULL;
    
	t_cmd *cmd1 = malloc(sizeof(t_cmd));
	cmd1->args = ft_split("uniq -c", ' ');
	cmd1->infile = NULL;
	cmd1->outfile = NULL;
	 
	t_cmd *cmd2 = malloc(sizeof(t_cmd));
	cmd2->args = ft_split("sort", ' ');
	cmd2->infile = NULL;
	cmd2->outfile = NULL;
 
	t_cmd *cmd3 = malloc(sizeof(t_cmd));
	cmd3->args = ft_split("head -n 3", ' ');
	cmd3->infile = NULL;
	cmd3->outfile = ft_strdup("test.outfile");

	t_node *node3 = malloc(sizeof(t_node));
	node3->cmd = cmd3;
	node3->next = NULL;
	
	t_node *node2 = malloc(sizeof(t_node));
	node2->cmd = cmd2;
	node2->next = node3;

	t_node *node1 = malloc(sizeof(t_node));
	node1->cmd = cmd1;
	node1->next = node2;
	
	t_node *node0 = malloc(sizeof(t_node));
	node0->cmd = cmd0;
	node0->next = node1;

	return (node0);
}

void	exec_print_cmd_input(t_node *node)
{
	int	i = 0;
	while (node != NULL)
	{
		ft_printf("cmd %d:\n", i);
		ft_printf("  args: ");
		int	j = 0;
		t_cmd *cmd = node->cmd;
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
		node = node->next;
		i++;
	}
}
