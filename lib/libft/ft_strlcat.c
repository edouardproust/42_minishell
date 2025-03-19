/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:28:36 by eproust           #+#    #+#             */
/*   Updated: 2024/09/25 13:43:35 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dest_len;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dst);
	if (dest_len >= size)
		return (size + src_len);
	if (src_len < size - dest_len)
		ft_memcpy(dst + dest_len, src, src_len + 1);
	else
	{
		ft_memcpy(dst + dest_len, src, size - dest_len - 1);
		dst[size - 1] = '\0';
	}
	return (dest_len + src_len);
}

/*
#include <stdio.h>
#include <bsd/string.h>

int	main(void)
{
	char dest[40] = "Hello";
	char dest1[40] = "Hello";
	char *str = " world";

	size_t	res = ft_strlcat(dest, str, sizeof(dest));
	printf("ft_strlcat: '%s' (return: %zu)\n", dest, res);

	size_t	res1 = strlcat(dest1, str, sizeof(dest1));
	printf("ft_strlcat: '%s' (return: %zu)\n", dest1, res1);

	return (0);
}
*/
