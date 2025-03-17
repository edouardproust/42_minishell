/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strglue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 02:51:48 by eproust           #+#    #+#             */
/*   Updated: 2025/02/14 02:51:50 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strglue(char *s1, char *glue, char *s2)
{
	char	*tmp;
	char	*glued;

	tmp = ft_strjoin(s1, glue);
	if (!tmp)
		return (NULL);
	glued = ft_strjoin(tmp, s2);
	ft_free(&tmp);
	if (!glued)
		return (NULL);
	return (glued);
}

/**
 * To compile:
 * `cc -Werror -Wall -Wextra ft_strglue.c ft_strjoin.c ft_free_ptrs.c
 * ft_strlen.c ft_strdup.c ft_memcpy.c && valgrind ./a.out`
 */
/*
#include <stdio.h>

int	main(void)
{
	char *glued = ft_strglue("hello", ", ", "world!");
	if (!glued)
		return (1);
	printf("%s\n", glued);
	 ft_free(&glued);
	return (0);
}
*/
