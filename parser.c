#include "minishell.h"

int     valid_quote(char *pipe)
{
    int i;

    i = 0;
    while (pipe[i])
    {
        if (pipe[i] == 34)
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
    int j;

    j = 0;
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
            //printf("1****%d\n",i);
            j = valid_quote(pipe + i + 1);
            //printf("j == %d\n",j);
            i = i + j + 1;
            //printf("-=-%c\n",pipe[i]);
            //printf("2****%d\n",i);
            //j = 0;
        }
        if (pipe[i] == '|')
            p++;
        i++;
    }
    return (p);
}

int     end(char *line)
{
    int i;
    int p;
    int k;

    p = 0;
    i = 0;
    while (line[i])
    {
        if (line[i] == 34)
        {
            i++;
            while (line[i])
            {
                if (line[i] == 34)
                    break;
                i++;
            }
        }
        if (line[i] == '|')
            return i;
        i++;
    }
    return i;
}

char    *command(char *cmd, int j, int m)
{
    int i;
    int k;
    char *str;

    i = 0;
    k = m - j + 1;
    str = malloc(k);
    while (cmd[j] != '\0' && i != k - 1)
    {
        str[i] = cmd[j];
        i++;
        j++;
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
        if (line[i] == '|')
            break;
        i++;
    }
    return (i);
}

char    **split_pipe(char *line)
{
    int i;
    int j;
    int k;
    int m;
    char **pipes;
    
    j = 0;
    k = alloc_pipe(line);
    printf ("%d\n", k);
    pipes = (char**)malloc(sizeof(char*) * (k + 1));
    i = 0;
    m = 0;
    while (i < k)
    {
        m = end(line + j) + j;
        //printf("j == %d m == %d\n",j, m);
        pipes[i] = command(line,j,m);
        //printf("|%s|..\n",pipes[i]);
        j = m + 1;
       //printf("1%s\n",pipes[i]);
        //j = skip_pipe(line) + 1;
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

t_pipe  *add_pipe_line(t_pipe *pipe, char *cmd)
{
    t_pipe *new;
    t_pipe *tmp;

    tmp = pipe;
    new = (t_pipe *)malloc(sizeof(t_pipe));
    new->pipe_line = strdup(cmd);
    new->next = NULL;
    while (tmp)
        tmp = tmp->next;
    tmp = new;
    return pipe;
}
t_pipe  *pipe_line(t_pipe *p, char **command)
{
    int i;

    while (command[i])
    {
        p = add_pipe_line(p, command[i]);
        i++;
    }
    return p;
}
int main(int argc, char **argv)
{
    int i;
    char **str;
    char *line;
    int g;
    t_file *filee;

    while (1)
    {
        line = readline("khater> ");
        if  (!line)
            exit(0);
        add_history(line);
        str = split_pipe(line);
        i = 0;
        while (str[i] != NULL)
        {
            printf("(%s)\n", str[i]);
            i++;
        }
    }
    return (0);
}