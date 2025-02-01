
// TODO (E) Remove file from makefile SRCS

#include "minishell.h"

t_node	*debug_init_pinput(void)
{
    t_cmd *cmd0 = malloc(sizeof(t_cmd));
	cmd0->args = ft_split("grep test", ' ');
	cmd0->infile = ft_strdup("test/infile");
	cmd0->outfile = NULL;
	cmd0->pipe_after = 1;
	cmd0->fdin = -1;
	cmd0->fdout = -1;
    
	t_cmd *cmd1 = malloc(sizeof(t_cmd));
	cmd1->args = ft_split("uniq -c", ' ');
	cmd1->infile = NULL;
	cmd1->outfile = NULL;
	cmd1->pipe_after = 1;
	cmd1->fdin = -1;
	cmd1->fdout = -1;
     
	t_cmd *cmd2 = malloc(sizeof(t_cmd));
	cmd2->args = ft_split("sort", ' ');
	cmd2->infile = NULL;
	cmd2->outfile = NULL;
	cmd2->pipe_after = 1;
 	cmd2->fdin = -1;
	cmd2->fdout = -1;
    
	t_cmd *cmd3 = malloc(sizeof(t_cmd));
	cmd3->args = ft_split("head -n 3", ' ');
	cmd3->infile = NULL;
	cmd3->outfile = ft_strdup("test/outfile");
	cmd3->pipe_after = 0;
	cmd3->fdin = -1;
	cmd3->fdout = -1;
    
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

void	debug_cmd(t_cmd *cmd, char *label)
{
	//ft_printf("■  cmd\n");
	if (label == NULL)
		ft_printf("╭─ cmd ─────────────────────────╮\n");
	else
		ft_printf("╭─ %s ─────────────────────────╮\n", label);
	char *before = "│ • ";
	char *after = "\n";
	ft_printf("%sargs: ", before);
	int	j = 0;
	while (cmd->args[j] != NULL)
	{
		ft_printf("%s", cmd->args[j]);
		if (cmd->args[j + 1] != NULL)
			ft_printf(", ");
		j++;
	}
	ft_printf("%s", after);
	ft_printf("%sinfile: %s%s", before, cmd->infile, after);
	ft_printf("%soutfile: %s%s", before, cmd->outfile, after);
	ft_printf("%spipe_after: %d%s", before, cmd->pipe_after, after);
	ft_printf("%sfdin: %d%s", before, cmd->fdin, after);
	ft_printf("%sfdout: %d%s", before, cmd->fdout, after);	
	if (label == NULL)
		ft_printf("╰───────────────────────────────╯\n");
	else
	{	
		ft_printf("╰────────────────────────────");
		int len = ft_strlen(label);
		while (len > 0)
		{
			ft_printf("─");
			len--;
		}
		ft_printf("╯\n");
	}
}

void	debug_pinput(t_node *pinput)
{
	int		i = 0;
	char	*a;

	while (pinput != NULL)
	{
		a = ft_itoa(i++);
		char *title = ft_strjoin("cmd", a);
		free(a);
		debug_cmd(pinput->cmd, title);
		free(title);
		if (pinput->cmd->pipe_after)
			ft_printf("\t\t▼\n");
		pinput = pinput->next;
	}	
}

void debug_fd(char *label, int fd) {
	int flags = fcntl(fd, F_GETFL);
	if (flags == -1) {
		ft_printf("➡ %s: fd=%d, status=%s\n", label, fd, strerror(errno));
	} else {
		ft_printf("➡ %s: fd=%d, status=OK\n", label, fd);
	}
}

void	debug_read_fd(char *label, int fd)
{
	char	buffer[1024];
	int		bytes_read;
	int		fdo = STDERR_FILENO;

	ft_putstr_fd("▶ ", fdo);
	if (label != NULL)
	{
		ft_putstr_fd("Read ", fdo);
		ft_putstr_fd(label, fdo);
	}
	else
		ft_putstr_fd("Read fd", fdo);
	ft_putstr_fd(":\n", fdo);
	while (1)
	{
		bytes_read = read(fd, buffer, 1024);
		if (bytes_read > 0)
			ft_putstr_fd(buffer, fdo);
		else if (bytes_read == 0)
		{
			ft_putstr_fd("(null)", fdo);
			break;
		}
		else
		{
			ft_putstr_fd("Error", fdo);
			break;
		}
	}
	ft_putstr_fd("\n", fdo);
}
