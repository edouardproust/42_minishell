#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# define FD_LIMIT 1024

enum e_token
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT
};

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				*pipe;
	int				fdin;
	int				fdout;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_builtin
{
	char	*name;
	void	(*fn)(char **args);
	int		affects_state;
} t_builtin;

// exit.c
void	exit_parsing(t_cmd **foo, char *fmt, ...); // TODO (Ava) Edit function in exit.c
void	exit_exec(t_cmd **head, char *fmt, ...);
void	exit_exec_code(int err_code, t_cmd **cmd_lst, char *fmt, ...);

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

// execute.c
void	execute_cmd_lst(t_cmd **cmd_lst, char **envp);
// execute_path.c
char    *get_exec_path(char *arg, t_cmd **cmd_lst);
// execute_builtins.c
t_builtin	*get_builtin(char *progname);
// execute/builtins
void exec_echo(char **args);
void exec_cd(char **args);
void exec_pwd(char **args);
void exec_export(char **args);
void exec_unset(char **args);
void exec_env(char **args);
void exec_exit(char **args);

#endif
