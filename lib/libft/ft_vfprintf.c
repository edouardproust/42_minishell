/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vfprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:49:00 by eproust           #+#    #+#             */
/*   Updated: 2025/02/01 21:15:03 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Dispatcher function.
 * 
 * Runs printing functions based on format specifier
 */
static ssize_t	print_conversion(int fd, char specifier, va_list arg_ptr)
{
	if (specifier == 'c')
		return (ft_print_char(arg_ptr, fd));
	if (specifier == 's')
		return (ft_print_str(arg_ptr, fd));
	if (specifier == 'd' || specifier == 'i')
		return (ft_print_int(arg_ptr, fd));
	if (specifier == 'u')
		return (ft_print_uint(arg_ptr, fd));
	if (specifier == 'x' || specifier == 'X')
		return (ft_print_hexa(arg_ptr, specifier, fd));
	if (specifier == 'p')
		return (ft_print_ptr(arg_ptr, fd));
	if (specifier == '%')
		return (write(fd, "%", 1));
	return (-1);
}

/*
 * Replicates usage of `vfprintf` function from stdlib.h
 *
 * Returns the amount of bytes written on the output or a negative number
 * in case of write failure at any point of the process.
 */

ssize_t	ft_vfprintf(int fd, const char *format, va_list arg_ptr)
{
	int		is_specifier;
	ssize_t	bytes;
	ssize_t	res;

	is_specifier = 0;
	bytes = 0;
	while (*format)
	{
		if (is_specifier)
		{
			is_specifier = 0;
			res = print_conversion(fd, *format, arg_ptr);
			if (res < 0)
				return (res);
			bytes += res;
		}
		else if (!is_specifier && *format == '%')
			is_specifier = 1;
		else
			bytes += write(fd, format, 1);
		format++;
	}
	return (bytes);
}
