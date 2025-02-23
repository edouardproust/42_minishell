#include "minishell.h"

t_token_op *get_token_ops(void)
{
    static t_token_op token_ops[] =
    {
        {"|", TOKEN_PIPE, handle_pipe},
//      {"<<", TOKEN_HEREDOC, handle_heredoc},
        {"<", TOKEN_REDIR_IN, handle_redir_in},
//      {">>", TOKEN_APPEND, handle_append},
        {">", TOKEN_REDIR_OUT, handle_redir_out},
        {NULL, TOKEN_WORD, handle_word}
    };
    return (token_ops);
}

t_token_op *get_token_op(int type)
{
    t_token_op  *token_ops;
    int i;

    token_ops = get_token_ops();
    i = 0;
    while (token_ops[i].pattern || token_ops[i].type != TOKEN_WORD)
    {
        if (token_ops[i].type == type)
            return (&token_ops[i]);
        i++;
    }
    return (&token_ops[i]);
}