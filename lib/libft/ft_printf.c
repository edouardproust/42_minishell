/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:49:00 by eproust           #+#    #+#             */
/*   Updated: 2025/02/01 21:09:08 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Replicates usage of `printf` function from stdlib.h
 *
 * Returns the amount of bytes written on the output or a negative number
 * in case of write failure at any point of the process.
 */
ssize_t	ft_printf(const char *format, ...)
{
	va_list	arg_ptr;
	ssize_t	bytes;

	va_start(arg_ptr, format);
	bytes = ft_vprintf(format, arg_ptr);
	va_end(arg_ptr);
	return (bytes);
}
