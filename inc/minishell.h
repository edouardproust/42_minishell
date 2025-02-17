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

typedef struct	s_parse	{
	t_cmd	**cmd_list_head;
	t_cmd	*current_cmd;
	t_token	*tokens_head;
	t_token	*current_token;
} t_parse;

//main.c
int	main(int ac, char **av, char **envp);

//cmd_list.c
t_cmd	*init_cmd_lst(char *input);

//general_utils.c
int	is_special_char(char c);
int	is_word_char(char c);
int	is_quote_char(char c);

//tokenize.c
t_token *tokenizer(char *input);

//tokens_utils.c
t_token	*token_new(char *value, int type);
int	get_token_type(char *input, int i);
t_token	*create_word_token(char *input, int *index);
void	token_addback(t_token **tokens, t_token *new);

//quote_handler.c
int	skip_quotes(char *input, int *index);
char	*remove_quotes(char *str);

//parser.c
t_cmd   *cmd_new();
void    add_arg_to_cmd(t_cmd *cmd, char *arg);
t_cmd   *parse_tokens(t_token *tokens_head);

//token_handlers.c
void    handle_input_redirection(t_parse *parse);
void    handle_output_redirection(t_parse *parse);
void    handle_word(t_parse *parse);
void    handle_pipe(t_parse *parse);

//parser_utils.c
void	handle_token_type(t_parse *parse);

// execute.c
void	execute_cmd_lst(t_cmd **cmd_lst, char **envp);
char    *get_exec_path(char *arg, t_cmd **cmd_lst);

// exit.c
void	exit_parsing(t_parse *parse, char *fmt, ...);
void	exit_exec(t_cmd **head, char *fmt, ...);

// free.c
t_cmd	*free_cmd(t_cmd **cmd);
void	free_cmd_lst(t_cmd **cmd_lst);
void	free_token_lst(t_token **tokens);
void	flush_fds(void);

// debug.c (TODO Delete these lines + debug.c before submit)
t_cmd	*create_cmd_lst(void);
void	debug_tokens(t_token *tokens);
void	debug_cmds(t_cmd *cmd);
void	debug_cmd_lst(t_cmd *cmd_lst);
void	debug_cmd(t_cmd *cmd, char *title);
void	debug_fd(char *label, int fd);
void	debug_read_fd(char *label, int fd);

#endif
