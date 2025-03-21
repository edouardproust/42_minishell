#include "minishell.h"
#include <sys/stat.h>

int	g_logfd = -1;

static t_cmd	*cmd_new_addback(char *bash_cmd,
	t_cmd *prev_cmd)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->args = NULL;
	cmd->infiles = NULL;
	cmd->outfiles = NULL;
	cmd->pipe = NULL;
	cmd->fdin = STDIN_FILENO;
	cmd->fdout = STDOUT_FILENO;
	cmd->prev = prev_cmd;
	cmd->next = NULL;
	cmd->pid = 0;
	cmd->args = ft_split(bash_cmd, ' ');
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

	cmd0 = cmd_new_addback("tail -n +4", NULL);
	cmd1 = cmd_new_addback("grep a", cmd0);
	cmd2 = cmd_new_addback("sort", cmd1);
	cmd3 = cmd_new_addback("uniq -c", cmd2);
	cmd4 = cmd_new_addback("sort -nr", cmd3);
	cmd_new_addback("head -n 3", cmd4);
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

static void	debug_cmd_args(FILE *o, t_cmd *cmd, char *before, char *after)
{
	int	i;

	fprintf(o, "%sargs: ", before);
	i = 0;
	if (cmd->args != NULL && cmd->args[0] != NULL)
	{
		while (cmd->args[i] != NULL)
		{
			fprintf(o, "\"%s\"", cmd->args[i]);
			if (cmd->args[i + 1] != NULL)
				fprintf(o, ", ");
			i++;
		}
	}
	else
		fprintf(o, "%p", NULL);
	fprintf(o, "%s", after);
}

static void	debug_cmd_infiles(FILE *o, t_cmd *cmd, char *before)
{
	t_infile	*in;
	int			i;

	fprintf(o, "%sinfiles: ", before);
	if (cmd->infiles == NULL)
		fprintf(o, "%p", NULL);
	else
	{
		i = 0;
		while (cmd->infiles[i])
		{
			in = cmd->infiles[i];
			fprintf(o, "\n│   • ");
			fprintf(o, "filepath: ");
			if (in->filepath)
				fprintf(o, "\"%s\"", in->filepath);
			else
				fprintf(o, "(null)");
			fprintf(o, ", is_heredoc: %s", in->is_heredoc == TRUE
				? "true" : "false");
			fprintf(o, ", hdoc_delimiter: ");
			if (in->hdoc_delimiter)
				fprintf(o, "\"%s\"", in->hdoc_delimiter);
			else
				fprintf(o, "(null)");
			fprintf(o, ", hdoc_fd: %d", in->hdoc_fd);
			fprintf(o, ", hdoc_start: %d", in->hdoc_start);
			i++;
		}
	}
	fprintf(o, "\n");
}

static void	debug_cmd_outfiles(FILE *o, t_cmd *cmd, char *before)
{
	t_outfile	*out;
	int			i;

	fprintf(o, "%soutfiles: ", before);
	if (cmd->outfiles == NULL)
		fprintf(o, "%p", NULL);
	else
	{
		i = 0;
		while (cmd->outfiles[i])
		{
			out = cmd->outfiles[i];
			fprintf(o, "\n│   • ");
			fprintf(o, "filepath: ");
			if (out->filepath)
				fprintf(o, "\"%s\"", out->filepath);
			else
				fprintf(o, "(null)");
			fprintf(o, ", append: %s", out->append == TRUE
				? "true" : "false");
			i++;
		}
	}
	fprintf(o, "\n");
}

void	debug_cmd(t_cmd *cmd, char *label)
{
	FILE	*o;
	char	*before;
	char	*after;
	int		len;

	o = stderr;
	if (label == NULL)
		fprintf(o, "╭─ cmd ─────────────────────────╮\n");
	else
		fprintf(o, "╭─ %s ─────────────────────────╮\n", label);
	before = "│ • ";
	after = "\n";
	debug_cmd_args(o, cmd, before, after);
	debug_cmd_infiles(o, cmd, before);
	debug_cmd_outfiles(o, cmd, before);
	fprintf(o, "%sfds: ", before);
	fprintf(o, "write=%d, ", cmd->pipe[1]);
	fprintf(o, "read=%d", cmd->pipe[0]);
	fprintf(o, "%s", after);
	fprintf(o, "%sfdin: %d%s", before, cmd->fdin, after);
	fprintf(o, "%sfdout: %d%s", before, cmd->fdout, after);
	fprintf(o, "%spid: %d%s", before, cmd->pid, after);
	if (label == NULL)
		fprintf(o, "╰───────────────────────────────╯\n");
	else
	{
		fprintf(o, "╰────────────────────────────");
		len = ft_strlen(label);
		while (len > 0)
		{
			fprintf(o, "─");
			len--;
		}
		fprintf(o, "╯\n");
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
		ft_free(&a);
		debug_cmd(cmd, title);
		ft_free(&title);
		if (cmd->next)
			printf("\t\t▼\n");
		cmd = cmd->next;
	}
}

void	debug_process(int pid, int status)
{
	fprintf(stderr, "[Process: pid=%d, status=%d]\n", pid,
		WEXITSTATUS(status));
}

void	debug_fd(char *label, int fd)
{
	FILE	*o;
	int		flags;

	o = stderr;
	flags = fcntl(fd, F_GETFL);
	if (flags == -1)
		fprintf(o, "➡ %s: fd=%d, status=%s\n", label, fd, strerror(errno));
	else
		fprintf(o, "➡ %s: fd=%d, status=OK\n", label, fd);
}

void	debug_envvars(t_envvar *lst)
{
	FILE	*o;

	o = stderr;
	fprintf(o, "╭────────────────────────────────╮\n");
	fprintf(o, "│ env. variables                 │\n");
	fprintf(o, "╰────────────────────────────────╯\n");
	while (lst)
	{
		fprintf(o, "'%s': '%s'\n", lst->name, lst->value);
		lst = lst->next;
	}
	fprintf(o, "────────────────────────────────────\n\n");
}

void	debug_envp(char **envp)
{
	FILE	*o;

	o = stderr;
	fprintf(o, "╭────────────────────────────────╮\n");
	fprintf(o, "│ envp                           │\n");
	fprintf(o, "╰────────────────────────────────╯\n");
	while (*envp)
	{
		fprintf(o, "%s\n", *envp);
		envp++;
	}
	fprintf(o, "────────────────────────────────────\n\n");
}

void	debug_killed_process(t_cmd *cmd)
{
	FILE	*o;

	o = stderr;
	fprintf(o, "[kill process %d]\n", cmd->pid);
}
