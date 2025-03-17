/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:08:50 by eproust           #+#    #+#             */
/*   Updated: 2024/09/25 17:49:17 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buf;
	size_t	total_size;

	if (size > 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	total_size = nmemb * size;
	buf = malloc(total_size);
	if (!buf)
		return (NULL);
	ft_bzero(buf, total_size);
	return (buf);
}

/*
#include <stdio.h>

int	main(void)
{
	size_t nmemb = 99999;
	size_t size = 9999;

	printf("ft_calloc: %p\n", ft_calloc(nmemb, size));
	printf("calloc: %p\n", calloc(nmemb, size));
	
	return (0);
}
*/
