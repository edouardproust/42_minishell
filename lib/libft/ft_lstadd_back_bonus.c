/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:08:20 by eproust           #+#    #+#             */
/*   Updated: 2024/09/25 12:09:58 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tail;

	tail = ft_lstlast(*lst);
	if (!tail)
		*lst = new;
	else
		tail->next = new;
}

/*
#include <stdio.h>

int	main(void)
{
	// Create list
	t_list *node1 = ft_lstnew("Node 1");
	t_list *node2 = ft_lstnew("Node 2");
	t_list *node3 = ft_lstnew("Node 3");
	t_list *node4 = ft_lstnew("Node 4");
	if (!node1 || !node2 || !node3 || !node4)
		return (1);
	ft_lstadd_back(&node1, node2);
	ft_lstadd_back(&node1, node3);
	ft_lstadd_back(&node1, node4);

	// Print list content + free nodes
	t_list *current = node1;
	t_list *next;
	while (current)
	{
		printf("'%s'\n", (char *)current->content);
		next = current->next;
		free(current);
		current = next;
	}

	return (0);
}
*/
