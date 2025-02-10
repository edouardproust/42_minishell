#ifndef DEBUG_H
# define DEBUG_H

#include "minishell.h"

# define DEBUG 1

extern int  g_logfd;

t_cmd		*create_cmd_lst(void);
void		debug_cmd_lst(t_cmd *cmd_lst);
void		debug_cmd(t_cmd *cmd, char *title);
void		open_logfile(char *filepath);
void		debug_fd(char *label, int fd);
void		debug_process(int pid, int status);
void		debug_read_fd(char *label, int fd);

#endif