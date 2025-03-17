#include "minishell.h"
/**
 * Handles tilde expansion for unquoted words starting with '~'.
 * - Checks quoting status and syntax validity
 * - Delegates to expand_tilde() for actual expansion
 * - Manages memory: frees original word if expansion succeeds
 * 
 * @param original_word Input word (may contain leading ~)
 * @param has_quotes 0 if unquoted, 1 if quoted
 * @param minishell Shell context for environment lookup
 * @return char* Expanded path or original word
 */
char	*handle_tilde_exp(char *original_word, int has_quotes,
	t_minishell *minishell)
{
	char	*expanded;

	if (has_quotes != 0)
		return (original_word);
	if (original_word[0] != '~'
		|| (original_word[1] && original_word[1] != '/'))
		return (original_word);
	expanded = expand_tilde(original_word, minishell);
	if (expanded)
		return (free(original_word), expanded);
	return (original_word);
}

/**
 * Performs tilde expansion by replacing ~ with home directory path.
 * - Only expands standalone ~ or ~/ prefixes
 * - Uses HOME environment variable
 * 
 * @param word Input string starting with ~
 * @param minishell Shell context for environment access
 * @return char* Newly allocated expanded path, or NULL if:
 *         - Invalid syntax
 *         - HOME unset
 * @note Caller must free returned string if not NULL
 */
char	*expand_tilde(char *word, t_minishell *minishell)
{
	char	*home_dir;
	char	*expanded;

	if (word[0] != '~' || (word[1] != '\0' && word[1] != '/'))
		return (NULL);
	home_dir = get_env_value("HOME", minishell);
	if (!home_dir)
		return (NULL);
	expanded = ft_strjoin(home_dir, word + 1);
	return (expanded);
}
