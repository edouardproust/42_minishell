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
    t_cmd			*cmd;
	struct s_node	*next;
} t_node;

t_node	*init_struct(void); // TODO remove (created for test purpose)
int	execute_command(t_node *cmd);

#endif
