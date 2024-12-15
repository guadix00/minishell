NAME = minishell

SRCS = env.c expansion.c main.c syntax.c tokenize.c utils.c
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I/usr/include
LDFLAGS = -L/usr/lib
LDLIBS = -lreadline

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

END = \033[m
YELLOW = \033[33m

all: submodule $(NAME)

submodule:
	git submodule init
	git submodule update

$(NAME): $(OBJS) $(LIBFT)
	@echo "\n$(YELLOW)Minishell in the oven...$(END)"
	$(CC) $(LDFLAGS) $(OBJS) $(LIBFT) $(LDLIBS) -o $(NAME)

%.o: %.c minishell.h libft/libft.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "\n$(YELLOW)Construyendo libft...$(END)"
	@make -C $(LIBFT_DIR)

clean:
	@echo "\n$(YELLOW)Limpiando archivos...$(END)"
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "\n$(YELLOW)Limpiando todo...$(END)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re submodule
