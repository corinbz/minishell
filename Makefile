NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
OBJDIR = ./obj/
SRCDIR = ./src/
INCLUDES = -I/usr/include/readline -I$(SRCDIR)

# Find all .c files in the src/ directory and its subdirectories
SRC := $(shell find $(SRCDIR) -name "*.c")
# Generate object file names
OBJS := $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)

# Colors
GREEN = \033[1;32m
BLUE = \033[1;36m
YELLOW = \033[1;33m
RED = \033[1;31m
NC = \033[0m # No Color

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)Linking: $(NAME)$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) -lreadline -o $@
	@echo "$(BLUE)$(NAME) created successfully!$(NC)"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(GREEN)Compiling: $<$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning object files$(NC)"
	@rm -rf $(OBJDIR)
	@echo "$(YELLOW)$(NAME) -> Object files removed!$(NC)"

fclean: clean
	@echo "$(RED)Removing executable: $(NAME)$(NC)"
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) executable removed!$(NC)"

re: fclean all

.PHONY: all clean fclean re