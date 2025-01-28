#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_cmd {
	char	**args;
	char	*infile;
	char	*outfile;
	int		pipe_after;
} t_cmd;

typedef struct s_node {
    t_cmd			*cmd;
	struct s_node	*next;
} t_node;

int	execute_input(t_node *parsed_input);

// list_utils
//int list_len(t_list *lst)

// TODO Delete follwoing lines (functions created for testing execute.c)
t_node	*exec_init_struct(void);
void	exec_print_cmd_input(t_node *cmds);

#endif
