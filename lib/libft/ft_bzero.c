/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:44 by eproust           #+#    #+#             */
/*   Updated: 2024/09/17 13:03:47 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
		ptr[i++] = '\0';
}

/*
#include <stdio.h>
#include <strings.h>

int	main(void)
{
	char s1[10] = "Hello";
	char s2[10] = "Hello";

	printf("ft_bzero:\n");
	printf("Before: \"%s\"\n", s1);
	ft_bzero(s1, sizeof(s1));
	printf("After: \"%s\"\n", s1);

	printf("\nbzero:\n");
	printf("Before: \"%s\"\n", s2);
	bzero(s2, sizeof(s2));
	printf("After: \"%s\"\n", s2);

	return (0);
}
*/
