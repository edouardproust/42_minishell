#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#define TOKEN_WORD 0
#define	TOKEN_PIPE 1
#define	TOKEN_REDIR_IN 3
#define	TOKEN_REDIR_OUT 4

typedef struct s_token
{
	char	*value;
	int	type;
	struct s_token *next;
} t_token;

typedef struct s_cmd {
    char    **args;
    char    *infile;
    char    *outfile;
    int     pipe_after;
    struct s_cmd *next;
} t_cmd;

typedef struct s_node {
    t_cmd           *cmd;
    struct s_node   *next;
} t_node;

int main(int argc, char **argv);
void    init_cmd_struct(t_cmd *cmd);
t_token *create_token(char *value, int type);
int get_token_type(char c);
t_token *create_word_token(char *input, int *index);
void add_token(t_token **tokens, t_token *new);
t_token *tokenizer(char *input);
//t_node  *create_node(void);
//void    populate_node(t_node *node, char *arg);
//void	free_nodes(t_node *node);
t_cmd *create_cmd();
void add_arg_to_cmd(t_cmd *cmd, char *arg);
t_cmd *parse_tokens(t_token *tokens);
void print_cmds(t_cmd *cmd);
void print_tokens(t_token *tokens);
void free_tokens(t_token *tokens);
void free_cmds(t_cmd *cmds);

#endif

