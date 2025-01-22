/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:49:54 by eproust           #+#    #+#             */
/*   Updated: 2024/12/20 16:31:09 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Print an unsigned integer in stdout.
 *
 * Returns the amount of bytes written to the output, a negative int
 * otherwise.
 *
 * Uses a buffer allocated string to insure to print either all the number
 * or nothing in case of `write` fn failure at any point of the process.
 */
ssize_t	ft_print_uint(va_list arg_ptr)
{
	unsigned int	nb;
	char			*str;
	ssize_t			bytes;

	nb = va_arg(arg_ptr, unsigned int);
	str = ft_lutoa_base(nb, "0123456789");
	bytes = ft_putstr_fd(str, 1);
	free(str);
	return (bytes);
}
