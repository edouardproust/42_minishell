#include "minishell.h"

/**
 * Close a file descriptor if it is not a standard one.
 * 
 * @param fd File descriptor
 * @return void
 */
void	close_fd(int fd)
{
	if (fd > STDERR_FILENO)
		close(fd);
}

/**
 * Close all file descriptors fd up to FD_LIMIT,
 * except standard ones.
 * 
 * @return void
 */
void	flush_fds(void)
{
	int	fd;

	fd = STDERR_FILENO + 1;
	while (fd < FD_LIMIT)
		close(fd++);
}