/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:13:28 by eproust           #+#    #+#             */
/*   Updated: 2024/09/17 13:13:33 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	ch;
	size_t			i;

	ptr = (unsigned char *)s;
	ch = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == ch)
			return (&ptr[i]);
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int c = '\t';
	char str[10] = "test	test";
	size_t	s = sizeof(str);

	printf("memory: \"%s\"\nint: \'%c\'\n", str, c);
	printf("ft_memchr:	%p\n", ft_memchr(str, c, s));
	printf("memchr:		%p\n", memchr(str, c, s));

	return (0);
}
*/
