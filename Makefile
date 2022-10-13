# **************************************************************************** #
# MAKEFILE

NAME		:= minishell

COMPILER	= cc
CFLAGS		= -Wall -Werror -Wextra -g -fsanitize=address

LIBFT_DIR	= ./libft/
LIBFT_EXEC	= libft/libft.a
LIB_INC		= -I ./includes/libft
LIBS		= -lreadline

# **************************************************************************** #
# SOURCES

SRC_FILES	:= main.c 2darray.c 2darray2.c

OBJ_FILES	:= ${SRC_FILES:.c=.o}
SRC			:= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			:= $(addprefix $(OBJ_DIR), $(OBJ_FILES))


# **************************************************************************** #
# COLORS

RED			:= \033[0;31m
GREEN		:= \033[0;92m
YELLOW		:= \033[0;93m
BLUE		:= \033[0;94m
END_COLOR	:= \033[0;39m


# **************************************************************************** #
# RULES

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBS)
	$(COMPILER) $(CFLAGS) $(LIBFT_EXEC)

clean: 
	$(RM) $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJ_DIR)
	make fclean -C $(LIBFT_DIR)

re: fclean all
	echo "$(RED)Cleaned up all files for $(NAME)!"

.PHONY:		all clean fclean re