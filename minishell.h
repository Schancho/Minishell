#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>

typedef struct  s_command
{
    char **command;
    char **file;
    struct s_command   *next_pipe;
}               t_command;

char    **split_pipe(char *line);
char	*ft_strjoin(char const *s1, char const *s2);

#endif