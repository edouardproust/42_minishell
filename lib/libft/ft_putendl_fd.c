/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:39:48 by eproust           #+#    #+#             */
/*   Updated: 2024/09/19 16:39:50 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

/*
#include <stdio.h>

int	open_error()
{
	printf("Open error\n");
	return (1);
}

int	main(void)
{
	char *str = "Hello, World!";
	char *filename = "test.txt";
	char buf[1024];

	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (open_error());
	ft_putendl_fd(str, fd);
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
