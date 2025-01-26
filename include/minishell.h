/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:49:19 by eproust           #+#    #+#             */
/*   Updated: 2025/01/26 19:35:07 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum {
    NODE_COMMAND,
    NODE_PIPELINE,
    NODE_REDIRECT,
} e_node_type;

typedef struct s_ast_node {
    e_node_type type;
    char **args;
    struct s_ast_node *left;
    struct s_ast_node *right;
    char *redirect_in;
    char *redirect_out;
} t_ast_node;

#endif
