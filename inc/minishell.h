#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

#include <errno.h>
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

void	execute_input(t_node **parsed_input);
char    *get_exec_path(char *arg, t_node **pinput);

void	exit_exec(t_node **parsed_input, char *fmt, ...);
void	free_parsed_input(t_node **pinput);

// TODO (E) Delete follwoing lines (functions created for testing execute.c)
t_node	*exec_init_struct(void);
void	exec_print_cmd_input(t_node *cmds);

#endif
