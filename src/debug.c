// TODO (E) Delete this file before submitting project
// TODO (E) Remove file from makefile SRCS

#include "minishell.h"
#include <sys/stat.h>

static t_node *node_create(char *bash_cmd, char *infile, char *outfile, t_node *prev_node);

t_node	*debug_init_pinput(void)
{
	t_node *node0 = node_create("tail -n +4", "test/infile", NULL, NULL);
	t_node *node1 = node_create("grep a", NULL, NULL, node0);
	t_node *node2 = node_create("llsort", NULL, NULL, node1);
	t_node *node3 = node_create("uniq -c", NULL, NULL, node2);
	t_node *node4 = node_create("sort -nr", NULL, NULL, node3); 
	node_create("head -n 3", NULL, "test/outfile", node4);
	return (node0);
}

static t_node *node_create(char *bash_cmd, char *infile, char *outfile, t_node *prev_node)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->pipe = NULL;
	cmd->fdin = STDIN_FILENO;
	cmd->fdout = STDOUT_FILENO;

	cmd->args = ft_split(bash_cmd, ' ');
	if (infile == NULL)
		cmd->infile = NULL;
	else
		cmd->infile = ft_strdup(infile);
	if (outfile == NULL)
		cmd->outfile = NULL;
	else
		cmd->outfile = ft_strdup(outfile);
	cmd->pipe = malloc(sizeof(int) * 2);
	cmd->pipe[0] = -1;
	cmd->pipe[1] = -1;

	t_node *node = malloc(sizeof(t_node));
	node->cmd = cmd;
	node->next = NULL;
	node->prev = prev_node;
	if (prev_node != NULL)
		prev_node->next = node;
	return (node);
}

void	debug_cmd(t_cmd *cmd, char *label)
{
	int	o = STDERR_FILENO;
	
	if (label == NULL)
		ft_fprintf(o, "╭─ cmd ─────────────────────────╮\n");
	else
		ft_fprintf(o, "╭─ %s ─────────────────────────╮\n", label);
	char *before = "│ • ";
	char *after = "\n";
	ft_fprintf(o, "%sargs: ", before);
	int	j = 0;
	while (cmd->args[j] != NULL)
	{
		ft_fprintf(o, "%s", cmd->args[j]);
		if (cmd->args[j + 1] != NULL)
			ft_fprintf(o, ", ");
		j++;
	}
	ft_fprintf(o, "%s", after);
	ft_fprintf(o, "%sinfile: %s%s", before, cmd->infile, after);
	ft_fprintf(o, "%soutfile: %s%s", before, cmd->outfile, after);
	ft_fprintf(o, "%sfds: ", before);
		ft_fprintf(o, "write=%d, ", cmd->pipe[1]);
		ft_fprintf(o, "read=%d", cmd->pipe[0]);
	ft_fprintf(o, "%s", after);
	ft_fprintf(o, "%sfdin: %d%s", before, cmd->fdin, after);
	ft_fprintf(o, "%sfdout: %d%s", before, cmd->fdout, after);
	if (label == NULL)
		ft_fprintf(o, "╰───────────────────────────────╯\n");
	else
	{	
		ft_fprintf(o, "╰────────────────────────────");
		int len = ft_strlen(label);
		while (len > 0)
		{
			ft_fprintf(o, "─");
			len--;
		}
		ft_fprintf(o, "╯\n");
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
		if (pinput->next)
			ft_printf("\t\t▼\n");
		pinput = pinput->next;
	}	
}

void debug_fd(char *label, int fd) {
	int	o = STDERR_FILENO;
	int flags = fcntl(fd, F_GETFL);

	if (flags == -1) {
		ft_fprintf(o, "➡ %s: fd=%d, status=%s\n", label, fd, strerror(errno));
	} else {
		ft_fprintf(o, "➡ %s: fd=%d, status=OK\n", label, fd);
	}
}

void debug_read_fd(char *label, int fd)
{
    char buffer[1024];
    int bytes_read;
    int o = STDERR_FILENO;

    ft_fprintf(o, "▶ ");
    if (label != NULL)
        ft_fprintf(o, "Read %s", label);
    else
        ft_fprintf(o, "Read fd");
    ft_fprintf(o, ":\n");

    int fd_copy = dup(fd);
    if (fd_copy == -1) {
        ft_fprintf(o, "Error: dup failed\n");
        return;
    }
    bytes_read = read(fd_copy, buffer, 1023);
    if (bytes_read == -1) {
        ft_fprintf(o, "Error: read failed\n");
        close(fd_copy);
        return;
    }
    buffer[bytes_read] = '\0';

    if (bytes_read == 0) {
        ft_fprintf(o, "(null)\n");
    } else {
        ft_fprintf(o, "%s\n", buffer);
    }
    struct stat st;
    if (fstat(fd, &st) == 0 && S_ISREG(st.st_mode)) {
        lseek(fd, 0, SEEK_SET);
    }

    close(fd_copy);
}
