#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

#define FD_LIMIT 1024

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
void	flush_fds(void);

// debug.c (TODO Delete these lines + debug.c before submit)
t_cmd	*create_cmd_lst(void);
void	debug_cmd_lst(t_cmd *cmd_lst);
void	debug_cmd(t_cmd *cmd, char *title);
void	debug_fd(char *label, int fd);
void	debug_read_fd(char *label, int fd);

#endif
