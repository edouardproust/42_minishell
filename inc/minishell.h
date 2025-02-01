#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

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
} t_node;

void	execute_input(t_node **parsed_input, char **envp);
char    *get_exec_path(char *arg, t_node **pinput);

void	exit_exec(t_node **parsed_input, char *fmt, ...);
void	free_pinput(t_node **pinput);

// TODO Debug functions to delete
t_node	*debug_init_pinput(void);
void	debug_pinput(t_node *pinput);
void	debug_cmd(t_cmd *cmd, char *title);
void	debug_fd(char *label, int fd);
void	debug_read_fd(char *label, int fd);

#endif
