/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:27 by eproust           #+#    #+#             */
/*   Updated: 2024/12/02 05:08:05 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *nptr)
{
	int		sign;
	long	res;

	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	res = 0;
	while (ft_isdigit(*nptr))
	{
		res = res * 10 + *nptr - '0';
		nptr++;
	}
	return (res * sign);
}

/*
#include <stdio.h>
#include <stdlib.h>

void	main(void)
{
	char *str = "-0y45us";

	printf("string: \"%s\"\n", str);
	printf("ft_atol: %d\n", ft_atol(str));
	printf("atol: %d\n", atol(str));
}
*/
