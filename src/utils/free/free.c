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