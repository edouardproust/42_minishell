/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:21:29 by eproust           #+#    #+#             */
/*   Updated: 2024/09/27 19:09:12 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*us1;
	unsigned char	*us2;
	size_t			i;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (us1[i] && us1[i] == us2[i] && i < n - 1)
		i++;
	return (us1[i] - us2[i]);
}

/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char *s1 = "Hello";
	char *s2 = "Hello World";
	size_t bytes = 10;

	printf("s1: \"%s\"\n", s1);
	printf("s2: \"%s\"\n", s2);
	printf("ft_strncmp: %d\n", ft_strncmp(s1, s2, bytes));
	printf("strncmp: %d\n", strncmp(s1, s2, bytes));
}
*/
