#include "minishell.h"

int     is_redirection(char c)
{
    if (c == '>' || c == '<')
        return (1);
    return (0);
}
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

char    *quote_handler(char *name, char *str, int *i)
{
    char q;
    char *s;

    s = malloc(2);
    q = str[*i];
    printf("--%d %c\n",*i,str[*i]);
    (*i)++;
    while (str[*i])
    {
        if (str[*i] == q)
        {
            (*i)++;
            return (name);
        }
        s[0] = str[*i];
        s[1] = '\0';
        name = ft_strjoin(name, s);
        printf("--%d %c\n",*i,str[*i]);
        (*i)++;
    }
    if (str[*i] == '\0')
    {
        printf("error quotes\n");
        //exit(0);
    }
    return (NULL);
}

char    *get_file_name(char *str)
{
    int i;
    char *name;
    int j;
    char *s;

    i = 0;
    j = 0;
    s = (char *)malloc(2);
    name = "\0";
    while (str[i] == ' ' )
        i++;
    while (str[i] && str[i] != ' ' && !is_redirection(str[i]))
    {
        s[0] = str[i];
        s[1] = '\0';
        printf("after %d %s\n",i,str+i);
        if (str[i] == 39 || str[i] == 34)
        {
            name = quote_handler(name, str, &i);
            printf("%d\n",i);
        }
        else
        {
            name = ft_strjoin(name, s);
            i++;
        }
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

    tmp = file;
    new = (t_file *)malloc(sizeof(t_file));
    new->next = NULL;
    new->type = type;
    new->file = (get_file_name(str));
    if (!tmp)
        return (new);
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return file;
}

int       skipe_quote(char *str, int i)
{
    char q;

    q = str[i];
    if (str[i] != 39 && str[i] != 34)
        return (i);
    i++;
    while (str[i] != q)
        i++;
    if (str[i] != q)
    {
        printf("Error quote!\n");
        exit(1);
    }
    return (i);
}
t_file    *file(t_file *files, char *command)
{
    int i;
    int k;

    i = 0;
    while (command[i])
    {
        i = skipe_quote(command, i);
        if (command[i] == '>' && command[i + 1] == '>')
        {
            i += 2;
            files = file_add(files, command + i, 4);
        }
        else if (command[i] == '<' && command[i + 1] == '<')
        {
            i += 2;
            files = file_add(files, command + i, 3);
        }
        else if (command[i] == '>')
        {
            i += 1;
            files = file_add(files, command + i, 1);
        }
        else if (command[i] == '<')
        {
            i += 1;
            files = file_add(files, command + i, 2);
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
    int     i;
    char **str;
    char *line;
    int g;
    t_file *filee;

    //filee = (t_file *)malloc(sizeof(t_file));
    filee = NULL;
    while (1)
    {
        line = readline("shell> ");
        if  (!line)
            exit(0);
        if (line[0] == '\0')
            ;
        else
        {
            add_history(line);
            str = split_pipe(line);
            i = 0;
            printf("(%s)\n", str[0]);
            filee = file(filee, str[0]);
            
            while (filee)
            {
                printf("type = %d file_name = %s\n",filee->type, filee->file);
                filee = filee->next;
            }
        }
    }
    return (0);
}