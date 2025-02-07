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
#define TOKEN_APPEND 4
#define TOKEN_HEREDOC 5

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

//lexer.c
t_token	*token_new(char *value, int type);
int	get_token_type(char *input, int i);
t_token	*create_word_token(char *input, int *index);
void    token_addback(t_token **tokens, t_token *new);
t_token *tokenizer(char *input);

//parser.c
t_cmd   *cmd_new();
void    add_arg_to_cmd(t_cmd *cmd, char *arg);
t_cmd   *parse_tokens(t_token *tokens);

//parser_utils.c
void    handle_input_redirection(t_cmd *current_cmd, t_token **tokens);
void    handle_output_redirection(t_cmd *current_cmd, t_token **tokens);
void    handle_word(t_cmd *current_cmd, t_token *tokens);
void    handle_pipe(t_cmd **current_cmd);

// execute.c
void	execute_cmd_lst(t_cmd **cmd_lst, char **envp);
char    *get_exec_path(char *arg, t_cmd **cmd_lst);

// exit.c
void	exit_parsing(t_cmd **foo, char *fmt, ...); // TODO (Ava) Edit function in exit.c
void	exit_exec(t_cmd **head, char *fmt, ...);

// free.c
t_cmd	*free_cmd(t_cmd **cmd); // TODO (Ava) Add free functions for lexer
void	free_cmd_lst(t_cmd **cmd_lst);
void	flush_fds(void);

// debug.c (TODO Delete these lines + debug.c before submit)
t_cmd	*create_cmd_lst(void);
void	debug_cmd_lst(t_cmd *cmd_lst);
void	debug_cmd(t_cmd *cmd, char *title);
void	debug_fd(char *label, int fd);
void	debug_read_fd(char *label, int fd);

#endif
