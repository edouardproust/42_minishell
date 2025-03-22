/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:32:42 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:33:54 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_outfile(t_outfile *outfile)
{
	int	flags;
	int	fdout;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (outfile->append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fdout = open(outfile->filepath, flags, 0644);
	return (fdout);
}

void	set_infile_fdin(t_cmd *cmd, t_infile *infile)
{
	if (infile->is_heredoc)
	{
		cmd->fdin = infile->hdoc_fd;
		if (cmd->fdin == -1)
			put_error("heredoc: invalid fd");
	}
	else
	{
		cmd->fdin = open(infile->filepath, O_RDONLY);
		if (cmd->fdin == -1)
			put_error1("%s", infile->filepath);
	}
}

int	duplicate_last_infile(t_cmd *cmd, t_infile *infile)
{
	if (ft_dup2(cmd->fdin, STDIN_FILENO) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	ft_close(&cmd->fdin);
	if (infile->is_heredoc)
	{
		infile->hdoc_fd = -1;
		return (put_error("heredoc: dup2"), EXIT_FAILURE);
	}
	else
		return (put_error1("%s: dup2", infile->filepath), EXIT_FAILURE);
}

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
int	read_heredoc(t_infile *infile, int write_fd, t_minishell *ms)
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
				int_to_str(infile->hdoc_start),
				infile->hdoc_delimiter);
			return (EXIT_SUCCESS);
		}
		if (ft_strcmp(line, infile->hdoc_delimiter) == 0)
			return (ft_free(&line), EXIT_SUCCESS);
		if (read_heredoc_line(line, write_fd, ms) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
