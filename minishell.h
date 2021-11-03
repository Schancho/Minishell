#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>

typedef enum e_file_type
{
        F_INPUT = 1,
        F_OUTPUT = 2,
        F_HEREDOC = 3,
        F_APPEND = 4
}           t_file_type;

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

char    **split_pipe(char *line);
char	**ft_split(char const *str, char c);
char    *search_env_var(t_env_var *env, char *str);
char    **environment_var(t_env_var *environment);



//Execution Functions
// int		execution(t_pline *p_line, t_env_var *env);
int		execution(t_pline *p_line,char **env, t_env_var *lenv);
char	*path_finder(char *key, t_env_var *lenv);

//Execution utils Functions
char	**_split(char const *str, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);

#endif