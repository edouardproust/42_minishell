#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

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
    int		pipe_after;
//  int		append; (to be implemented later)
//  char	*heredoc_del; (to be implemented later)
    struct s_cmd *next;
} t_cmd;

typedef struct s_node {
    t_cmd           *cmd;
    struct s_node   *next;
} t_node;

int		main(int argc, char **argv);
t_token *token_new(char *value, int type);
int		get_token_type(char *input, int i);
t_token *create_word_token(char *input, int *index);
char    *remove_quotes(char *str);
int skip_quotes(char *input, int *index);
void	token_addback(t_token **tokens, t_token *new);
t_token *tokenizer(char *input);
t_cmd	*cmd_new();
void	add_arg_to_cmd(t_cmd *cmd, char *arg);
void    handle_input_redirection(t_cmd *current_cmd, t_token **tokens);
void    handle_output_redirection(t_cmd *current_cmd, t_token **tokens);
void    handle_word(t_cmd *current_cmd, t_token *tokens);
void    handle_pipe(t_cmd **current_cmd);
t_cmd	*parse_tokens(t_token *tokens);
void 	print_cmds(t_cmd *cmd);
void	print_tokens(t_token *tokens);
void	free_tokens(t_token *tokens);
void	free_cmds(t_cmd *cmds);

#endif
