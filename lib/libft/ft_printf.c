/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:49:00 by eproust           #+#    #+#             */
/*   Updated: 2024/12/20 16:29:27 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	print_conversion(char specifier, va_list arg_ptr);

/*
 * Replicates usage of `printf` function from stdlib.h
 *
 * Returns the amount of bytes written on the output or a negative number
 * in case of write failure at any point of the process.
 */
ssize_t	ft_printf(const char *format, ...)
{
	va_list	arg_ptr;
	int		is_specifier;
	ssize_t	bytes;
	ssize_t	res;

	va_start(arg_ptr, format);
	is_specifier = 0;
	bytes = 0;
	while (*format)
	{
		if (is_specifier)
		{
			is_specifier = 0;
			res = print_conversion(*format, arg_ptr);
			if (res < 0)
				return (res);
			bytes += res;
		}
		else if (!is_specifier && *format == '%')
			is_specifier = 1;
		else
			bytes += write(1, format, 1);
		format++;
	}
	return (bytes);
}

/*
 * Dispatcher function.
 * 
 * Runs printing functions based on format specifier
 */
static ssize_t	print_conversion(char specifier, va_list arg_ptr)
{
	if (specifier == 'c')
		return (ft_print_char(arg_ptr));
	if (specifier == 's')
		return (ft_print_str(arg_ptr));
	if (specifier == 'd' || specifier == 'i')
		return (ft_print_int(arg_ptr));
	if (specifier == 'u')
		return (ft_print_uint(arg_ptr));
	if (specifier == 'x' || specifier == 'X')
		return (ft_print_hexa(arg_ptr, specifier));
	if (specifier == 'p')
		return (ft_print_ptr(arg_ptr));
	if (specifier == '%')
		return (write(1, "%", 1));
	return (-1);
}
