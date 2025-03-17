/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:56:09 by eproust           #+#    #+#             */
/*   Updated: 2024/09/27 19:32:23 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	if (!dest && !src)
		return (dest);
	while (n--)
		*d++ = *s++;
	return (dest);
}

/*
#include <stdio.h>
#include <string.h>

int main()
{
	char src[] = "Hello World!";
	char dest1[20];
	char dest2[20];

	printf("src: %s\n", src);
	ft_memcpy(src + 2, src, 8);
	printf("ft_memcpy: '%s'\n", dest1);
	memcpy(src + 2, src, 8);
	printf("memcpy: '%s'\n", dest2);

    return 0;
}
*/
