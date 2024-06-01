NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g3

LIBFT = ./libft/libft.a
LIBFTDIR = ./libft/
OBJDIR = ./obj/
INCLUDES = -I$(LIBFTDIR) -I/usr/include/readline

SRC := $(shell find ./src/minishell/ -name "*.c")

# Colors
GREEN = \033[1;32m
BLUE = \033[1;36m
YELLOW = \033[1;33m
RED = \033[1;31m
NC = \033[0m # No Color

OBJS = $(patsubst ./src/minishell/%.c, $(OBJDIR)%.o, $(SRC))

$(OBJDIR)%.o: src/minishell/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN)Compiled $< successfully!$(NC)"

all: $(NAME)

$(NAME): $(OBJS)
	@make -s -C $(LIBFTDIR)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFTDIR) -lft -lreadline -o $@
	@echo "$(BLUE)$(NAME) created successfully!$(NC)"

clean:
	@rm -rf $(OBJDIR)
	@make -s -C $(LIBFTDIR) clean
	@echo "$(YELLOW)$(NAME) -> Object files removed!$(NC)"

fclean: clean
	@rm -f $(NAME)
	@make -s -C $(LIBFTDIR) fclean
	@echo "$(RED)$(NAME) executable removed!$(NC)"

re: fclean all

.PHONY: all clean fclean re
