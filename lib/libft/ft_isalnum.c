/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:01:17 by eproust           #+#    #+#             */
/*   Updated: 2024/09/17 13:07:24 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	char c = '&';

	printf("ft_isalnum: %s\n", ft_isalnum(c) ? "Yes" : "No");
	printf("isalnum: %s\n", isalnum(c) ? "Yes" : "No");

	return (0);
}
*/
