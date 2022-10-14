NAME = minishell

LIBFT = libft/libft.a

INC = includes
LIBFT = libft/libft.a 
SRCS = src/main c. \
		src/2darray.c \
		src/2darray2.c \
		src/commandtrim.c \
		src/initialise_prompt.c \
		src/signal.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra
RM =  rm -rf


UNAME := $(shell uname -s)

ifeq ($(UNAME) , Linux)
	INCDIR := -L/usr/local/lib -I/usr/local/include 

else
	INCDIR := -I ~/goinfre/.brew/opt/readline/include -L ~/goinfre/.brew/opt/readline/lib
endif

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) -lreadline -lncurses $^ -o $(NAME)  -I $(INCDIR) -lreadline

%.o:%.c $(INC)/minishell.h
	$(CC) $(CFLAGS) -I $(INC) -c $< -o $@ -I $(INCDIR) -lreadline

$(LIBFT):
	make bonus -C libft
clean :
	$(RM) $(OBJS)
	make clean -C libft
fclean : clean
	$(RM) $(NAME)
	make fclean -C libft
re : fclean all

run : $(NAME)
	./$(NAME)