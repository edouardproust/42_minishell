/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpapadak <fpapadak@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:41:10 by fpapadak          #+#    #+#             */
/*   Updated: 2025/03/19 11:41:12 by fpapadak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * Processes a single split value into a new token
 * - Duplicates split value for isolation from original data
 * - Maintains original token's metadata for error contexts
 * - Handles memory allocation failures with proper cleanup
 * 
 * @param split_val Current substring from split operation
 * @param orig Original token being processed
 * @param head Head of temporary token list
 * @return int 1 on success, 0 on memory failure
 */
static int	handle_split_element(char *split_val, t_token *orig, t_token **head)
{
	t_token	*new;

	new = token_new(ft_strdup(split_val), TOKEN_WORD);
	if (!new)
		return (0);
	new->original_value = ft_strdup(orig->original_value);
	if (!new->original_value)
		return (free(new->value), free(new), 0);
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

/**
 * Splits unquoted tokens into multiple argument tokens
 * - Creates safe copy of expanded value for splitting
 * - Generates temporary tokens for command arguments
 * - Ensures proper memory cleanup of intermediate data
 * 
 * @param orig_token Original unquoted token
 * @param expanded_val Expanded string value to split
 * @return t_token* List of split tokens, NULL on failure
 */
t_token	*split_unquoted(t_token *orig_token, char *expanded_val)
{
	char	**split;
	t_token	*head;
	char	*value_copy;

	if (!expanded_val)
		return (NULL);
	value_copy = ft_strdup(expanded_val);
	if (!value_copy)
		return (NULL);
	split = ft_split(value_copy, ' ');
	free(value_copy);
	head = create_split_tokens(split, orig_token);
	ft_free_split(&split);
	return (head);
}
