/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:21:39 by eproust           #+#    #+#             */
/*   Updated: 2024/09/26 20:17:05 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (big[j + i] == little[j] && i + j < len)
			{
				if (little[j + 1] == '\0')
					return ((char *)big + i);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <bsd/string.h>

int	main(void)
{
	char *haystack = "Foo Bar Baz";
	char *needle = "Bar";
	size_t size = 8;

	printf("haystack: \"%s\"\n", haystack);
	printf("needle: \"%s\"\n", needle);
	printf("ft_strnstr: \"%s\"\n", ft_strnstr(haystack, needle, size));
	printf("strstr: \"%s\"\n", strnstr(haystack, needle, size));
}
*/
