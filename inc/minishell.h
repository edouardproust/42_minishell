#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_cmd {
	char	**args;
	int		pipe_after;
	int		pipe_before;
	char	*infile;
	char	*outfile;
	int		fdin;
	int		fdout;
} t_cmd;

typedef struct s_node {
    t_cmd			*cmd;
	struct s_node	*next;
} t_node;

#endif
