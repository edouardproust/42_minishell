NAME = ./minishell


# ************************************
# Sources                            *
# ************************************

C_DIR = src

C_FILES = debug.c \
	main.c \
	utils/free/minishell.c \
	utils/free/envvar.c \
	utils/free/token.c \
	utils/free/cmd.c \
	utils/exit.c \
	utils/error.c \
	utils/string.c \
	utils/char.c \
	utils/fd.c \
	utils/cmd.c \
	env/init.c \
	env/ops.c \
	env/path.c \
	env/utils/envp.c \
	env/utils/envvar.c \
	env/valid.c \
	signal/signal.c \
	signal/utils.c \
	tokenizer/tokenizer.c \
	tokenizer/token_ops.c \
	tokenizer/token_creation.c \
	tokenizer/token_list.c \
	tokenizer/quote_handling.c \
	tokenizer/remove_quotes_expand.c \
	tokenizer/vars_expansion/exp_init.c \
	tokenizer/vars_expansion/var_name_extraction.c \
	tokenizer/vars_expansion/special_cases.c \
	tokenizer/vars_expansion/expansion.c \
	tokenizer/vars_expansion/tilde_expansion.c \
	parser/cmd/init_list.c \
	parser/cmd/new_cmd.c \
	parser/cmd/utils.c \
	parser/parser.c \
	parser/parser_ops.c \
	parser/handlers/handle_word.c \
	parser/handlers/handle_pipe.c \
	parser/handlers/handle_redir_in.c \
	parser/handlers/handle_redir_out.c \
	parser/handlers/handle_redir_append.c \
	parser/handlers/handle_redir_heredoc.c \
	parser/handlers/utils/redir_valid.c \
	parser/handlers/utils/redir_create.c \
	parser/handlers/utils/redir_add.c \
	parser/handlers/split_tokens.c \
	execute/parent_process.c \
	execute/child_process.c \
	execute/pipe.c \
	execute/redirection/save_restore.c \
	execute/redirection/setup.c \
	execute/redirection/utils.c \
	execute/heredoc/heredoc.c \
	execute/heredoc/utils.c \
	execute/executable.c \
	execute/builtin.c \
	execute/utils.c \
	execute/builtins/utils_args.c \
	execute/builtins/cd/cd.c \
	execute/builtins/cd/utils_dir.c \
	execute/builtins/cd/utils_envvar.c \
	execute/builtins/echo.c \
	execute/builtins/env.c \
	execute/builtins/exit.c \
	execute/builtins/export.c \
	execute/builtins/pwd.c \
	execute/builtins/unset.c \

SRCS = $(addprefix $(C_DIR)/,$(C_FILES))


# ************************************
# Objects                            *
# ************************************

O_DIR = src/_obj

OBJS = $(addprefix $(O_DIR)/,$(C_FILES:.c=.o))


# ************************************
# Headers                            *
# ************************************

H_DIR = inc

H_FILES = debug.h \
	minishell.h

HEADERS = $(addprefix $(H_DIR)/,$(H_FILES))


# ************************************
# Flags                              *
# ************************************

CFLAGS = -Wall -Wextra -Werror


# ************************************
# Libraries                          *
# ************************************

LIBS_DIR = lib

LIBFT_DIR = $(LIBS_DIR)/libft

LIBFT = $(LIBFT_DIR)/libft.a

LIBS = $(LIBFT) -lreadline


# ************************************
# Includes                           *
# ************************************

INCLUDES = -I$(H_DIR) -I$(LIBFT_DIR)


# ************************************
# Rules                              *
# ************************************

all: libft $(NAME)

$(O_DIR)/%.o: $(C_DIR)/%.c Makefile $(HEADERS)
	@mkdir -p $(@D)
	cc -c -o $@ $< $(INCLUDES) $(CFLAGS)

$(NAME): $(OBJS) $(LIBFT)
	cc -o $@ $^ $(LIBS)

clean:
	rm -rf $(O_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

libft:
	$(MAKE) -C $(LIBFT_DIR)

valgrind:
	valgrind --leak-check=full --track-origins=yes --track-fds=yes $(NAME)

# ************************************
# Phony                              *
# ************************************

.PHONY: all clean fclean re libft valgrind
