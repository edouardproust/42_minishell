/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:47:21 by eproust           #+#    #+#             */
/*   Updated: 2024/12/20 16:30:19 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Print a signed integer in stdout.
 *
 * Returns the amount of bytes written to the output, a negative int
 * otherwise.
 *
 * Uses a buffer allocated string to insure to print either all the number
 * or nothing in case of `write` fn failure at any point of the process.
 */
ssize_t	ft_print_int(va_list arg_ptr)
{
	int		nb;
	char	*str;
	int		bytes;

	nb = va_arg(arg_ptr, int);
	str = ft_itoa(nb);
	bytes = ft_putstr_fd(str, 1);
	free(str);
	return (bytes);
}
