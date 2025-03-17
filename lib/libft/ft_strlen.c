/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:21:15 by eproust           #+#    #+#             */
/*   Updated: 2024/09/17 13:21:18 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char *str = "";

	printf("string: \"%s\"\n", str);
	printf("ft_strlen: %ld\n", ft_strlen(str));
	printf("strlen: %ld\n", strlen(str));
}
*/
