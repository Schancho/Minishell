LDFLAGS=-lreadline -L/goinfre/schancho/schancho/.brew/opt/readline/lib
CPPFLAGS=-I/goinfre/schancho/schancho/.brew/opt/readline/include
CC = gcc -g -fsanitize=address
FLAGS = -Wall -Wextra -Werror
SRC = parser.c utils.c split.c
NAME = minishell

all : $(NAME)

$(NAME) : $(SRC)
		$(CC) $(LDFLAGS) $(CPPFLAGS) -o $(NAME) $(SRC)
clean:
	@echo "there is no object files"

fclean:clean
	@rm minishell

re:fclean all
