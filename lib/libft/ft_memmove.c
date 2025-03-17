/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:28:41 by eproust           #+#    #+#             */
/*   Updated: 2024/09/17 16:52:17 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (dest < src)
		ft_memcpy(d, s, n);
	else if (dest > src)
	{
		d += n - 1;
		s += n - 1;
		while (n--)
			*d-- = *s--;
	}
	return (dest);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char src1[20] = "Hello";
	char src2[20] = "Hello";
	int bytes_overlap = 3;
	char *dest1;
	char *dest2;

	printf("ft_memmove:\n");
	dest1 = (char *)ft_memmove(src1 + bytes_overlap, src1, 10);
	printf("- src: %s\n- dest: %s\n", src1, dest1);

	printf("\nmemmove:\n");
	dest2 = (char *)memmove(src2 + bytes_overlap, src2, 10);
	printf("- src: %s\n- dest: %s\n", src2, dest2);

	return (0);	
}
*/
