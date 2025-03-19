#include "minishell.h"

static int	read_heredoc_line(char *line, int write_fd,
	t_minishell *ms)
{
	char	*expanded_line;

	expanded_line = remove_quotes_and_expand(line, ms, FALSE);
	ft_free(&line);
	if (!expanded_line)
		return (EXIT_FAILURE);
	ft_putstr_fd(expanded_line, write_fd);
	ft_putstr_fd("\n", write_fd);
	ft_free(&expanded_line);
	return (EXIT_SUCCESS);
}

/**
 * Reads heredoc input until delimiter, writing to pipe.
 *
 * Reads the heredoc and writes each line to the write_fd descriptor.
 * The reading stops as soon as the delimiter (cmd->heredoc_del) is encountered.
 *
 * @param cmd Command structure containing delimiter
 * @param write_fd Pipe write end file descriptor
 * @param ms Struct containing data on the program
 * @return EXIT_SUCCESS on delimiter match, EXIT_FAILURE on error/EOF
 */
int	read_heredoc(t_cmd *cmd, int write_fd, t_minishell *ms)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (get_and_reset_signal() == SIGINT)
				return (ft_free(&line), E_SIGBASE + SIGINT);
			put_error2("warning: here-document at line %s delimited by "
				"end of file (wanted `%s')",
				int_to_str(cmd->heredoc->start),
				cmd->heredoc->delimiter);
			return (EXIT_SUCCESS);
		}
		if (ft_strcmp(line, cmd->heredoc->delimiter) == 0)
			return (ft_free(&line), EXIT_SUCCESS);
		if (read_heredoc_line(line, write_fd, ms) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
