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
    char q;

    i = 0;
    q = pipe[i];
    i++;
    while (pipe[i])
    {
        if (pipe[i] == q)
            return (i);
        i++;
    }
    printf("Quote error\n");
    exit (1);
}

int     is_valide_pipe(char *pipe)
{
    int i;

    i = 0;
    while (pipe[i] && pipe[i] == ' ')
        i++;
    if (pipe[i] == '|')
    {
        printf("syntax error near unexpected token `|'\n");
        exit (1);
    }
    if (pipe[i] == '\0')
    {
        printf("syntax error: Invalide pipe\n");
        exit (1);
    }
    return (1);
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
        while (pipe[i] == 34 || pipe[i] == 39)
        {
            j = valid_quote(pipe + i);
            i = i + j + 1;
        }
        if (pipe[i] == '|' && is_valide_pipe(pipe + i + 1))
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
    char q;

    p = 0;
    i = 0;
    while (line[i])
    {
        if (line[i] == 34 || line[i] == 39)
        {
            q = line[i];
            i++;
            while (line[i])
            {
                if (line[i] == q)
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
        pipes[i] = command(line,j,m);
        j = m + 1;
        i++;
    }
    pipes[i] = NULL;
    return pipes;
}

char    *quote_handler(char *name, char *str, int *i)
{
    char q;
    char *s;
    char k;

    s = malloc(2);
    q = str[*i];
     s[0] = str[*i];//
     s[1] = '\0';//
     name = ft_strjoin(name, s);//
     k = 0;//
    (*i)++;
    while (str[*i])
    {
        if (str[*i] == q)
        {
            
            s[0] = str[*i];//
            (*i)++;
            name = ft_strjoin(name, s);//
            return (name);
        }
        s[0] = str[*i];
        s[1] = '\0';
        name = ft_strjoin(name, s);
        (*i)++;
    }
    if (str[*i] == '\0')
    {
        printf("eerror quotes\n");
        exit(0);
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
        if (str[i] == 39 || str[i] == 34)
        {
            name = quote_handler(name, str, &i);
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
        k = 0;
        i = skipe_quote(command, i);
        if (command[i] == '>' && command[i + 1] == '>')
        {
            i += 2;
            files = file_add(files, command + i, 4);
            k = 1;
        }
        else if (command[i] == '<' && command[i + 1] == '<')
        {
            i += 2;
            files = file_add(files, command + i, 3);
            k = 1;
        }
        else if (command[i] == '>')
        {
            i += 1;
            files = file_add(files, command + i, 1);
            k = 1;
        }
        else if (command[i] == '<')
        {
            i += 1;
            files = file_add(files, command + i, 2);
            k = 1;
        }
        if (k != 1)
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

char    *get_red_to_delete(char *str)
{
    return NULL;
}

int     skip_redirection(char *str, int i)
{
    char q;

    while (str[i] && str[i] == ' ')
        i++;
    while (str[i] && str[i] != ' ')
    {
        if (str[i] == 34 || str[i] == 39)
        {
            q = str[i];
            i++;
            while (str[i] != q)
                i++;
        }
        i++;
    }
    return (i);
}

char    *delete_red(char *str)
{
    char *ret;
    char *s;
    int i;
    char q;

    s = malloc(2);
    ret = malloc(1);
    s[1] = '\0';
    ret[0] = '\0';
    i = 0;
    while (str[i])
    {
        if (str[i] == 34 || str[i] == 39)
        {
            q = str[i];
            if (str[i + 1] == q)
                i = i + 2;
            else
            {
                s[0] = str[i];
                ret = ft_strjoin(ret, s);
                i++;
                while (str[i] != q)
                {
                    s[0] = str[i];
                    if (str[i] != q)
                        ret = ft_strjoin(ret, s);
                    i++;
                }
                s[0] = str[i];
                ret = ft_strjoin(ret, s);
                i++;
            }
        }
        else if (is_redirection(str[i]))
        {
            i++;
            if (is_redirection(str[i]))
                i++;
            i = skip_redirection(str, i) ;
        }
        else
        {
            s[0] = str[i];
            ret = ft_strjoin(ret, s);
            i++;
        }
    }
    return (ret);
}

t_command   *command_parser(t_command *cmd, char *str)
{
    t_command *tmp;
    t_command *new;

    tmp = cmd;
    new = (t_command *)malloc(sizeof(t_command));
    new->next = NULL;
    new->command = strdup(str);
    if(!tmp)
        return (new);
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return (cmd);
}

t_command   *get_command(t_command *cmd, char *command)
{
    char **str;
    int i;

    i = 0;
    str = ft_split(delete_red(command), ' ');
    while (str[i])
    {
        cmd = command_parser(cmd, str[i]);
        i++;
    }
    return cmd; 
}

t_pline     *pipeline(t_pline *pipe, t_file *file, t_command *cmd)
{
    t_pline *new;
    t_pline *tmp;

    tmp = pipe;
    new = (t_pline *)malloc(sizeof(t_pline));
    new->next = NULL;
    new->file = file;
    new->command = cmd;
    if (!tmp)
        return (new);
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return (pipe);
}

t_pline     *pline(t_pline *p_line, t_file *files, t_command *cmd, char *str)
{
    files = file(files, str);
    cmd = get_command(cmd, str);
    p_line = pipeline(p_line, files, cmd);
    return (p_line);
}

t_line  *command_line(t_line *line, t_pline *pipe)
{
    t_line *tmp;
    t_line *new;

    tmp = line;
    new = (t_line *)malloc(sizeof(t_line));
    new->next = NULL;
    new->pipe_line = pipe;
    if (!tmp)
        return (new);
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return (line);  
}

char    *env_var(char **env, char *str)
{
    int i;
    int l;

    i = 0;
    l = strlen(str);
    while (env[i])
    {
        if (strncmp(env[i], str, l) == 0 && env[i][l] == '=')
            return (env[i] + l + 1);
        i++;
    }
    return (NULL);
}

void    reline(int sig)
{
    //signal(SIGINT, reline);
    //write(2, "\r",1);
    rl_on_new_line();
    //rl_replace_line("shell",STDIN_FILENO);
    rl_redisplay();
}

int main(int argc, char **argv, char **env)
{
    int     i;
    char **str;
    char *line;
    int j;
    t_file *files;
    t_command *command;
    t_pline *p_line;
    

    p_line = NULL;
    command = NULL;
    char *cmd;
    //char **command;

    files = NULL;
        
    
    signal(SIGINT, reline);
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
            while (str[i])
            {
                p_line = pline(p_line, files, command, str[i]);
                i++;
            }
            i = 1;
            // while (env[i])
            //     printf("%s\n",env[i++]);
            // cmd = env_var(env, line);
            // printf("env var: %s\n", cmd);
            while (p_line)
            {
                printf("pipeline N %d: \n",i);
                j = 1;
                while (p_line->command)
                {
                    printf("    command N %d: %s\n",j,p_line->command->command);
                    p_line->command = p_line->command->next;
                    j++;
                }
                j = 0;
                while (p_line->file)
                {
                    printf("    file N %d: %s Type %d\n",j,p_line->file->file, p_line->file->type);
                    p_line->file = p_line->file->next;
                    j++;
                }
                p_line = p_line->next;
                i++;
            }
            // p_line = pline(p_line, files, command, str[0]);
            // printf("command: |%s|\n file: %s\n",p_line->command->command, p_line->file->file);
            // i = 0;
            // printf("(%s)\n", str[0]);
            // files = file(files, str[0]);
            // cmd = delete_red(str[0]);
            // printf("cmd: |%s|\n",cmd);
            // command = get_command(command, str[0]);
            // i = 0;
            // while (command)
            // {
            //     printf("command %d: %s\n",i,command->command);
            //     command = command->next;
            //     i++;
            // }
            // while (files)
            // {
            //     printf("type = %d file_name = %s\n",files->type, files->file);
            //     files = files->next;
            // }
        }
    }
    return (0);
}
/*
linked list :
            var=dddddd
            var
            ddddddd

char *expand(char *old_token);
linked_list clone_env(char **env);
add_env to linkedlist
remove env linkedlist
search env in linked list
conver env to char ** in this format xx=ddddd
*/
