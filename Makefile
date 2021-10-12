LDFLAGS=-lreadline -L/goinfre/schancho/schancho/.brew/opt/readline/lib
CPPFLAGS=-I/goinfre/schancho/schancho/.brew/opt/readline/include
CC = gcc
FLAGS = -Wall -Wextra -Werror
SRC = parser.c utils.c 
NAME = minishell

all : $(NAME)

$(NAME) : $(SRC)
		$(CC) $(LDFLAGS) $(CPPFLAGS) -o $(NAME) $(SRC)
