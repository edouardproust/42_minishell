NAME = libft.a

SRCS = get_next_line.c \
	ft_atoi.c \
	ft_atol.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_exit.c \
	ft_fprintf.c \
	ft_free_ptrs.c \
	ft_free_split.c \
	ft_free_splitn.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_isspace.c \
	ft_itoa.c \
	ft_lutoa_base.c \
	ft_matrix_dup.c \
	ft_matrix_size.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_pexit.c \
	ft_print_char.c \
	ft_print_hexa.c \
	ft_print_int.c \
	ft_print_ptr.c \
	ft_print_str.c \
	ft_print_uint.c \
	ft_printf.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strchri.c \
	ft_strdup.c \
	ft_strglue.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_vfprintf.c \
	ft_vprintf.c

FLAGS = -Wall -Werror -Wextra

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

%.o: %.c Makefile libft.h
	cc -c $< -o $@ $(FLAGS) -I .

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	ranlib	$(NAME)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
