#include "minishell.h"

int     valid_quote(char *pipe)
{
    int i;

    i = 0;
    while (pipe[i])
    {
        if (pipe[i] == '"')
            return (i);
        i++;
    }
    printf("Quote error\n");
    exit (1);
}

int     alloc_pipe(char *pipe)
{
    int i;
    int p;

    p = 1;
    i = 0;
    if (pipe[0] == '|')
    {
        printf("error");
        exit(1);
    }
    while (pipe[i])
    {
        if (pipe[i] == 34)
        {
            //printf("****%d\n",i);
            i = valid_quote(pipe) + i + 3;
            //printf("-=-%c\n",pipe[i]);
            //printf("****%d\n",i);
        }
        if (pipe[i] == '|')
            p++;
        i++;
    }
    return (p);
}

char    *command(char *cmd)
{
    int i;
    char *str;

    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '|')
            break;
        i++;
    }
    str = malloc(i + 1);
    i = 0;
    while (cmd[i] != '\0')
    {        
        if (cmd[i] == '|' && cmd[i - 1] == ' ' && cmd[i + 1] == ' ')
            break;
        str[i] = cmd[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

int     skip_pipe(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '|' && line[i - 1] == '"' && line[i + 1] == '"')
            break;
        i++;
    }
    return (i);
}

char    **split_pipe(char *line)
{
    int i;
    int j;
    char **pipes;
    
    j = 0;
    printf ("%d\n", alloc_pipe(line));
    pipes = (char**)malloc(sizeof(char*) * (alloc_pipe(line) + 1));
    i = 0;
    while (i < alloc_pipe(line))
    {
        pipes[i] = command(line + j);
       //printf("1%s\n",pipes[i]);
        j = skip_pipe(line) + 1;
        i++;
    }
    pipes[i] = NULL;
    return pipes;
}

char    *get_file_name(char *str)
{
    int i;
    char *name;
    int j;

    i = 0;
    j = 0;
    name = NULL;
    while (str[i] == ' ')
        i++;
    while (str[i] && str[i] != ' ')
    {
        ft_strjoin(name, &str[i]);
        i++;
        j++;
    }
    if (j == 0)
    {
        printf("syntax error near unexpected token\n");
        exit (1);
    }
    return (name);
}

t_file  *file_add(t_file *file, char *str, int type)
{
    t_file *new;
    t_file *tmp;

    new = (t_file *)malloc(sizeof(t_file));
    new->type = type;
    new->file = get_file_name(str);
    tmp = file;
    while (tmp->next)
    {
        tmp = tmp->next;
    }
    tmp->next = new;
    return file;
}
t_file  *file(char *command)
{
    t_file *files;
    int i;

    i = 0;
    while (command[i])
    {
        if (command[i] == '<' && command[i + 1] == '<')
        {
            i++;
            files = file_add(files, command + i, 4);
        }
        i++;
    }
    return (files);
}

int main(int argc, char **argv)
{
    int i;
    char **str;
    char *line;
    t_file *filee;

    while (1)
    {
         line = readline("khater> ");
    if  (!line)
        exit(0);
    add_history(line);
    str = split_pipe(line);
    // filee = file(str[0]);
    // printf("%s\n",filee->file);
    i = 0;

    while (str[i] != NULL)
    {
        printf("%s\n", str[i]);
        i++;
    }
    }
    return (0);
}