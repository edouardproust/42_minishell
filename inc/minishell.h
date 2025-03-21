/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust & fpapadak                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:07:30 by eproust           #+#    #+#             */
/*   Updated: 2025/02/16 20:07:31 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define E_PARSEREDIR 2
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
	char			*original_value;
	char			*value;
	int				type;
	int				was_quoted;
	struct s_token	*next;
}	t_token;

typedef struct s_infile
{
	char		*filepath;
	t_bool		is_heredoc;
	char		*hdoc_delimiter;
	int			hdoc_fd;
	int			hdoc_start;

}	t_infile;

typedef struct s_outfile
{
	char	*filepath;
	t_bool	append;
}	t_outfile;

typedef struct s_cmd
{
	char			**args;

	pid_t			pid;
	int				*pipe;
	int				saved_stdin;
	int				saved_stdout;

	int				fdin;
	int				fdout;
	t_infile		**infiles;
	t_outfile		**outfiles;

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
	int				input_line;
}	t_minishell;

typedef struct s_tokenize_op
{
	char	*pattern;
	int		type;
}	t_tokenize_op;

typedef struct s_expansion
{
	char	*cleaned;
	char	in_quote;
	int		buf_size;
	int		input_pos;
	int		output_pos;
}	t_expansion;

typedef struct s_parse_op
{
	int		type;
	int		(*handler)(t_token **, t_cmd **, t_minishell *);
}	t_parse_op;

typedef struct s_builtin
{
	char	*name;
	int		(*fn)(char **args, t_minishell *minishell);
}	t_builtin;

/****************************************/
/* Functions                            */
/****************************************/

/******** Initialization ********/
/* Env */
t_envvar		*init_envvars(t_minishell *minishell);
t_envvar		*envvar_new(char *var);
int				envvar_addoneback(t_envvar **lst, t_envvar *new);
int				envvar_deleteone(t_envvar **lst, t_envvar *node);
int				envvar_updateone(t_envvar *node, char *new_value);
char			*get_env_value(char *var_name, t_minishell *minishell);
int				envvar_lstsize(t_envvar *head);
t_envvar		*envvar_findbyname(t_envvar *lst, char *name);
char			*get_envp_var_identifier(char *var);
char			*get_envp_var_value(char *var);
int				update_envp(t_minishell *minishell);
t_bool			is_directory(char *path);
t_bool			is_path(char *s);
t_bool			is_valid_envp_var(char *var);
/* Signals */
void			rl_sigint_handler(int signal);
void			heredoc_sigint_handler(int signal);
void			exec_sigint_handler(int signal);
void			put_sigquit_message(int status, t_cmd *cmd);
void			kill_all_children(t_minishell *ms);
int				get_and_reset_signal(void);
t_bool			ft_signal(int signum, void (*handler)(int));

/******** Tokenization ********/
t_token			*tokenizer(t_minishell *minishell);
t_token			*token_new(char *value, int type);
t_tokenize_op	*get_tokenize_ops(void);
t_token			*handle_special_char(char *input, int *i);
t_token			*create_word_token(char *input, int *index,
					char *unmatched_quote, t_minishell *minishell);
t_token			*handle_token_creation(char *input, int *i,
					char *unmatched_quote, t_minishell *minishell);
int				handle_token_error(t_token **token_lst, char unmatched_quote,
					t_minishell *minishell);
void			token_addback(t_token **tokens, t_token *new);
int				skip_quotes(char *input, int *index, char *unmatched_quote);
int				process_quotes(char c, t_expansion *exp);
char			*remove_quotes_and_expand(char *str, t_minishell *minishell,
					t_bool remove_quotes);
char			*handle_tilde_exp(char *original_word, int has_quotes,
					t_minishell *minishell);
char			*expand_tilde(char *word, t_minishell *minishell);
t_token			*split_unquoted(t_token *orig_token, char *expanded_val);

/******** Parsing ********/
void			init_cmd_lst(t_minishell *minishell);
t_cmd			*cmd_new(t_cmd *prev_cmd);
void			add_arg_to_cmd(t_cmd *cmd, char *arg);
int				parse_tokens(t_minishell *minishell);
char			*redir_error(t_token *token);
int				check_redir_syntax(t_token *token, t_minishell *minishell);
int				check_ambiguous_redir(t_token *file_token,
					t_minishell *minishell);
t_parse_op		*get_parse_ops(void);
int				handle_token_type(t_token **cur_token, t_cmd **cur_cmd,
					t_minishell *minishell);
int				handle_redir_in(t_token **cur_token, t_cmd **cur_cmd,
					t_minishell *minishell);
int				handle_redir_out(t_token **cur_token, t_cmd **cur_cmd,
					t_minishell *minishell);
