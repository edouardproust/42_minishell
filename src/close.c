#include "minishell.h"

void	close_fd(int fd)
{
	if (fd > STDERR_FILENO)
		close(fd);
}

/**
 * Close any fd up to FD_LIMIT, except standard ones.
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
