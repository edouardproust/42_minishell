/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:48:00 by eproust           #+#    #+#             */
/*   Updated: 2025/01/26 19:38:58 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
t_token	*tokenize(char *input)
{

}

t_ast_node	*parse(t_token *tokens)
{

}

int	execute(t_ast_node *ast)
{
	// Go throught the tree and create pipelines
	// Execute pipeline sub-commands + do needed redirections
		// check if is a bultin command
		// else use execve
}
*/

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell $");
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			ft_free_ptrs(1, &input);
			break;
		}
		add_history(input);
		//t_token *tokens = tokenize(input);
		free(input);
		//t_ast_node *ast = parse(input);
		//execute(ast);
	}
	return (EXIT_SUCCESS);
}
