NAME = minishell

CFLAGS = -g3 #-fsanitize=address -static-libasan #-Wall -Wextra -Werror

OBJDIR = ./obj/
INCLUDES = -I/usr/include/readline

# Find all .c files in the src/ directory and its subdirectories
SRC := $(shell find ./src/ -name "*.c")

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
	@$(CC) $(CFLAGS) $(OBJS) -lreadline -o $@
	@echo "$(BLUE)$(NAME) created successfully!$(NC)"

clean:
	@rm -rf $(OBJDIR)
	@echo "$(YELLOW)$(NAME) -> Object files removed!$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) executable removed!$(NC)"

re: fclean all

.PHONY: all clean fclean re
