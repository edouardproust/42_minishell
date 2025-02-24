/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:37:41 by eproust           #+#    #+#             */
/*   Updated: 2025/02/10 20:37:48 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strchri(char *s, int c)
{
	char	ch;
	int		i;

	if (!s)
		return (-1);
	ch = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return (i);
		i++;
	}
	if (s[i] == ch)
		return (i);
	return (-1);
}

/*
#include <stdio.h>
int	main(void)
{
	char	*s = "LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:";
	char	c = '=';

	printf("s='%s'\nc='%c'\nindex=%d\n", s, c, ft_strchri(s, c));
}
*/
