#ifndef DEBUG_H
# define DEBUG_H

# include "minishell.h"

extern int	g_logfd;

t_cmd	*create_cmd_lst(void);
void	debug_cmd_lst(t_cmd *cmd_lst);
void	debug_cmd(t_cmd *cmd, char *title);
void	open_logfile(char *filepath);
void	debug_tokens(t_token *tokens);
void	debug_fd(char *label, int fd);
void	debug_process(int pid, int status);
void	debug_envvars(t_envvar *lst);
void	debug_envp(char **envp);

#endif