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

typedef struct s_envvar
{
	char*			name;
	char*			value;
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
void		exit_exec(int exit_code, t_cmd **head, char *fmt, ...);
void		set_errno(int err_no);
int			builtin_error(char *err_msg, ...);

/* Memory */
t_envvar	*free_envvar_node(t_envvar **node);
void		free_envvar_lst(t_envvar **var_lst);
void		free_cmd_lst(t_cmd **cmd_lst);
void		flush_fds(void);

/* Env */
t_envvar	*init_envvars(char **envp);
t_envvar	*envvar_new(char *var);
int			envvar_addoneback(t_envvar **lst, t_envvar *new);
int			envvar_deleteone(t_envvar **lst, t_envvar *node);
int			envvar_updateone(t_envvar *node, char *new_value);
t_envvar	*envvar_findbyname(t_envvar *lst, char *name);

/* Execute */
void		execute_cmd_lst(t_cmd **cmd_lst, char **envp);
char		*get_exec_path(char *arg, t_cmd **cmd_lst);
pid_t		run_in_child_process(t_builtin *builtin, t_cmd *cmd, char **envp,
				t_cmd **cmd_lst);

/* Executables */
void		run_executable(t_cmd *cmd, char **envp, t_cmd **cmd_lst);

/* Builtins */
t_builtin	*get_builtin(char *progname);
void		run_builtin(int in_child_process, t_builtin *builtin, char **args,
				t_cmd **cmd_lst);
int			do_echo(char **args);
int			do_cd(char **args);
int			do_pwd(char **args);
int			do_export(char **args);
int			do_unset(char **args);
int			do_env(char **args);
int			do_exit(char **args);

#endif /* MINISHELL_H */
