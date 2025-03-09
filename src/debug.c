// TODO (E) Delete this file before submitting project
// TODO (E) Remove file from makefile SRCS

#include "minishell.h"
#include <sys/stat.h>

int	g_logfd = -1;

static t_cmd	*cmd_new_addback(char *bash_cmd, char *infile, char *outfile,
	t_cmd *prev_cmd)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->pipe = NULL;
	cmd->fdin = STDIN_FILENO;
	cmd->fdout = STDOUT_FILENO;
	cmd->prev = prev_cmd;
	cmd->next = NULL;
	cmd->pid = 0;
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

t_cmd	*create_cmd_lst(void)
{
	t_cmd	*cmd0;
	t_cmd	*cmd1;
	t_cmd	*cmd2;
	t_cmd	*cmd3;
	t_cmd	*cmd4;

	cmd0 = cmd_new_addback("tail -n +4", "test/infile", NULL, NULL);
	cmd1 = cmd_new_addback("grep a", NULL, NULL, cmd0);
	cmd2 = cmd_new_addback("sort", NULL, NULL, cmd1);
	cmd3 = cmd_new_addback("uniq -c", NULL, NULL, cmd2);
	cmd4 = cmd_new_addback("sort -nr", NULL, NULL, cmd3);
	cmd_new_addback("head -n 3", NULL, NULL, cmd4);
	return (cmd0);
}

void	debug_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: '%s' (Type: %d)\n", tokens->value, tokens->type);
		tokens = tokens->next;
	}
}

void	open_logfile(char *filepath)
{
	int	tmp_fd;

	tmp_fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd != -1)
		close(tmp_fd);
	g_logfd = open(filepath, O_WRONLY | O_APPEND, 0644);
	if (g_logfd == -1)
		ft_pexit("DEBUG: Wrong logfile path");
}

void	debug_cmd(t_cmd *cmd, char *label)
{
	int		o;
	char	*before;
	char	*after;
	int		len;
	int		i;

	o = STDERR_FILENO;
	if (label == NULL)
		ft_fprintf(o, "╭─ cmd ─────────────────────────╮\n");
	else
		ft_fprintf(o, "╭─ %s ─────────────────────────╮\n", label);
	before = "│ • ";
	after = "\n";
	ft_fprintf(o, "%sargs: ", before);
	i = 0;
	if (cmd->args != NULL && cmd->args[0] != NULL)
	{
		while (cmd->args[i] != NULL)
		{
			ft_fprintf(o, "\"%s\"", cmd->args[i]);
			if (cmd->args[i + 1] != NULL)
				ft_fprintf(o, ", ");
			i++;
		}
	}
	else
		ft_fprintf(o, "%s", NULL);
	ft_fprintf(o, "%s", after);
	ft_fprintf(o, "%sinfile: %s%s", before, cmd->infile, after);
	ft_fprintf(o, "%soutfile: %s%s", before, cmd->outfile, after);
	ft_fprintf(o, "%sfds: ", before);
	ft_fprintf(o, "write=%d, ", cmd->pipe[1]);
	ft_fprintf(o, "read=%d", cmd->pipe[0]);
	ft_fprintf(o, "%s", after);
	ft_fprintf(o, "%sfdin: %d%s", before, cmd->fdin, after);
	ft_fprintf(o, "%sfdout: %d%s", before, cmd->fdout, after);
	ft_fprintf(o, "%spid: %d%s", before, cmd->pid, after);
	if (label == NULL)
		ft_fprintf(o, "╰───────────────────────────────╯\n");
	else
	{
		ft_fprintf(o, "╰────────────────────────────");
		len = ft_strlen(label);
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
	int		i;
	char	*a;
	t_cmd	*cmd;
	char	*title;

	cmd = cmd_lst;
	i = 0;
	while (cmd)
	{
		a = ft_itoa(i++);
		title = ft_strjoin("cmd", a);
		ft_free(1, &a);
		debug_cmd(cmd, title);
		ft_free(1, &title);
		if (cmd->next)
			ft_printf("\t\t▼\n");
		cmd = cmd->next;
	}
}

void	debug_process(int pid, int status)
{
	ft_fprintf(g_logfd, "[Process: pid=%d, status=%d]\n", pid,
		WEXITSTATUS(status));
}

void	debug_fd(char *label, int fd)
{
	int	o;
	int	flags;

	o = g_logfd;
	flags = fcntl(fd, F_GETFL);
	if (flags == -1)
		ft_fprintf(o, "➡ %s: fd=%d, status=%s\n", label, fd, strerror(errno));
	else
		ft_fprintf(o, "➡ %s: fd=%d, status=OK\n", label, fd);
}

void	debug_envvars(t_envvar *lst)
{
	int	fd;

	fd = STDERR_FILENO;
	ft_fprintf(fd, "╭────────────────────────────────╮\n");
	ft_fprintf(fd, "│ env. variables                 │\n");
	ft_fprintf(fd, "╰────────────────────────────────╯\n");
	while (lst)
	{
		ft_fprintf(fd, "'%s': '%s'\n", lst->name, lst->value);
		lst = lst->next;
	}
	ft_fprintf(fd, "────────────────────────────────────\n\n");
}

void	debug_envp(char **envp)
{
	int	fd;

	fd = STDERR_FILENO;
	ft_fprintf(fd, "╭────────────────────────────────╮\n");
	ft_fprintf(fd, "│ envp                           │\n");
	ft_fprintf(fd, "╰────────────────────────────────╯\n");
	while (*envp)
	{
		ft_fprintf(fd, "%s\n", *envp);
		envp++;
	}
	ft_fprintf(fd, "────────────────────────────────────\n\n");
}

void	debug_killed_process(t_cmd *cmd)
{
	int	fd;

	fd = STDERR_FILENO;
	ft_fprintf(fd, "[kill process %d]\n", cmd->pid);
}
