#include "minishell.h"
/**
 * Generates a unique temporary file for heredoc input.
 *
 * Creates a file with the pattern `/tmp/minishell_heredoc_<counter>` where:
 * - `<counter>` is a static integer incremented for each heredoc
 * - File is created with exclusive access (O_EXCL Requires 
 *   that the file must not exist before opening)
 * - File permissions are 0600 (user read/write) for security 
 *
 * @param tmp_file Buffer where the generated filename is stored.
 * (minimum 256 bytes)
 * @return File descriptor of the created file, or -1 on failure.
 */
static int	generate_unique_file(char *tmp_file)
{
	static int	counter;
	const char	*base;
	char		*num_str;
	int			fd;

	while (1)
	{
		num_str = ft_itoa(counter++);
		if (!num_str)
			return (1);
		base = "/tmp/minishell_heredoc_";
		ft_strlcpy(tmp_file, base, 256);
		ft_strlcat(tmp_file, num_str, 256);
		ft_free(num_str);
		if (access(tmp_file, F_OK) == -1)
		{
			fd = open(tmp_file, O_WRONLY | O_CREAT | O_EXCL, 0600);
			if (fd != -1)
				return (fd);
		}
	}
}

/**
 * Reads user input for heredoc (<<) and writes it to the specified file.
 * 
 * Continuously reads input from the user until the heredoc delimiter 
 * (cmd->heredoc_del) is encountered. Each input line is written to the 
 * temporary file. If the delimiter is encountered, input stops.
 * 
 * @param tmp_fd File descriptor for the temporary heredoc file.
 * @param cmd Pointer to the command struct containing the heredoc delimiter.
 * @return EXIT_SUCCESS after successfully reading the heredoc input.
 */
static int	read_heredoc(int tmp_fd, t_cmd *cmd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, cmd->heredoc_del) == 0)
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	return (EXIT_SUCCESS);
}

/**
 * Processes the heredoc (<<) redirection by storing input to a tmp file.
 *
 * - Calls @generate_unique_file to create a temporary file
 * - Calls @read_heredoc in order to read input until delimiter is entered
 * - Stores file path in command structure
 *
 * @param cmd Pointer to the command struct containing heredoc details.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE if file creation or memory 
 * allocation fails.
 */
int	process_heredoc(t_cmd *cmd)
{
	char	tmp_file[256];
	int		tmp_fd;

	tmp_fd = generate_unique_file(tmp_file);
	if (tmp_fd == -1)
		return (EXIT_FAILURE);
	read_heredoc(tmp_fd, cmd);
	ft_close(&tmp_fd);
	cmd->infile = ft_strdup(tmp_file);
	cmd->heredoc_tmpfile = ft_strdup(tmp_file);
	if (!cmd->infile || !cmd->heredoc_tmpfile)
	{
		unlink(tmp_file);
		free(cmd->infile);
		free(cmd->heredoc_tmpfile);
		cmd->infile = NULL;
		cmd->heredoc_tmpfile = NULL;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * Processes heredoc (`<<`) redirections for all commands in the command list.
 *
 * Iterates through each command in `ms->cmd_lst`, checking if it has a 
 * heredoc delimiter (`heredoc_del`). If so, it calls process_heredoc.
 *
 * If any heredoc processing fails, `ms->exit_code` is set to EXIT_FAILURE.
 *
 * @param ms Pointer to the global Minishell structure.
 * @return EXIT_SUCCESS (failure is tracked in `ms->exit_code`).
 */
int	process_all_heredocs(t_minishell *ms)
{
	t_cmd	*cmd;

	cmd = ms->cmd_lst;
	while (cmd)
	{
		if (cmd->heredoc_del)
		{
			if (process_heredoc(cmd) != EXIT_SUCCESS)
				ms->exit_code = EXIT_FAILURE;
		}
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}

/*
 * Deletes heredoc_tmpfile and cleans up the relevant resources.
 */
void	cleanup_heredoc(t_minishell *ms)
{
	t_cmd	*cmd;

	cmd = ms->cmd_lst;
	while (cmd)
	{
		if (cmd->heredoc_tmpfile)
		{
			unlink(cmd->heredoc_tmpfile);
			free(cmd->heredoc_tmpfile);
			cmd->heredoc_tmpfile = NULL;
		}
		cmd = cmd->next;
	}
}
