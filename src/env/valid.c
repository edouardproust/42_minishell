/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:39:21 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:39:27 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if a string represents a relative or absolute path.
 *
 * The strings represents a path:
 * - if it start by: /, ./ or ../
 * - or if it contains a / anywhere
 *
 * @param s The string to check. If `NULL` or empty, returns `FALSE`.
 * @return t_bool `TRUE` if the string represents an path..
 */
t_bool	is_path(char *s)
{
	if (!s || s[0] == '\0')
		return (FALSE);
	if ((s[0] == '.' && s[1] == '/')
		|| (s[0] == '.' && s[1] == '.' && s[2] == '/'))
		return (TRUE);
	if (s[0] == '/')
		return (TRUE);
	if (ft_strchr(s, '/') != NULL)
		return (TRUE);
	return (FALSE);
}

/**
 * Checks if a path matches with an existing directory.
 *
 * @param s The path to check. If `NULL` or empty, returns `FALSE`.
 * @return t_bool `TRUE` if the path is a valid directory.
 */
t_bool	is_directory(char *path)
{
	struct stat	path_stat;
	int			res;

	if (!path || path[0] == '\0')
		return (FALSE);
	res = stat(path, &path_stat);
	if (res == 0 && S_ISDIR(path_stat.st_mode))
		return (TRUE);
	return (FALSE);
}

/**
 * Check if the given string corresponds to a valid envp variable.
 *
 * @param str The string to check
 * @return TRUE if is a valid envp variable, FALSE otherwise
 */
t_bool	is_valid_envp_var(char *str)
{
	if (!str || *str == '\0' || *str == '=' || ft_isdigit(*str))
		return (FALSE);
	while (*str && *str != '=')
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (FALSE);
		str++;
	}
	return (TRUE);
}
