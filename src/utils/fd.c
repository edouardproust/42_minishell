/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:39:21 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:27 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Duplicates a file descriptor.
 *
 * @param src_fd Source file descriptor.
 * @param dst_fd Destination file descriptor.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int	ft_dup(int src_fd, int *dst_fd)
{
	*dst_fd = dup(src_fd);
	if (*dst_fd == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * Duplicates a file descriptor and closes the original.
 *
 * @param oldfd File descriptor to duplicate.
 * @param newfd Destination file descriptor.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int	ft_dup2(int oldfd, int newfd)
{
	if (oldfd == newfd)
		return (EXIT_SUCCESS);
	if (dup2(oldfd, newfd) == -1)
		return (EXIT_FAILURE);
	close(oldfd);
	return (EXIT_SUCCESS);
}

/**
 * Closes a file descriptor if it is not a standard one.
 * 
 * Sets the descriptor to -1 to indicate it is no longer valid.
 *
 * @param fd File descriptor to close.
 * @return void
 */
void	ft_close(int *fd)
{
	if (*fd != -1 && *fd > STDERR_FILENO)
	{
		close(*fd);
		*fd = -1;
	}
}

/**
 * Closes all file descriptors up to FD_LIMIT, except standard ones.
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
