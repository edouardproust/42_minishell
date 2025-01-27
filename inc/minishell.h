/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:49:19 by eproust           #+#    #+#             */
/*   Updated: 2025/01/27 16:45:23 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_cmd {
	char	**args;
	char	**infile;
	char	**outfile;
} t_cmd;

typedef struct s_node {
    t_cmd	*cmd;
	t_cmd	*next;
} t_node;

t_node	*init_struct(void); // TODO remove (created for test purpose)
int	execute_command(t_node *cmd);

#endif
