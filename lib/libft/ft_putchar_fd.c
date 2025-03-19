/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:39:03 by eproust           #+#    #+#             */
/*   Updated: 2025/01/08 11:38:03 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

/*
#include <stdio.h>
#include <fcntl.h>

int	open_error()
{
	printf("Open error\n");
	return (1);
}

int	main(void)
{
	char c = 'A';
	char *filename = "test.txt";
	char buf[1024];

	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (open_error());
	ft_putchar_fd(c, fd);
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (open_error());
	int bytes_read = read(fd, buf, sizeof(buf));
	while (bytes_read > 0)
	{
		write(1, buf, bytes_read);
		bytes_read = read(fd, buf, sizeof(buf));
	}
	close(fd);

	return (0);
}
*/
