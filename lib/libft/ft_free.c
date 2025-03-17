/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:54:41 by eproust           #+#    #+#             */
/*   Updated: 2025/01/19 14:58:55 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Frees a string in a safe manner:
 * - Check that the input string is not NULL.
 * - Set the freed string to NULL.
 */
void	*ft_free(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

/*
int main()
{
    char	*test;

    test = ft_strdup("Hello");
	if (!test)
        return (1);
    printf("Before free: %s\n", test);
     ft_free(&test);
    printf("After free: %s\n", test);
    return (0);
}
*/
