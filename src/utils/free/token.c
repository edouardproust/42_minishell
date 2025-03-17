#include "minishell.h"

/**
 * Frees all the tokens' value and structure in the token list.
 *
 * @param token_lst Pointer to the head of the list (by reference)
 * @return void
 */
void	free_token_lst(t_token **token_lst)
{
	t_token	*cur_token;
	t_token	*nxt_token;

	if (!token_lst || !*token_lst)
		return ;
	cur_token = *token_lst;
	while (cur_token)
	{
		ft_free(&cur_token->value);
		ft_free(&cur_token->original_value);
		nxt_token = cur_token->next;
		ft_free_ptr((void **)&cur_token);
		cur_token = nxt_token;
	}
	*token_lst = NULL;
}
