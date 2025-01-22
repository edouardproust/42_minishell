/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:08:56 by eproust           #+#    #+#             */
/*   Updated: 2024/09/25 12:08:57 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}

/*
#include <stdio.h>
#include <string.h>

static void	del_content(void *content)
{
    if (content)
	{
		printf("Deleting content: '%s'...\n", (char *)content);
		free(content);
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

	// Delete node2 + relink
    ft_lstdelone(node2, del_content);
	node1->next = node3;

	// print result + free list
	printf("\nNew list:\n");
    t_list *current = node1;
	t_list *next;
    while (current)
    {
        printf("%s\n", (char *)current->content);
        next = current->next;
		free(current);
		current = next;
    }
    return 0;
}
*/
