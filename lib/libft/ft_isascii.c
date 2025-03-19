/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:02:03 by eproust           #+#    #+#             */
/*   Updated: 2024/09/17 13:11:54 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	return (0 <= c && c <= 127);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	char c = 3;

	printf("ft_isascii: %s\n", ft_isascii(c) ? "Yes" : "No");
	printf("isascii: %s\n", isascii(c) ? "Yes" : "No");

	return (0);
}
*/
