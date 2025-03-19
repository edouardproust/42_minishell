/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:00:15 by eproust           #+#    #+#             */
/*   Updated: 2024/09/17 13:10:07 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	char c = 'A';

	printf("ft_isalpha: %s\n", ft_isalpha(c) ? "Yes" : "No");
	printf("isalpha: %s\n", isalpha(c) ? "Yes" : "No");

	return (0);
}
*/
