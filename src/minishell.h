#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_cmd {
    char    **args;
    char    *infile;
    char    *outfile;
    int     pipe_after;
} t_cmd;

typedef struct s_node {
    t_cmd           *cmd;
    struct s_node   *next;
} t_node;

int main(int argc, char **argv);
char    **tokenizer(char *input);
t_node  *create_node(void);
void    populate_node(t_node *node, char *arg);
void	free_nodes(t_node *node);
void    parse_arguments(char **tokens, t_node *node);
void    parse_redirections(char **tokens, t_node *node);
void    parse_command(char *input, t_node **args_list);

#endif

