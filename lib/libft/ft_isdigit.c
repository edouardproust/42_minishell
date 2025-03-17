/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:00:53 by eproust           #+#    #+#             */
/*   Updated: 2024/09/17 13:08:46 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	char c = '5';

	printf("ft_isdigit: %s\n", ft_isdigit(c) ? "Yes" : "No");
	printf("isdigit: %s\n", isdigit(c) ? "Yes" : "No");

	return (0);
}
*/
