#include "minishell.h"

/**
 * Frees any pointer and sets it to NULL.
 *
 * @param ptr The address of the pointer to free.
 */
void	ft_free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

/**
 * Free minishell at any point during the program execution.
 *
 * @param minishell Struct containing global data on the program,
 * 	including lists of t_cmd, t_envvar, etc.
 * @return void
 */
void	free_minishell(t_minishell **ms)
{
	rl_clear_history();
	flush_fds();
	if (!ms || !*ms)
		return ;
	if ((*ms)->input)
		ft_free(&(*ms)->input);
	if ((*ms)->envp)
		ft_free_split(&(*ms)->envp);
	if ((*ms)->envvar_lst)
		free_envvar_lst(&(*ms)->envvar_lst);
	if ((*ms)->token_lst)
		free_token_lst(&(*ms)->token_lst);
	if ((*ms)->cmd_lst)
		free_cmd_lst(&(*ms)->cmd_lst);
	ft_free_ptr((void **)ms);
}
