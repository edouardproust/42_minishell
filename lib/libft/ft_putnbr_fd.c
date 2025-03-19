/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:39:17 by eproust           #+#    #+#             */
/*   Updated: 2024/09/19 16:39:18 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	li;

	li = (long int)n;
	if (li < 0)
	{
		ft_putchar_fd('-', fd);
		li = -li;
	}
	if (li > 9)
		ft_putnbr_fd(li / 10, fd);
	ft_putchar_fd(li % 10 + '0', fd);
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
	int str = -2147483648; // INT_MAX = 2147483647 | INT_MIN = -2147483648
	char *filename = "test.txt";
	char buf[1024];

	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (open_error());
	ft_putnbr_fd(str, fd);
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
