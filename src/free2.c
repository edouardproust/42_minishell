#include "minishell.h"

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
