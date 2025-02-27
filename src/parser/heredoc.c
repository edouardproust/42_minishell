#include "minishell.h"
/**
 * Generates a unique temporary file for heredoc and returns its fd.
 *
 * The function loops to find an available filename under `/tmp/` with the 
 * format "minishell_heredoc_<counter>". It ensures that the file does not 
 * already exist before opening it with exclusive permissions.
 *
 * @param tmp_file Buffer where the generated filename is stored.
 * @return File descriptor of the created file, or -1 on failure.
 */
static int	generate_unique_file(char *tmp_file)
{
	static int	counter;
	const char	*base;
	char		*num_str;
	int			fd;

	counter = 0;
	while (1)
	{
		num_str = ft_itoa(counter++);
		if (!num_str)
			return (1);
		base = "/tmp/minishell_heredoc_";
		ft_strlcpy(tmp_file, base, sizeof(base));
		ft_strlcat(tmp_file, num_str, 256);
		if (access(tmp_file, F_OK) == -1)
		{
			fd = open(tmp_file, O_WRONLY | O_CREAT | O_EXCL, 0600);
			if (fd != -1)
				return (fd);
		}
	}
}

/**
 * Processes the heredoc (`<<`) redirection by reading user input until 
 * the delimiter is encountered and storing it in a temporary file.
 *
 * Calls @generate_unique_file, reads input from the user
 * line by line, and writes each line to the file until the delimiter 
 * (heredoc_del) is reached. The temporary file is then set as the command's 
 * input file (infile).
 *
 * @param cmd Pointer to the cmd struct containing heredoc details.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int	process_heredoc(t_cmd *cmd)
{
	char	tmp_file[256];
	int		tmp_fd;
	char	*line;

	tmp_fd = generate_unique_file(tmp_file);
	if (tmp_fd == -1)
		return (EXIT_FAILURE);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, cmd->heredoc_del, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	close_fd(tmp_fd);
	cmd->infile = ft_strdup(tmp_file);
	cmd->heredoc_tmpfile = ft_strdup(tmp_file);
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
