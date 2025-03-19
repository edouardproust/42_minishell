/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:59:00 by eproust           #+#    #+#             */
/*   Updated: 2024/09/19 19:17:14 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_inset(char c, char const *set)
{
	while (*set)
	{
		if (*set++ == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trimmed;

	start = 0;
	while (s[start] && ft_inset(s[start], set))
		start++;
	end = ft_strlen(s);
	while (end > start && ft_inset(s[end - 1], set))
		end--;
	trimmed = ft_substr(s, start, end - start);
	return (trimmed);
}

/*
#include <stdio.h>

int	main(void)
{
	char *s1 = "\t .Hello, .World!!!\n ";
	char *set = "\t\n !.";
	printf("%s\n", ft_strtrim(s1, set));
	return (0);
}
*/
