/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:49:00 by eproust           #+#    #+#             */
/*   Updated: 2025/02/01 21:16:12 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Replicates usage of `vprintf` function from stdlib.h
 *
 * Returns the amount of bytes written on the output or a negative number
 * in case of write failure at any point of the process.
 */

ssize_t	ft_vprintf(const char *format, va_list arg_ptr)
{
	return (ft_vfprintf(STDOUT_FILENO, format, arg_ptr));
}
