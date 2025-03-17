/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:42:57 by eproust           #+#    #+#             */
/*   Updated: 2024/09/20 12:45:58 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*cpy;
	unsigned int	i;

	cpy = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (s[i])
	{
		cpy[i] = f(i, s[i]);
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

/*
#include <stdio.h>

char ft_redact_char_if(unsigned int i, char c)
{
	static int seen_at = 0;
	static int seen_dot = 0;

	if (c == '@')
		seen_at = 1;
	else if (seen_at && c == '.')
		seen_dot = 1;
	if (i > 0 && !seen_at)
		c = '*';
	if (seen_at && !seen_dot && c != '@')
		c = '*';

	return (c);
}


int	main(void)
{
	char *str = "test@gmail.com";

	char *cpy = ft_strmapi(str, &ft_redact_char_if);
	printf("str: '%s'\n", str);
	printf("ft_strmapi(str, f): '%s'\n", cpy);

	return (0);
}
*/
