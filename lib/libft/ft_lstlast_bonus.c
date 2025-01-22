/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:09:16 by eproust           #+#    #+#             */
/*   Updated: 2024/09/25 12:09:18 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}

/*
#include <stdio.h>

int	main(void)
{
	// Create list
	t_list *node1 = ft_lstnew("Node 1");
	t_list *node2 = ft_lstnew("Node 2");
	t_list *node3 = ft_lstnew("Node 3");;
	t_list *node4 = ft_lstnew("Node 4");
	if (!node1 || !node2 || !node3 || !node4)
		return (1);
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;

	// Print list size
	t_list *last_node = ft_lstlast(node1);
	printf("Last node content: '%s'\n", (char *)last_node->content);
	
	// Free memory
	t_list *current = node1;
	t_list *next;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}

	return (0);
}
*/
