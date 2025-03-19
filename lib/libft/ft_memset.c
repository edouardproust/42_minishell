/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:13:52 by eproust           #+#    #+#             */
/*   Updated: 2024/09/17 13:54:02 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	c = (unsigned char)c;
	i = 0;
	while (i < n)
		ptr[i++] = c;
	return (s);
}

/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char s1[10] = "Hello";
	char s2[10] = "Hello";

	printf("ft_memset:\n");
	printf("Before: \"%s\"\n", s1);
	ft_memset(s1, 'A', strlen(s1));
	printf("After: \"%s\"\n", s1);

	printf("\nmemset:\n");
	printf("Before: \"%s\"\n", s2);
	memset(s2, 'A', strlen(s2));
	printf("After: \"%s\"\n", s2);

	return (0);
}
*/
