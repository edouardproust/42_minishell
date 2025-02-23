#include "minishell.h"
/**
 * Handles the pipe (`|`) token by creating a new command.
 * - Checks for syntax errors like consecutive pipes.
 * - Creates a new command for the next part of the pipeline.
 * @TODO Check malloc error message (for now on NULL)
 * 
 */
void	handle_pipe(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	if (!(*cur_token)->next || (*cur_token)->next->type == TOKEN_PIPE)
		exit_minishell(EXIT_FAILURE, minishell,
			"syntax error near unexpected token `|'");
	(*cur_cmd)->next = cmd_new((*cur_cmd));
	if (!(*cur_cmd)->next)
		exit_minishell(EXIT_FAILURE, minishell, NULL);
	(*cur_cmd) = (*cur_cmd)->next;
}

/**
 * Handles input redirection (`<`) token by setting the infile for the
 * current command.
 * - Ensures that the next token is a valid file name (word token).
 * - Copies the file name to the current command's infile field.
 * @TODO Check malloc error message (for now on NULL)
 */
void	handle_input_redirection(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	if (!(*cur_token)->next || (*cur_token)->next->type != TOKEN_WORD)
		exit_minishell(EXIT_FAILURE, minishell,
			"syntax error near unexpected token `newline'");
	ft_free_ptrs(1, &(*cur_cmd)->infile);
	(*cur_cmd)->infile = ft_strdup((*cur_token)->next->value);
	if (!(*cur_cmd)->infile)
		exit_minishell(EXIT_FAILURE, minishell, NULL);
	(*cur_token) = (*cur_token)->next;
}

/**
 * Handles output redirection (`>`) token by setting the outfile for the
 * current command.
 * - Ensures that the next token is a valid file name (word token).
 * - Copies the file name to the current command's outfile field.
 * @TODO Check malloc error message (for now on NULL)
 */
void	handle_output_redirection(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	if (!(*cur_token)->next || (*cur_token)->next->type != TOKEN_WORD)
		exit_minishell(EXIT_FAILURE, minishell,
			"syntax error near unexpected token `newline'");
	ft_free_ptrs(1, &(*cur_cmd)->outfile);
	(*cur_cmd)->outfile = ft_strdup((*cur_token)->next->value);
	if (!(*cur_cmd)->outfile)
		exit_minishell(EXIT_FAILURE, minishell, NULL);
	(*cur_token) = (*cur_token)->next;
}

/**
 * Handles a word token by copying its value and adding it to the current
 * command's arguments.
 * - Duplicates the word and adds it to the args list of the current command.
 * @TODO Check malloc error message (for now on NULL)
 */
void	handle_word(t_token **cur_token, t_cmd **cur_cmd,
	t_minishell *minishell)
{
	char	*arg_copy;

	arg_copy = ft_strdup((*cur_token)->value);
	if (!arg_copy)
		exit_minishell(EXIT_FAILURE, minishell, NULL);
	add_arg_to_cmd(*cur_cmd, arg_copy);
}
