#include "minishell.h"
/**
 * Processes a single split element from expanded value into token
 * - Duplicates split value to avoid dependency on split array
 * - Creates new token with proper original value tracking
 * - Handles all memory allocation failures with cleanup
 * @param split_val Current string from split array
 * @param orig Original token being split
 * @param head Head of new token list being built
 * @return 1 on success, 0 on memory failure
 */
static int	handle_split_element(char *split_val, t_token *orig, t_token **head)
{
	char	*val_copy;
	char	*orig_copy;
	t_token	*new;

	val_copy = ft_strdup(split_val);
	if (!val_copy)
		return (0);
	new = token_new(val_copy, TOKEN_WORD);
	if (!new)
		return (free(val_copy), 0);
	orig_copy = ft_strdup(orig->original_value);
	if (!orig_copy)
		return (free(val_copy), free(new), 0);
	new->original_value = orig_copy;
	new->was_quoted = 0;
	token_addback(head, new);
	return (1);
}

/**
 * Creates list of tokens from split array of expanded value
 * - Iterates through split results
 * - Delegates element processing to handle_split_element()
 * - Returns NULL if any element processing fails
 * @param split Result of ft_split() on expanded value
 * @param original Original token being split
 * @return Head of new token list or NULL on failure
 */
static t_token	*create_split_tokens(char **split, t_token *original)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (split && split[i])
	{
		if (!handle_split_element(split[i], original, &head))
		{
			if (head)
				free_token_lst(&head);
			return (NULL);
		}
		i++;
	}
	return (head);
}

/*
 * Splits unquoted tokens into multiple word tokens based on spaces
 * 1. Splits expanded value using ft_split()
 * 2. Creates new token list from split parts
 * 3. Always frees original token and split array
 */
t_token	*split_unquoted(t_token *orig_token, char *expanded_val)
{
	char	**split;
	t_token	*head;

	split = ft_split(expanded_val, ' ');
	head = create_split_tokens(split, orig_token);
	ft_free_split(&split);
	free_token_lst(&orig_token);
	return (head);
}
