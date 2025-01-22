/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:09:46 by eproust           #+#    #+#             */
/*   Updated: 2024/09/25 12:22:40 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*current;

	current = lst;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/*
#include <stdio.h>

int	main(void)
{
	t_list *node1 = ft_lstnew("Node 1");
	t_list *node2 = ft_lstnew("Node 2");
	t_list *node3 = ft_lstnew("Node 3");
	t_list *node4 = ft_lstnew("Node 4");
	t_list *node5 = ft_lstnew("Node 5");
	if (!node1 || !node2 || !node3 || !node4 || !node5)
		return (1);
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	printf("Nodes: %d\n", ft_lstsize(node1));
	return (0);
}
*/
