NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fPIE

SRC_DIR = src/
OBJ_DIR = obj/
SRC_FILES = ft_atoi.c parse.c philo.c function_utils.c print_errors.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
INCLUDE = -I./include/

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INCLUDE)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re