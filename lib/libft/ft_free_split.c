/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:31:01 by eproust           #+#    #+#             */
/*   Updated: 2025/01/30 13:20:08 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Frees a 2D array of pointers (e.g. an array of strings char**).
 * The array must be NULL-terminated.
 */
void	ft_free_split(char ***array)
{
	char	**element;

	if (!array || !*array)
		return ;
	element =  *array;
	while (*element)
	{
		free(*element);
		*element = NULL;
		element++;
	}
	free(*array);
	*array = NULL;
}

/*
//cc -Werror -Wextra -Wall ft_free_split.c ft_split.c ft_substr.c ft_strdup.c ft_strlcpy.c ft_strlen.c ft_memcpy.c && ./a.out

#include <stdio.h>

int	main(void)
{
	char *s = "Hello world my name is Ed.";
	char **split = ft_split(s, ' ');
	int i = 0;
	while (split[i])
		printf("[%s]\n", split[i++]);
	ft_free_split(&split);
	return (0);
}
*/
