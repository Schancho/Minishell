#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

typedef enum e_file_type
{
        F_INPUT = 1,
        F_OUTPUT = 2,
        F_HEREDOC = 3,
        F_APPEND = 4
}           t_file_type;

typedef struct s_garbage
{
    void *garb;
    struct s_garbage *next;

}               t_garbage;

typedef struct  s_file
{
    t_file_type type;
    char        *file;
    struct s_file *next;
}               t_file;

typedef struct          s_command
{
    char                *command;
    struct s_command    *next;
}                       t_command;

typedef struct          s_pline
{
    t_command           *command;
    t_file              *file;
    struct s_pline      *next;
}                       t_pline;

// typedef struct      s_line
// {
//     char            **command;
//     t_file          *file;
//     struct s_line   *next;
// }                   t_line;


typedef struct s_pipe
{
    char    *pipe_line;
    struct s_pipe   *next;
}               t_pipe;

typedef struct s_env_var
{
    char *env;
    char *var;
    char *value;
    struct s_env_var *next;
}               t_env_var;

typedef struct s_line
{
    t_pline *pipe_line;
    struct s_line *next;
}               t_line;
char    **split_pipe(char *line, t_garbage **g);
char    *ft_strjoin(char const *s1, char const *s2, t_garbage **g);
char	**ft_split(char const *str, char c, t_garbage **g);
void        garbage(t_garbage **garbage, void *address);
char	**_split(char const *str, char c);





int execution(t_pline *p_line, char **env);

#endif
