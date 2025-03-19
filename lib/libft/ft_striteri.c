/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:45:47 by eproust           #+#    #+#             */
/*   Updated: 2024/09/20 13:34:18 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}

/*
#include <stdio.h>

void	ft_redact_if(unsigned int i, char *str)
{
	if (i > 0 && *str != '@')
		*str = '*';
}

int	main(void)
{
	char str[20] = "test@gmail.com";

	printf("str: '%s'\n", str);
	ft_striteri(str, &ft_redact_if);
	printf("ft_strteri(str, f): '%s'\n", str);

	return (0);
}
*/
