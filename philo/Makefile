NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -lpthread #-fsanitize=thread
SRC_DIR = src/
OBJ_DIR = obj/
SRC_FILES = ft_atoi.c parse.c philo.c function_utils.c print_errors.c \
dinner_simulation.c getters_setters.c init_data.c synchornization.c print.c \
monitor.c get_set_time.c cases.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
INCLUDE = -I./include/
RM = rm -f

# Colors for terminal output
GREEN = \033[0;32m
BLUE = \033[0;34m
RESET = \033[0m

all: $(NAME) logo 



$(NAME): $(OBJS)
	@echo "$(GREEN)Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INCLUDE)
	@echo "$(GREEN)Compiled successfully! ./philo is ready.$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	@echo "$(BLUE)Cleaning object files...$(RESET)"
	@$(RM) $(OBJS)

fclean: clean
	@echo "$(BLUE)Removing executable...$(RESET)"
	@$(RM) $(NAME)

logo:
	@echo "$(BLUE)"
	@echo "██████╗ ██╗  ██╗██╗██╗      ██████╗ "
	@echo "██╔══██╗██║  ██║██║██║     ██╔═══██╗"
	@echo "██████╔╝███████║██║██║     ██║   ██║"
	@echo "██╔═══╝ ██╔══██║██║██║     ██║   ██║"
	@echo "██║     ██║  ██║██║███████╗╚██████╔╝"
	@echo "╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ "
	@echo "$(RESET)"

re: fclean all

.PHONY: all clean fclean re logo
