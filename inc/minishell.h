#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

#include <stdio.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_cmd {
	char	**args;
	int		pipe_after;
	char	*infile;
	char	*outfile;
	int		fdin;
	int		fdout;
} t_cmd;

typedef struct s_node {
    t_cmd			*cmd;
	struct s_node	*next;
	int				pipe_after;
} t_node;

void	execute_input(t_node *parsed_input);

// list_utils
//int list_len(t_list *lst)

// TODO (E) Delete follwoing lines (functions created for testing execute.c)
t_node	*exec_init_struct(void);
void	exec_print_cmd_input(t_node *cmds);

#endif
