/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:09:27 by eproust           #+#    #+#             */
/*   Updated: 2024/09/25 12:09:28 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*lst_cpy;
	t_list	*nod_cpy;

	current = lst;
	lst_cpy = NULL;
	while (current)
	{
		nod_cpy = ft_lstnew(f(current->content));
		if (!nod_cpy)
		{
			ft_lstclear(&lst_cpy, del);
			return (NULL);
		}
		ft_lstadd_back(&lst_cpy, nod_cpy);
		current = current->next;
	}
	return (lst_cpy);
}
