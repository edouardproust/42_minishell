/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:02:49 by eproust           #+#    #+#             */
/*   Updated: 2024/09/17 13:48:35 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if ('A' <= c && c <= 'Z')
		c += 'a' - 'A';
	return (c);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	int c = 'A';

	printf("\'%c\' -> \'%c\'\n", c, ft_tolower(c));
	printf("\'%c\' -> \'%c\'\n", c, tolower(c));

	return (0);
}
*/
