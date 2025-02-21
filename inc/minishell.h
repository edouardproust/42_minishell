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

# define FD_LIMIT 1024

# define TRUE 1
# define FALSE 0

/* Exit codes */
# define E_CMDWRONGARG 2
# define E_CMDNOTEXEC 126
# define E_CMDNOTFOUND 127
# define E_SIGBASE 128
# define E_ERRMAX 255

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

typedef unsigned int	t_bool;

typedef struct s_envvar
{
	char			*name;
	char			*value;
	struct s_envvar	*prev;
	struct s_envvar	*next;
}	t_envvar;

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
	pid_t			pid;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minishell
{
	t_cmd		*cmd_lst;
	char		**envp;
	t_envvar	*envvar_lst;
}	t_minishell;

typedef struct s_builtin
{
	char	*name;
	int		(*fn)(char **args, t_minishell *minishell);
	int		affects_state;
}	t_builtin;

/****************************************/
/* Functions                            */
/****************************************/

/* Error handling */
void		set_errno(int err_no);
void		put_error_va(char *fmt, va_list args);
void		put_error(char *fmt, ...);

/* Memory */
void		free_minishell(t_minishell *minishell);
t_envvar	*free_envvar_node(t_envvar **node);
void		free_envvar_lst(t_envvar **var_lst);
void		free_cmd_lst(t_cmd **cmd_lst);
void		flush_fds(void);

/* Exit */
void		exit_minishell(int exit_code, t_minishell *minishell,
				char *fmt, ...);

/* Env */
char		*get_env_value(char *var_name, t_minishell *minishell);
t_envvar	*init_envvars(t_minishell *minishell);
int			update_envp(t_minishell *minishell);
t_envvar	*envvar_new(char *var);
int			envvar_addoneback(t_envvar **lst, t_envvar *new);
int			envvar_deleteone(t_envvar **lst, t_envvar *node);
int			envvar_updateone(t_envvar *node, char *new_value);
t_envvar	*envvar_findbyname(t_envvar *lst, char *name);

/* Execute */
void		execute_cmd_lst(t_minishell *minishell);
char		*get_exec_path(char *arg, t_minishell *minishell);
pid_t		run_in_child_process(t_builtin *builtin, t_cmd *cmd,
				t_minishell *minishell);

/* Executables */
void		run_executable(t_cmd *cmd, t_minishell *minishell);

/* Builtins */
t_builtin	*get_builtin(char *progname);
void		run_builtin(t_bool in_child_process, t_builtin *builtin, char **args,
				t_minishell *minishell);
int			do_echo(char **args, t_minishell *minishell);
int			do_cd(char **args, t_minishell *minishell);
int			do_pwd(char **args, t_minishell *minishell);
int			do_export(char **args, t_minishell *minishell);
int			do_unset(char **args, t_minishell *minishell);
int			do_env(char **args, t_minishell *minishell);
int			do_exit(char **args, t_minishell *minishell);

#endif
