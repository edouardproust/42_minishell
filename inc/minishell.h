#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

#define TRUE 1
#define FALSE 0
typedef int t_bool;

typedef struct s_cmd {
	char			**args;
	char			*infile;
	char			*outfile;
	int				*pipe;
	int				fdin;
	int				fdout;
	struct s_cmd	*prev;
	struct s_cmd	*next;
} t_cmd;

// execute.c
void	execute_cmd_lst(t_cmd **cmd_lst, char **envp);
char    *get_exec_path(char *arg, t_cmd **cmd_lst);

// exit.c
void	exit_parsing(t_cmd **foo, char *fmt, ...); // TODO (Ava) Edit function in exit.c
void	exit_exec(t_cmd **head, char *fmt, ...);

// free.c
t_cmd	*free_cmd(t_cmd **cmd);
void	free_cmd_lst(t_cmd **cmd_lst);

// debug.c (TODO Delete these lines + debug.c before submit)
t_cmd	*create_cmd_lst(void);
void	debug_cmd_lst(t_cmd *cmd_lst);
void	debug_cmd(t_cmd *cmd, char *title);
void	debug_fd(char *label, int fd);
void	debug_read_fd(char *label, int fd);

#endif
