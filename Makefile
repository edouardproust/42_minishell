NAME = ./minishell


# ************************************
# Sources                            *
# ************************************

C_DIR = src

C_FILES = debug.c \
	main.c \
	free.c \
	close.c \
	exit.c \
	error.c \
	env/init.c \
	env/utils.c \
	env/ops.c \
	env/path.c \
	cmd_list.c \
	tokenizer/tokenizer.c \
	tokenizer/tokenizer_utils.c \
	tokenizer/token_utils.c \
	tokenizer/quote_handler.c \
	parser/parser.c \
	parser/parser_utils.c \
	parser/cmd_utils.c \
	parser/token_handlers.c \
	execute/parent_process.c \
	execute/child_process.c \
	execute/executables.c \
	execute/builtins.c \
	execute/builtins/cd.c \
	execute/builtins/echo.c \
	execute/builtins/env.c \
	execute/builtins/exit.c \
	execute/builtins/export.c \
	execute/builtins/pwd.c \
	execute/builtins/unset.c \
	utils/string_utils.c \

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

$(NAME): $(OBJS)
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

# ************************************
# Phony                              *
# ************************************

.PHONY: all clean fclean re libft
