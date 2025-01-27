NAME = ./minishell


# ************************************
# Sources                            *
# ************************************

C_DIR = src

C_FILES = main.c

SRCS = $(addprefix $(C_DIR)/,$(C_FILES))


# ************************************
# Objects                            *
# ************************************

O_DIR = src/obj

OBJS = $(addprefix $(O_DIR)/,$(C_FILES:.c=.o))


# ************************************
# Headers                            *
# ************************************

H_DIR = inc

H_FILES = minishell.h

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
	@mkdir -p $(O_DIR)
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
