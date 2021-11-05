#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_garbage
{
    void *garb;
    struct s_garbage *next;

}               t_garbage;

typedef struct s_env_var
{
    char *env;
    char *var;
    char *value;
    struct s_env_var *next;
}               t_env_var;

typedef enum e_file_type
{
        F_INPUT = 1,
        F_OUTPUT = 2,
        F_HEREDOC = 3,
        F_APPEND = 4
}           t_file_type;

typedef struct          s_command
{
    char                *command;
    struct s_command    *next;
}                       t_command;

typedef struct  s_file
{
    t_file_type type;
    char        *file;
    struct s_file *next;
}               t_file;

typedef struct          s_pline
{
    t_command           *command;
    t_file              *file;
    struct s_pline      *next;
}                       t_pline;

//PARSE FUNCTIONS
char	**ft_split(char const *str, char c, t_garbage **g);


//UTILS FUNCTIONS
size_t	_strlen(const char *s);
char	*_strjoin(char const *s1, char const *s2);
char	**za7asplit(char const *str, char c);

int		frederictions(int *fd, t_file * iter);
char	*path_finder(char *key, t_env_var *lenv);
char	**conv_cmd(t_command *cmd);
char    *search_env_var(t_env_var *env, char *str);
char    **environment_var(t_env_var *environment, t_garbage **g);

#endif