int				handle_word(t_token **cur_token, t_cmd **cur_cmd,
					t_minishell *minishell);
int				handle_pipe(t_token **cur_token, t_cmd **cur_cmd,
					t_minishell *minishell);
int				handle_redir_heredoc(t_token **cur_token, t_cmd **cur_cmd,
					t_minishell *minishell);
int				handle_redir_append(t_token **cur_token, t_cmd **cur_cmd,
					t_minishell *minishell);
/* Vars expansion */
void			init_expansion(t_expansion *exp, char *str);
void			ensure_buffer_space(t_expansion *exp, int space_needed);
int				expand_var(t_expansion *exp, char *str, t_minishell *minishell);
char			*extract_var_name(char *start, int *chars_consumed);
int				handle_special_cases(t_expansion *exp, char *str,
					t_minishell *minishell);
t_bool			is_valid_varchar(char c, t_bool first_char);
/* Redirections */
int 			add_infile_to_cmd(t_cmd *cmd, t_infile *new_infile);
int 			add_outfile_to_cmd(t_cmd *cmd, t_outfile *new_outfile);
t_infile		*create_infile_from_heredoc(char *delimiter, int start);
t_infile		*create_infile_from_path(char *path);
t_outfile		*create_outfile(char *path, t_bool append);

/******** Execution ********/
void			execute_cmd_lst(t_minishell *minishell);
char			*get_exec_path(char *arg, t_minishell *minishell);
pid_t			run_in_child_process(t_builtin *builtin, t_cmd *cmd,
					t_minishell *minishell);
int				process_all_heredocs(t_minishell *ms);
int				setup_redirections(t_cmd *cmd);
t_bool			is_forbidden_cmd(t_cmd *cmd);
int				process_all_heredocs(t_minishell *ms);
int				read_heredoc(t_cmd *cmd, int write_fd, t_minishell *ms);
/* Pipes and redirections */
void			init_pipe_if(t_cmd *cmd, t_minishell *minishell);
void			setup_pipe_ends(t_cmd *cmd, t_minishell *minishell);
void			close_pipe_if(t_cmd *cmd);
int				setup_redirections(t_cmd *cmd);
void			save_stdin_stdout(t_cmd *cmd, t_minishell *minishell);
void			restore_stdin_stdout(t_cmd *cmd, t_minishell *minishell);
t_infile		*get_last_infile(t_infile **infiles);
t_outfile		*get_last_outfile(t_outfile **outfiles);
/* Executables */
void			run_executable(t_cmd *cmd, t_minishell *minishell);
void			setup_pipe_ends(t_cmd *cmd, t_minishell *minishell);
void			close_pipe_if(t_cmd *cmd);
/* Builtins */
t_builtin		*get_builtin(t_cmd *cmd);
void			run_builtin(t_bool in_child_process, t_builtin *builtin,
					char **args, t_minishell *minishell);
int				do_cd(char **args, t_minishell *minishell);
int				do_echo(char **args, t_minishell *minishell);
int				do_pwd(char **args, t_minishell *minishell);
int				do_export(char **args, t_minishell *minishell);
int				do_unset(char **args, t_minishell *minishell);
int				do_env(char **args, t_minishell *minishell);
int				do_exit(char **args, t_minishell *minishell);
char			*get_destdir(char **args, int args_nb, t_minishell *ms);
char			*get_current_pwd(void);
int				change_directory(char *dest_dir, char **pwd);
int				update_envvars(char **pwd, char **new_pwd, t_minishell *ms);
int				error_if_options(char **args, char *builtin_name);
int				error_if_wrong_args(char **args, char *builtin_name,
					int max_args_nb);

/******** Utils ********/
/* Error handling */
void			set_errno(int err_no);
void			put_error(char *err_msg);
void			put_error1(char *fmt, char *arg);
void			put_error2(char *fmt, char *arg1, char *arg2);
/* Memory */
void			ft_free_ptr(void **ptr);
void			free_minishell(t_minishell **minishell);
void			free_envvar_lst(t_envvar **var_lst);
t_envvar		*free_envvar_node(t_envvar **node);
void			free_token_lst(t_token **token_lst);
void			free_cmd_lst(t_cmd **cmd_lst);
t_cmd			*free_cmd_node(t_cmd **cmd);
/* Exit */
void			exit_minishell(int exit_code, t_minishell *minishell,
					char *err_msg);
void			exit_minishell1(int exit_code, t_minishell *minishell,
					char *fmt, char *arg);
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
char			*char_to_str(char c);
char			*int_to_str(int n);
/* Command */
t_bool			cmd_has_redirections(t_cmd *cmd);

#endif
