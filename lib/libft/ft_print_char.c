/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:46:40 by eproust           #+#    #+#             */
/*   Updated: 2024/12/20 16:29:48 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Print a char in stdout.
 * 
 * Returns 1 in case of write success, or a negative int otherwise.
 */
ssize_t	ft_print_char(va_list arg_ptr)
{
	int	c;

	c = va_arg(arg_ptr, int);
	return (ft_putchar_fd(c, 1));
}
