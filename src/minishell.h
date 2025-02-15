#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"

#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

#define FD_LIMIT 1024

#define TOKEN_WORD 0
#define	TOKEN_PIPE 1
#define	TOKEN_REDIR_IN 2
#define	TOKEN_REDIR_OUT 3
#define	TOKEN_APPEND 4
#define	TOKEN_HEREDOC 5

typedef struct s_token
{
	char	*value; //here store the text here eg, "echo", "<"
	int		type; //we store the number of what kind of token this is
	struct s_token *next;
} t_token;

typedef struct s_cmd {
    char	**args;
    char	*infile;
    char	*outfile;
    int				*pipe;
    int				fdin;
    int				fdout;
//  int		append; (to be implemented later)
//  char	*heredoc_del; (to be implemented later)
    struct s_cmd *prev;
    struct s_cmd *next;
} t_cmd;

//int		main(int argc, char **argv);
int     main(int ac, char **av, char **envp);
t_cmd *create_cmd_lst(char *input);
void    debug_tokens(t_token *tokens);
void    debug_cmds(t_cmd *cmd);
void    debug_cmd(t_cmd *cmd, char *label);
void    debug_cmd_lst(t_cmd *cmd_lst);
void debug_fd(char *label, int fd);
void debug_read_fd(char *label, int fd);
t_token *token_new(char *value, int type);
int     is_word_char(char c);
int is_special_char(char c);
int		get_token_type(char *input, int i);
t_token *create_word_token(char *input, int *index);
char    *remove_quotes(char *str);
int skip_quotes(char *input, int *index);
void	token_addback(t_token **tokens, t_token *new);
t_token *tokenizer(char *input);
t_cmd	*cmd_new(t_cmd *prev_cmd);
void	add_arg_to_cmd(t_cmd *cmd, char *arg);
void handle_input_redirection(t_cmd **cmd_list_head, t_token **tokens_head, t_cmd *current_cmd, t_token **current_token);
void handle_output_redirection(t_cmd **cmd_list_head, t_token **tokens_head, t_cmd *current_cmd, t_token **current_token);
void    handle_word(t_cmd **cmd_list_head, t_token **tokens_head, t_cmd *current_cmd, t_token *token);
void handle_pipe(t_cmd **cmd_list_head, t_cmd **current_cmd, t_token **tokens_head, t_token **current_token);
void handle_token_type(t_cmd **cmd_list_head, t_cmd **current_cmd, t_token **tokens_head, t_token **current_token);
t_cmd	*parse_tokens(t_token *tokens_head);
void 	print_cmds(t_cmd *cmd);
void	print_tokens(t_token *tokens);
void    exit_exec(t_cmd **cmd_lst, char *fmt, ...);
void    exit_parsing(t_cmd **cmd_lst, t_token **tokens_head, char *fmt, ...);
t_cmd   *free_cmd(t_cmd **cmd);
void    free_cmd_lst(t_cmd **cmd_lst);
void    free_token_lst(t_token **tokens);
void	flush_fds(void);
void    execute_cmd_lst(t_cmd **cmd_lst, char **envp);
char    *get_exec_path(char *progname, t_cmd **cmd_lst);

#endif
