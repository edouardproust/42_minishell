/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:52:06 by eproust           #+#    #+#             */
/*   Updated: 2024/09/17 19:07:44 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*cpy;
	size_t	len;

	len = ft_strlen(s);
	cpy = malloc(sizeof(char) * (len + 1));
	if (!cpy)
		return (NULL);
	ft_memcpy(cpy, s, len + 1);
	return (cpy);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char *s = "Hello, World!";

	printf("ft_strdup: \"%s\"\n", ft_strdup(s));
	printf("strdup: \"%s\"\n", strdup(s));

	return (0);
}
*/
