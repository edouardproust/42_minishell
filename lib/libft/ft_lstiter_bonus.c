/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:09:06 by eproust           #+#    #+#             */
/*   Updated: 2024/09/25 12:09:07 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*current;

	current = lst;
	while (current)
	{
		f(current->content);
		current = current->next;
	}
}

/*
#include <stdio.h>
#include <string.h>

void	uppercase_content(void *content)
{
	char *cont = (char *)content;
	while (*cont)
	{
		if ('a' <= *cont && *cont <= 'z')
			*cont -= 32;
		cont++;
	}
}

int	main(void)
{
	// Create list
	t_list *node1 = ft_lstnew(strdup("Node 1"));
	t_list *node2 = ft_lstnew(strdup("Node 2"));
	t_list *node3 = ft_lstnew(strdup("Node 3"));
	if (!node1 || !node2 || !node3)
		return (1);
	ft_lstadd_back(&node1, node2);
	ft_lstadd_back(&node1, node3);

	// Uppercase content of all nodes
	ft_lstiter(node1, uppercase_content);

	// Print result + free nodes
	t_list *current = node1;
	t_list *next;
	while (current)
	{
		printf("'%s'\n", (char *)current->content);
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}

	return (0);
}
*/
