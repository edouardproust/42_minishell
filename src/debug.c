// TODO (E) Delete this file before submitting project
// TODO (E) Remove file from makefile SRCS

#include "minishell.h"
#include <sys/stat.h>

static t_cmd *cmd_new_addback(char *bash_cmd, char *infile, char *outfile, t_cmd *prev_cmd);

t_cmd	*create_cmd_lst(void)
{
	//t_cmd *cmd0 = cmd_new_addback("tail -n +4", "test/infile", NULL, NULL);
	t_cmd *cmd0 = cmd_new_addback("ls sdfg", "test/infile", NULL, NULL);
	t_cmd *cmd1 = cmd_new_addback("grep a", NULL, NULL, cmd0);
	t_cmd *cmd2 = cmd_new_addback("sort", NULL, NULL, cmd1);
	t_cmd *cmd3 = cmd_new_addback("uniq -c", NULL, NULL, cmd2);
	t_cmd *cmd4 = cmd_new_addback("sort -nr", NULL, NULL, cmd3); 
	cmd_new_addback("head -n 3", NULL, "test/outfile", cmd4);
	return (cmd0);
}

static t_cmd *cmd_new_addback(char *bash_cmd, char *infile, char *outfile, t_cmd *prev_cmd)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->pipe = NULL;
	cmd->fdin = STDIN_FILENO;
	cmd->fdout = STDOUT_FILENO;
	cmd->prev = prev_cmd;
	cmd->next = NULL;

	cmd->args = ft_split(bash_cmd, ' ');
	if (infile != NULL)
		cmd->infile = ft_strdup(infile);
	if (outfile != NULL)
		cmd->outfile = ft_strdup(outfile);
	cmd->pipe = malloc(sizeof(int) * 2);
	if (cmd->prev)
		cmd->prev->next = cmd;
	cmd->pipe[0] = -1;
	cmd->pipe[1] = -1;

	return (cmd);
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

void	debug_cmd_lst(t_cmd *cmd_lst)
{
	int		i = 0;
	char	*a;
	t_cmd	*cmd;

	cmd = cmd_lst;
	while (cmd)
	{
		a = ft_itoa(i++);
		char *title = ft_strjoin("cmd", a);
		free(a);
		debug_cmd(cmd, title);
		free(title);
		if (cmd->next)
			ft_printf("\t\t▼\n");
	 	cmd = cmd->next;
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
