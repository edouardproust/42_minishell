#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#define TOKEN_WORD 0
#define TOKEN_PIPE 1
#define TOKEN_REDIR_IN 2
#define TOKEN_REDIR_OUT 3

typedef struct s_token {
	char	*value;
	int		type;
	struct s_token *next;
} t_token;

typedef struct s_cmd {
	char	**args;
	int		pipe_after;
	int		pipe_before;
	char	*infile;
	char	*outfile;
	int		fdin;
	int		fdout;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_node {
    t_cmd			*cmd;
	struct s_node	*next;
} t_node;

#endif
