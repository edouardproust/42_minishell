/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:02:35 by eproust           #+#    #+#             */
/*   Updated: 2024/09/25 12:46:11 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if ('a' <= c && c <= 'z')
		c -= 'a' - 'A';
	return (c);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	int c = 'a';

	printf("\'%c\' -> \'%c\'\n", c, ft_toupper(c));
	printf("\'%c\' -> \'%c\'\n", c, toupper(c));

	return (0);
}
*/
