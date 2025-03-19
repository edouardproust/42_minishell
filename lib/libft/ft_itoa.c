/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:28:00 by eproust           #+#    #+#             */
/*   Updated: 2024/09/25 16:34:51 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_int(long n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	int		i;
	long	nb;

	nb = (long)n;
	len = ft_count_int(nb);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	i = len - 1;
	while (nb > 0)
	{
		str[i] = nb % 10 + '0';
		nb /= 10;
		i--;
	}
	str[len] = '\0';
	return (str);
}

/*
#include <stdio.h>

int	main(void)
{
	int n = -2147483648; // INT_MIN = -2147483648, INT_MAX = 2147483647

	char *str = ft_itoa(n);	
	printf("%s\n", str);
	free(str);

	return (0);
}
*/
