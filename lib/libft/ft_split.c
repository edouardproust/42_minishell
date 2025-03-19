/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:23:47 by eproust           #+#    #+#             */
/*   Updated: 2024/09/27 17:52:54 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_parts(char const *s, char sep)
{
	size_t	count;
	int		flag;

	count = 0;
	flag = 0;
	while (*s)
	{
		if (!flag && *s != sep)
		{
			flag = 1;
			count++;
		}
		if (flag && *s == sep)
			flag = 0;
		s++;
	}
	return (count);
}

static size_t	ft_partlen(char const *s, int i, char sep)
{
	size_t	len;

	len = 0;
	while (s[i] && s[i] != sep)
	{
		len++;
		i++;
	}
	return (len);
}

char	**ft_split(char const *s, char sep)
{
	char	**split;
	size_t	parts;
	size_t	part;
	size_t	part_len;
	int		i;

	parts = ft_count_parts(s, sep);
	split = malloc (sizeof(char *) * (parts + 1));
	if (!split)
		return (NULL);
	part = 0;
	i = 0;
	while (part < parts)
	{
		while (s[i] == sep)
			i++;
		part_len = ft_partlen(s, i, sep);
		split[part] = ft_substr(s, i, part_len);
		if (!split[part])
			return (ft_free_splitn(&split, part), NULL);
		part++;
		i += part_len;
	}
	split[part] = NULL;
	return (split);
}

/*
TEST COMMANDE IN VIM:
:w | !clear && cc % ft_substr.c ft_strlen.c ft_strdup.c ft_strlcpy.c 
ft_memcpy.c -Werror -Wall -Wextra -lbsd -fsanitize=address && ./a.out

#include <stdio.h>

int	main(void)
{
	char *str = "  Hello word my name is Ed  ";
	char sep = ' ';

	char **split = ft_split(str, sep);
	int i = 0;
	while (split[i])
	{
		printf("%s\n", split[i]);
		free(split[i]);
		i++;
	}
	free(split);
	return (0);
}
*/
