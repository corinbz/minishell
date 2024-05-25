NAME = minishell

CFLAGS = -Wall -Wextra #-Werror

LIBFT = ./libft/libft.a
LIBFTDIR = ./libft/
OBJDIR = ./obj/
INCLUDES = -I$(LIBFTDIR) -I/usr/include/readline

# Find all .c files in the src/ directory and its subdirectories
SRC := $(shell find ./src/minishell/ -name "*.c")

# Colors
GREEN = \033[1;32m
BLUE = \033[1;36m
YELLOW = \033[1;33m
RED = \033[1;31m
NC = \033[0m # No Color

OBJS = $(SRC:src/%.c=$(OBJDIR)%.o)

$(OBJDIR)%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
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
