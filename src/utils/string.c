/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:32:42 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:33:54 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Skips all leading whitespace characters in the input string.
 * Advances the `i` index to the next non-whitespace character.
 *
 * @param input The input string
 * @param i Pointer to the current index in the input string.
 * @return void
 */
void	skip_whitespaces(char *input, int *i)
{
	while (input[*i] == ' ' || (input[*i] >= 9 && input[*i] <= 13))
		(*i)++;
}

/**
 * Converts a character to a null-terminated string.
 *
 * @param c The character to convert.
 * @return A pointer to a static string representing the character.
 */
char	*char_to_str(char c)
{
	static char	str[2];

	str[0] = c;
	str[1] = '\0';
	return (str);
}

/**
 * Converts an integer to a string.
 *
 * Frees the result of ft_itoa immediately and returns a static buffer
 * to avoid memory leaks.
 *
 * @param n The integer to convert.
 * @param minishell Pointer to the minishell struct for cleanup on failure.
 * @return A pointer to a static string representing the integer.
 */
char	*int_to_str(int n)
{
	static char	buf[12];
	char		*tmp;

	tmp = ft_itoa(n);
	if (!tmp)
		return (NULL);
	ft_strlcpy(buf, tmp, sizeof(buf));
	free(tmp);
	return (buf);
}
