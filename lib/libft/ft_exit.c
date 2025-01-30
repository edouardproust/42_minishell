/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:22:23 by eproust           #+#    #+#             */
/*   Updated: 2025/01/30 15:03:36 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_exit(char *error_msg)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(EXIT_FAILURE);
}
