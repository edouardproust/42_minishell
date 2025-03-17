/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lutoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:28:00 by eproust           #+#    #+#             */
/*   Updated: 2024/10/06 18:50:56 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_int(unsigned long n, size_t base_len)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n > 0)
	{
		count++;
		n /= base_len;
	}
	return (count);
}

char	*ft_lutoa_base(unsigned long n, char *base)
{
	char		*str;
	size_t		len;
	size_t		base_len;
	int			i;

	base_len = ft_strlen(base);
	len = count_int(n, base_len);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	str[0] = base[0];
	i = len - 1;
	while (n > 0)
	{
		str[i--] = base[n % base_len];
		n /= base_len;
	}
	return (str);
}

/*
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	int n = LONG_MAX;

	char *str = ft_itoa_base(n, "0123456789ABCDEF");
	printf("%s\n", str);
	free(str);

	return (0);
}
*/
