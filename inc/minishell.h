#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

/****************************************/
/* Macros                               */
/****************************************/

# ifndef DEBUG
#  define DEBUG 0
# endif
# define FD_LIMIT 1024

/* Exit codes */
# define E_CMDNOTEXEC 126
# define E_CMDNOTFOUND 127
# define E_SIG 128

/****************************************/
/* Enums, Typedefs and Structs          */
/****************************************/

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
	int		(*fn)(char **args);
	int		affects_state;
}	t_builtin;

/****************************************/
/* Functions                            */
/****************************************/

/* Error handling and exit */
void		exit_parsing(t_cmd **foo, char *fmt, ...); // TODO (Ava) Edit function in exit.c
void		exit_exec(t_cmd **head, char *fmt, ...);

/* Memory */
t_cmd		*free_cmd(t_cmd **cmd);
void		free_cmd_lst(t_cmd **cmd_lst);
void		flush_fds(void);

/* Execute */
void		execute_cmd_lst(t_cmd **cmd_lst, char **envp);
char		*get_exec_path(char *arg, t_cmd **cmd_lst);
void		run_in_child_process(t_builtin *builtin, t_cmd *cmd, char **envp,
				t_cmd **cmd_lst);

/* Executables */
void	run_executable(t_cmd *cmd, char **envp, t_cmd **cmd_lst);

/* Builtins */
t_builtin	*get_builtin(char *progname);
void		run_builtin(t_builtin *builtin, char **args, t_cmd **cmd_lst);
int			do_echo(char **args);
int			do_cd(char **args);
int			do_pwd(char **args);
int			do_export(char **args);
int			do_unset(char **args);
int			do_env(char **args);
int			do_exit(char **args);

/* Debug */
t_cmd		*create_cmd_lst(void);
void		debug_cmd_lst(t_cmd *cmd_lst);
void		debug_cmd(t_cmd *cmd, char *title);
void		debug_fd(char *label, int fd);
void		debug_read_fd(char *label, int fd);

#endif /* MINISHELL_H */
