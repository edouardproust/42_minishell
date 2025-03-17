/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:54:49 by eproust           #+#    #+#             */
/*   Updated: 2024/09/17 13:41:42 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		ch;
	const char	*last;

	ch = (char)c;
	last = NULL;
	while (*s)
	{
		if (*s == ch)
			last = s;
		s++;
	}
	if (*s == ch)
		last = s;
	return ((char *)last);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char *str = "Hello world!";
	int c = 'l';

	printf("string: \"%s\"\n", str);
	printf("char: \'%c\'\n", c);
	printf("ft_strrchr: \"%s\"\n", ft_strrchr(str, c));
	printf("strrchr: \"%s\"\n", strrchr(str, c));	

	return (0);
}
*/
