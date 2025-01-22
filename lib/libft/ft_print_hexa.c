/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 02:06:45 by eproust           #+#    #+#             */
/*   Updated: 2024/12/20 16:30:01 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Print an unsigned int as an hexadecimal number in stdout.
 * 
 * Returns the amount of bytes written to the output, a negative int
 * otherwise.
 *
 * Uses a buffer allocated string to insure to print either all the number
 * or nothing in case of `write` fn failure at any point of the process.
 */
ssize_t	ft_print_hexa(va_list arg_ptr, char specifier)
{
	unsigned int	nb;
	char			*str;
	ssize_t			bytes;

	nb = va_arg(arg_ptr, unsigned int);
	bytes = 0;
	if (specifier == 'x')
		str = ft_lutoa_base(nb, "0123456789abcdef");
	else
		str = ft_lutoa_base(nb, "0123456789ABCDEF");
	bytes = ft_putstr_fd(str, 1);
	free(str);
	return (bytes);
}
