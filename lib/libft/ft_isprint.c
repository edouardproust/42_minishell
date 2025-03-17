/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:02:18 by eproust           #+#    #+#             */
/*   Updated: 2024/09/17 13:13:16 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	return (32 <= c && c <= 126);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	char c = '\n';

	printf("ft_isprint: %s\n", ft_isprint(c) ? "Yes" : "No");
	printf("isprint: %s\n", isprint(c) ? "Yes" : "No");

	return (0);
}
*/
