/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:08:33 by eproust           #+#    #+#             */
/*   Updated: 2024/09/25 12:08:35 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

/*
#include <stdio.h>

int	main(void)
{
	// Build list of 3 nodes
	t_list *node1 = ft_lstnew("Node 1");
	t_list *node2 = ft_lstnew("Node 2");
	t_list *node3 = ft_lstnew("Node 3");
	if (!node1 || !node2 || !node3)
		return (1);
	node1->next = node2;
	node2->next = node3;

	// Add new node in front
	t_list *head = ft_lstnew("Head");
	if (!head)
		return (1);
	ft_lstadd_front(&node1, head);

	// Print list
	t_list *current = node1;
	t_list *next;
	while(current)
	{
		printf("'%s'\n", (char *)current->content);
		next = current->next;
		free(current);
		current = next;	
	}
	return (0);
}
*/
