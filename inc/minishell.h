#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h> 
# include <termios.h>

/****************************************/
/* Macros and Enums                     */
/****************************************/

# define FD_LIMIT 1024
# define TRUE 1
# define FALSE 0

enum	e_token
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
};

/* Exit codes */
# define E_CRITICAL 2
# define E_CMDWRONGARG 2
# define E_CMDNOTEXEC 126
# define E_CMDNOTFOUND 127
# define E_SIGBASE 128
# define E_ERRMAX 255

/****************************************/
/* Structs and Typedefs                 */
/****************************************/

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
	char			*heredoc_del;
	int				heredoc_fd;
	int				append;
	int				*pipe;
	int				saved_stdin;
	int				fdin;
	int				saved_stdout;
	int				fdout;
	pid_t			pid;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minishell
{
	char			*input;
	char			**envp;
	t_envvar		*envvar_lst;
	t_token			*token_lst;
	t_cmd			*cmd_lst;
	sig_atomic_t	exit_code;
}	t_minishell;

typedef struct s_tokenize_op
{
	char	*pattern;
	int		type;
}	t_tokenize_op;

typedef struct s_parse_op
{
	int		type;
	void	(*handler)(t_token **, t_cmd **, t_minishell *);
}	t_parse_op;

typedef struct s_builtin
{
	char	*name;
	int		(*fn)(char **args, t_minishell *minishell);
}	t_builtin;

/****************************************/
/* Functions                            */
/****************************************/

/* Error handling */
void			set_errno(int err_no);
void			put_error_va(char *fmt, va_list args);
void			put_error(char *fmt, ...);

/* Memory */
void			free_minishell(t_minishell **minishell);
void			free_token_lst(t_token **token_lst);
t_envvar		*free_envvar_node(t_envvar **node);
void			free_envvar_lst(t_envvar **var_lst);
void			free_cmd_lst(t_cmd **cmd_lst);

/* Exit */
void			exit_minishell(int exit_code, t_minishell *minishell,
					char *fmt, ...);

/* Env */
char			*get_env_value(char *var_name, t_minishell *minishell);
t_envvar		*init_envvars(t_minishell *minishell);
t_bool			is_directory(char *path);
t_bool			is_path(char *s);
int				update_envp(t_minishell *minishell);
t_envvar		*envvar_new(char *var);
int				envvar_addoneback(t_envvar **lst, t_envvar *new);
int				envvar_deleteone(t_envvar **lst, t_envvar *node);
int				envvar_updateone(t_envvar *node, char *new_value);
t_envvar		*envvar_findbyname(t_envvar *lst, char *name);

/* Signals */
void			set_sigint_sigquit(__sighandler_t sigint_handler, __sighandler_t sigquit_handler);
void			rl_sigint_handler(int signal);
void			heredoc_sigint_handler(int signal);
void			exec_sigint_handler(int signal);
void			put_signal_message(int status);
void			kill_all_children(t_minishell *ms);
int				get_and_reset_signal(void);
t_bool			ft_signal(int signum, void (*handler)(int));

/* Parsing */
void			init_cmd_lst(t_minishell *minishell);
t_cmd			*cmd_new(t_cmd *prev_cmd);
void			add_arg_to_cmd(t_cmd *cmd, char *arg);
int				parse_tokens(t_minishell *minishell);
t_parse_op		*get_parse_ops(void);
int				process_heredoc(t_cmd *cmd, t_minishell *ms);
//int			process_all_heredocs(t_minishell *ms); //TODO
//void			cleanup_heredoc(t_minishell *ms); // TODO keep?
void			handle_token_type(t_token **cur_token, t_cmd **cur_cmd,
					t_minishell *minishell);
void			handle_redir_in(t_token **cur_token, t_cmd **cur_cmd,
					t_minishell *minishell);
void			handle_redir_out(t_token **cur_token, t_cmd **cur_cmd,
					t_minishell *minishell);
void			handle_word(t_token **cur_token, t_cmd **cur_cmd,
					t_minishell *minishell);
void			handle_pipe(t_token **cur_token, t_cmd **cur_cmd,
					t_minishell *minishell);
void			handle_redir_heredoc(t_token **cur_token, t_cmd **cur_cmd,
					t_minishell *minishell);
void			handle_redir_append(t_token **cur_token, t_cmd **cur_cmd,
					t_minishell *minishell);

/* Tokenization */
t_token			*tokenizer(t_minishell *minishell);
t_token			*token_new(char *value, int type);
t_tokenize_op	*get_tokenize_ops(void);
t_token			*handle_special_char(char *input, int *i);
t_token			*create_word_token(char *input, int *index,
					char *unmatched_quote);
t_token			*handle_token_creation(char *input, int *i,
					char *unmatched_quote);
int				handle_token_error(t_token **token_lst, char unmatched_quote,
					t_minishell *minishell);
void			token_addback(t_token **tokens, t_token *new);
int				skip_quotes(char *input, int *index, char *unmatched_quote);
char			*remove_quotes(char *str);

/* Execute */
void			execute_cmd_lst(t_minishell *minishell);
char			*get_exec_path(char *arg, t_minishell *minishell);
pid_t			run_in_child_process(t_builtin *builtin, t_cmd *cmd,
					t_minishell *minishell);
int				setup_redirections(t_cmd *cmd);
int				setup_heredoc_redirection(t_cmd *cmd);

/* Pipes and redirections */
void			init_pipe_if(t_cmd *cmd, t_minishell *minishell);
void			setup_pipe_ends(t_cmd *cmd, t_minishell *minishell);
void			close_pipe_if(t_cmd *cmd);
int				setup_redirections(t_cmd *cmd);
void			save_stdin_stdout(t_cmd *cmd, t_minishell *minishell);
void			restore_stdin_stdout(t_cmd *cmd, t_minishell *minishell);

/* Executables */
void			run_executable(t_cmd *cmd, t_minishell *minishell);
void			setup_pipe_ends(t_cmd *cmd, t_minishell *minishell);
void			close_pipe_if(t_cmd *cmd);

/* Builtins */
t_builtin		*get_builtin(t_cmd *cmd);
void			run_builtin(t_bool in_child_process, t_builtin *builtin,
					char **args, t_minishell *minishell);
int				do_echo(char **args, t_minishell *minishell);
int				do_cd(char **args, t_minishell *minishell);
int				do_pwd(char **args, t_minishell *minishell);
int				do_export(char **args, t_minishell *minishell);
int				do_unset(char **args, t_minishell *minishell);
int				do_env(char **args, t_minishell *minishell);
int				do_exit(char **args, t_minishell *minishell);

/* File descriptors */
int				ft_dup(int src_fd, int *dst_fd);
int				ft_dup2(int oldfd, int newfd);
void			ft_close(int *fd);
void			flush_fds(void);

/* Strings */
int				is_special_char(char c);
int				is_space_char(char c);
int				is_quote_char(char c);
void			skip_whitespaces(char *input, int *i);

#endif