#include "minishell.h"

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
        if (pipe[i] == '|' && pipe[i - 1] == ' ' && pipe[i + 1] == ' ')
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
        if (cmd[i] == '|' && cmd[i - 1] == ' ' && cmd[i + 1] == ' ')
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
        if (line[i] == '|' && line[i - 1] == ' ' && line[i + 1] == ' ')
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
    pipes = malloc(sizeof(char*) * alloc_pipe(line) + 1);
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

int main(int argc, char **argv)
{
    int i;
    char **str;
    char *line;

    i = 1;
    // while (i < argc)
    // {
    //     line = ft_strjoin(line, argv[i]);
    //     i++;
    // }
    str = split_pipe(argv[1]);
    i = 0;
    while (str[i] != NULL)
    {
        printf("%s\n", str[i]);
        i++;
    }
    return (0);
}