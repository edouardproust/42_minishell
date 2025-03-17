#include "minishell.h"
/* 
 * Returns a static list of parsing operators and their corresponding handlers.
 *
 * Used in `handle_token_type()` to determine how to process tokens.
 * 
 * Returns: A pointer to a static array of `t_parse_op` structures.
 */
t_parse_op	*get_parse_ops(void)
{
	static t_parse_op	parse_ops[] = {
	{TOKEN_PIPE, handle_pipe},
	{TOKEN_REDIR_IN, handle_redir_in},
	{TOKEN_REDIR_OUT, handle_redir_out},
	{TOKEN_HEREDOC, handle_redir_heredoc},
	{TOKEN_APPEND, handle_redir_append},
	{TOKEN_WORD, handle_word},
	{0, NULL}
	};

	return (parse_ops);
}

/* 
 * Processes tokens based on their type using appropriate handler functions
 * - Calls handlers for redirections (`<`, `>`, `<<`, `<<`),
 *   pipes (`|`), and words.
 * - If an unknown token is encountered, exits with an error.
 */
int	handle_token_type(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	t_parse_op	*parse_ops;
	int			type;
	int			i;

	parse_ops = get_parse_ops();
	type = (*cur_token)->type;
	i = 0;
	while (parse_ops[i].handler)
	{
		if (parse_ops[i].type == type)
		{
			if (parse_ops[i].handler
				(cur_token, cur_cmd, minishell) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	exit_minishell(EXIT_FAILURE, minishell, NULL);
	return (EXIT_FAILURE);
}

/**
 * Determines the error message for invalid redirection syntax.
 * 
 * @param token Current token (e.g., `<`, `>`, `<<`, `>>`).
 * @return "newline" if no token follows, "|" for unexpected pipes.
 * 
 */
char	*redir_error(t_token *token)
{
	if (!token->next)
		return ("newline");
	if (token->next->type == TOKEN_PIPE)
		return ("|");
	return (token->next->value);
}

/**
 * Validates redirection targets to prevent ambiguous filenames.
 * 
 * @param file_token Token containing filename (after expansion)
 * @param minishell Shell context for error reporting
 * @return EXIT_SUCCESS if valid, EXIT_FAILURE if:
 *         - Value is empty/unset
 *         - Contains spaces in unquoted token
 * @note Uses original token value for error messages
 */
int	check_ambiguous_redirect(t_token *file_token, t_minishell *minishell)
{
	char	*expanded_val;

	expanded_val = file_token->value;
	if (!expanded_val || expanded_val[0] == '\0')
	{
		put_error1("%s: ambiguous redirect", file_token->original_value);
		minishell->exit_code = E_CRITICAL;
		return (EXIT_FAILURE);
	}
	if (ft_strchr(expanded_val, ' ') && !file_token->was_quoted)
	{
		put_error1("%s: ambiguous redirect", file_token->original_value);
		minishell->exit_code = E_CRITICAL;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
