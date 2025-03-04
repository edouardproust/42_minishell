/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:15:14 by eproust           #+#    #+#             */
/*   Updated: 2025/01/19 15:03:17 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_into_stash(int fd, char *buffer, char **stash)
{
	int		br;
	char	*new_stash;

	br = 1;
	while (!ft_strchr(*stash, '\n') && br != 0)
	{
		br = read(fd, buffer, BUFFER_SIZE);
		if (br < 0)
			return (ft_free(2, &buffer, stash));
		if (br > 0)
		{
			buffer[br] = '\0';
			new_stash = ft_strjoin(*stash, buffer);
			if (!new_stash)
				return (ft_free(2, &buffer, stash));
			free(*stash);
			*stash = new_stash;
		}
	}
	ft_free(1, &buffer);
	return (*stash);
}

static char	*extract_line_from_stash(char **stash)
{
	char	*line;
	int		i;

	i = 0;
	while ((*stash)[i] != '\n' && (*stash)[i] != '\0')
		i++;
	if ((*stash)[i] == '\0' && i > 0)
		i--;
	line = ft_substr(*stash, 0, i + 1);
	if (!line)
		return (ft_free(1, stash));
	if (ft_strlen(line) == 0)
		return (ft_free(2, &line, stash));
	return (line);
}

static char	*cleanup_stash_after_extract(char **stash, int line_len)
{
	char	*tmp;
	int		len;

	len = ft_strlen(*stash);
	if (len == line_len)
		return (ft_free(1, stash));
	tmp = ft_substr(*stash, line_len, len);
	ft_free(1, stash);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_free(1, &stash[fd]));
	buffer[0] = '\0';
	stash[fd] = read_into_stash(fd, buffer, &stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = extract_line_from_stash(&stash[fd]);
	if (!line)
		return (NULL);
	stash[fd] = cleanup_stash_after_extract(&stash[fd], ft_strlen(line));
	return (line);
}
