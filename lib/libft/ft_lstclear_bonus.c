/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:08:45 by eproust           #+#    #+#             */
/*   Updated: 2024/09/25 12:08:47 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	while (current)
	{
		next = current->next;
		ft_lstdelone(current, del);
		current = next;
	}
	*lst = NULL;
}

/*
#include <stdio.h>
#include <string.h>

void	delete_node(void *content)
{
	if (content)
	{
		printf("Deleting '%s'...\n", (char *)content);
		free(content);
	}
}

int	main(void)
{
	// create list
	t_list *node1 = ft_lstnew(strdup("Node 1"));
	t_list *node2 = ft_lstnew(strdup("Node 2"));
	t_list *node3 = ft_lstnew(strdup("Node 3"));
	t_list *node4 = ft_lstnew(strdup("Node 4"));
	t_list *node5 = ft_lstnew(strdup("Node 5"));
	if (!node1 || !node2 || !node3 || !node4 || !node5)
		return (1);
	ft_lstadd_back(&node1, node2);
	ft_lstadd_back(&node1, node3);
	ft_lstadd_back(&node1, node4);
	ft_lstadd_back(&node1, node5);

	// Clear from node3
	node2->next = NULL;
	ft_lstclear(&node3, delete_node);

	// Print list
	printf("\nResult:\n");
	t_list *current = node1;
	while (current)
	{
		printf("- %s\n", (char *)current->content);
		current = current->next;
	}

	// Free remaining nodes
	printf("\n");
	ft_lstclear(&node1, delete_node);

	return (0);
}
*/
