NAME		:=	philo
OBJ_DIR		:=	obj
SRC_DIR		:=	src

CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra
#CFLAGS		:=	-Wall -Werror -Wextra -g -fsanitize=address
#CFLAGS		:=	-Wall -Werror -Wextra -g -fsanitize=thread
HEADERS		:=  includes

SRCS_NAME	:=	main.c check_arg.c ft_atoi.c ft_isdigit.c watchman.c philo_set.c print_log.c routine.c table_set.c \

SRCS	:= $(addprefix $(SRC_DIR)/, $(SRCS_NAME))
OBJECTS	:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME):	$(OBJECTS)
	$(CC) $(CFLAGS) -I $(HEADERS) -o $(NAME) $(OBJECTS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re
