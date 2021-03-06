#include "minishell.h"

void        garbage(t_garbage **garbage, void *address)
{
    t_garbage *new;

    new = (t_garbage *)malloc(sizeof(t_garbage));
    new->next = *(garbage);
    new->garb = address;
    *garbage = new;
}

int     is_redirection(char c)
{
    if (c == '>' || c == '<')
        return (1);
    return (0);
}
//malloc;
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
        if (pipe[i++] == '|' && is_valide_pipe(pipe + i))
            p++;
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

char    *command(char *cmd, int j, int m, t_garbage **g)
{
    int i;
    int k;
    char *str;

    i = 0;
    k = m - j + 1;
    str = malloc(k);
    garbage(g, str);
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

char    **split_pipe(char *line, t_garbage **g)
{
    int i;
    int j;
    int k;
    int m;
    char **pipes;
    
    j = 0;
    k = alloc_pipe(line);
    // printf ("%d\n", k);
    pipes = (char**)malloc(sizeof(char*) * (k + 1));
    garbage(g, pipes);
    i = 0;
    m = 0;
    while (i < k)
    {
        m = end(line + j) + j;
        pipes[i] = command(line,j,m, g);
        j = m + 1;
        i++;
    }
    pipes[i] = NULL;
    return pipes;
}

char    *quote_handler(char *name, char *str, int *i, t_garbage **g)
{
    char q;
    char *s;
    char k;

    s = malloc(2);
    garbage(g, s);
    q = str[*i];
     s[0] = str[*i];//
     s[1] = '\0';//
     name = ft_strjoin(name, s, g);//
     k = 0;//
    (*i)++;
    while (str[(*i)++])
    {
        if (str[*i] == q)
        {    
            s[0] = str[*i];//
            (*i)++;
            name = ft_strjoin(name, s,g);//
            free(s);
            return (name);
        }
        s[0] = str[*i];
        s[1] = '\0';
        name = ft_strjoin(name, s,g);
        //(*i)++;
    }
    if (str[*i] == '\0')
    {
        printf("eerror quotes\n");
        exit(0);
    }
    free(s);
    return (NULL);
}

char    *get_file_name(char *str, t_garbage **g)
{
    int i;
    char *name;
    int j;
    char *s;

    i = 0;
    j = 0;
    s = (char *)malloc(2);
    garbage(g, s);
    name = "\0";
    while (str[i] == ' ' )
        i++;
    while (str[i] && str[i] != ' ' && !is_redirection(str[i]))
    {
        s[0] = str[i];
        s[1] = '\0';
        if (str[i] == 39 || str[i] == 34)
        {
            name = quote_handler(name, str, &i, g);
        }
        else
        {
            name = ft_strjoin(name, s, g);
            i++;
        }
        j++;
    }
    if (j == 0)
    {
        printf("syntax error near unexpected token\n");
        exit (1);
    }
    free(s);
    return (name);
}

t_file  *file_add(t_file *file, char *str, int type, t_garbage **g)
{
    t_file *new;
    t_file *tmp;

    tmp = file;
    new = (t_file *)malloc(sizeof(t_file));
    garbage(g, new);
    new->next = NULL;
    new->type = type;
    new->file = (get_file_name(str,g));
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
t_file    *file(t_file *files, char *command, t_garbage **g)
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
            files = file_add(files, command + i, F_OUTPUT, g);
            k = 1;
        }
        else if (command[i] == '<' && command[i + 1] == '<')
        {
            i += 2;
            files = file_add(files, command + i, F_HEREDOC, g);
            k = 1;
        }
        else if (command[i] == '>')
        {
            i += 1;
            files = file_add(files, command + i, F_OUTPUT, g);
            k = 1;
        }
        else if (command[i] == '<')
        {
            i += 1;
            files = file_add(files, command + i, F_INPUT, g);
            k = 1;
        }
        if (k != 1)
            i++;
    }
    return (files);
}


t_pipe  *add_pipe_line(t_pipe *pipe, char *cmd, t_garbage **g)
{
    t_pipe *new;
    t_pipe *tmp;

    tmp = pipe;
    new = (t_pipe *)malloc(sizeof(t_pipe));
    garbage(g, new);
    new->pipe_line = strdup(cmd);
    garbage(g, new->pipe_line);
    new->next = NULL;
    while (tmp)
        tmp = tmp->next;
    tmp = new;
    return pipe;
}
t_pipe  *pipe_line(t_pipe *p, char **command, t_garbage **g)
{
    int i;

    while (command[i])
    {
        p = add_pipe_line(p, command[i], g);
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

char    *delete_red(char *str, t_garbage **g)
{
    char *ret;
    char *s;
    int i;
    char q;

    s = malloc(2);
    ret = malloc(1);
    garbage(g, s);
    garbage(g,ret);
    s[1] = '\0';
    ret[0] = '\0';
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == 34 || str[i] == 39)
        {
            q = str[i];
            if (str[i + 1] == q)
            {
                s[0] = str[i];
                ret = ft_strjoin(ret, s, g);
                ret = ft_strjoin(ret, s, g);
                i = i + 2;
            }
            else
            {
                s[0] = str[i];
                ret = ft_strjoin(ret, s, g);
                i++;
                while (str[i] != q)
                {
                    
                    s[0] = str[i];
                    if (str[i] != q)
                        ret = ft_strjoin(ret, s,g);
                    i++;
                }
                s[0] = str[i];
                ret = ft_strjoin(ret, s, g);
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
            ret = ft_strjoin(ret, s, g);
            i++;
        }
        
    }
    free(s);
    return (ret);
}

t_command   *command_parser(t_command *cmd, char *str, t_garbage **g)
{
    t_command *tmp;
    t_command *new;

    tmp = cmd;
    new = (t_command *)malloc(sizeof(t_command));
    garbage(g, new);
    new->next = NULL;
    new->command = strdup(str);
    garbage(g , new->command);
    if(!tmp)
        return (new);
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return (cmd);
}

t_command   *get_command(t_command *cmd, char *command, t_garbage **g)
{
    char **str;
    int i;

    i = 0;
    str = ft_split(delete_red(command,g), ' ', g);
    while (str[i])
    {
        cmd = command_parser(cmd, str[i], g);
        i++;
    }
    return cmd; 
}

t_pline     *pipeline(t_pline *pipe, t_file *file, t_command *cmd, t_garbage **g)
{
    t_pline *new;
    t_pline *tmp;

    tmp = pipe;
    new = (t_pline *)malloc(sizeof(t_pline));
    garbage(g, new);
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

t_pline     *pline(t_pline *p_line, t_file *files, t_command *cmd, char *str, t_garbage **g)
{
    files = file(files, str, g);
    cmd = get_command(cmd, str, g);
    p_line = pipeline(p_line, files, cmd, g);
    return (p_line);
}

t_line  *command_line(t_line *line, t_pline *pipe, t_garbage **g)
{
    t_line *tmp;
    t_line *new;

    tmp = line;
    new = (t_line *)malloc(sizeof(t_line));
    garbage(g, new);
    new->next = NULL;
    new->pipe_line = pipe;
    if (!tmp)
        return (new);
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return (line);  
}

char    *search_env_var(t_env_var *env, char *str)
{
    int i;
    int l;

    i = 0;
    l = strlen(str);
    while (env)
    {
        if (strncmp(env->env, str, l) == 0 && env->env[l] == '=')
            return (env->env + l + 1);
        env = env->next;
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

// t_env_var   *search_env_var(t_env_var *env, char *key)
// {

// }

t_env_var   *remove_env_var(t_env_var *env, char *key)
{
    t_env_var *tmp;
    t_env_var *prev;

    tmp = env;
    if (tmp != NULL && strcmp(tmp->value, key) == 0)
    {
        env = env->next;
        free(tmp);
        return (env);
    }
    while (tmp && strcmp(tmp->value, key) != 0)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
    {
        printf("There's no environment variable named %s\n",key);
        exit(1);
    }
    prev->next = tmp->next;
    free(tmp);
    return (env);
}

t_env_var   *add_var_to_env(t_env_var *env, char *var, t_garbage **g)
{
    t_env_var *new;

    new = (t_env_var *)malloc(sizeof(t_env_var));
    garbage(g, new);
    new->env = strdup(var);
    garbage(g, new->env);
    new->var = strchr(var, '=') + 1;
    var[strlen(var) - strlen(strchr(var, '='))] = '\0';
    new->value = var;
    new->next = env;
    return (new);
}

t_env_var   *clone_env(t_env_var *env_var, char **env, t_garbage **g)
{
    int i;

    i = 0;
    while (env[i])
    {
        env_var = add_var_to_env(env_var, env[i], g);
        i++;
    }
    return (env_var);
}

char    **environment_var(t_env_var *environment, t_garbage **g)
{
    char **env;
    t_env_var *tmp;
    int i;

    tmp = environment;
    int len;
    while (tmp)
    {
        tmp = tmp->next;
        len++;
    }
    env = (char **)malloc(sizeof(char*) * (len + 1));
    garbage(g, env);
    i = 0;
    while (environment)
    {
        env[i] = environment->env;
        environment = environment->next;
        i++;
    }
    env[i] = NULL;
    return (env);
}

int     is_alpha_num(char c)
{
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    return (0);
}

int     skip_env(char *str)
{
    int i;

    i = 0;
    while (is_alpha_num(str[i]) || str[i] == '_')
        i++;
    return i;

}

char    *get_env_va(char *str, t_garbage **g)
{
    int i;
    char *ret;
    char *s;
    s = malloc(2);
    ret = malloc(1);
    garbage(g, s);
    garbage(g, ret);
    s[1] = '\0';
    ret[0] = '\0';
    i = 0;
    while (is_alpha_num(str[i]) == 1 || str[i] == '_')
    {
        s[0] = str[i];
        ret = ft_strjoin(ret, s, g);
        i++;
    }
    free(s);
    return (ret);
}

char    *expander(t_env_var *env, char *str, t_garbage **g)
{
    char *ret;
    char *s;
    int i;
    char q;

    ret = malloc(1);
    s = malloc(2);
    garbage(g, ret);
    garbage(g, s);
    s[1] = '\0';
    ret[0] = '\0';
    i = 0;
    while (str[i])
    {
        if (str[i] && (str[i] == 34 || str[i] == 39))
        {
            q = str[i];
            i++;
            if (q == 39)
            {
                while (str[i] && str[i] != 39)
                {
                    s[0] = str[i]; 
                    ret = ft_strjoin(ret, s, g);
                    i++;
                }
            }
            else
            {
                while (str[i] && str[i] != q)
                {
                    if (str[i] == '$' && str[i + 1] != '$')
                    {
                        if (search_env_var(env, get_env_va(str + i + 1, g)))
                            ret = ft_strjoin(ret, search_env_var(env, get_env_va(str + i + 1, g)), g);
                        i = skip_env(str + i + 1) + i + 1;
                    }
                    else
                    {
                        s[0] = str[i];
                        if (s[0] != q)
                            ret = ft_strjoin(ret, s, g);
                        i++;
                    }
                }
            }
            if (str[i] == '\0')
            {
                free(s);
                return (ret);
            }
            i++;
        }
        if (str[i] == '$' && str[i + 1] != '$')
        {
            if (search_env_var(env, get_env_va(str + i + 1, g)))
                ret = ft_strjoin(ret, search_env_var(env, get_env_va(str + i + 1, g)), g);
            i = skip_env(str + i + 1) + i;

        }
        else
        {
            s[0] = str[i];
            if (s[0] != 34 && s[0] != 39)
                ret = ft_strjoin(ret, s, g);
        }
        if (str[i] == '\0')
        {
            free(s);
            return (ret);
        }
        i++;
    }
    if (ret[0] == '\0')
    {
        free(s);
        return (NULL);
    }
    free(s);
    return (ret);
}

t_command   *remove_command_null_element(t_command *command)
{
    t_command *tmp;
    t_command *prev;

    tmp = command;
    if (tmp != NULL && tmp->command == NULL)
    {
        command = command->next;
        free(tmp);
        return (command);
    }
    while (tmp && tmp->command != NULL)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return (command);
    prev->next = tmp->next;
    free(tmp);
    return (command);
}

t_file      *remove_file_null_element(t_file *file)
{
    t_file *tmp;
    t_file *prev;

    tmp = file;
    if (tmp != NULL && tmp->file == NULL)
    {
        file = file->next;
        free(tmp);
        return (file);
    }
    while (tmp && tmp->file != NULL)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return (file);
    prev->next = tmp->next;
    free(tmp);
    return (file);
}

t_command   *command_delete_null(t_command *cmd)
{
    t_command *tmp;
    
    tmp = cmd;
    while (tmp)
    {
        cmd = remove_command_null_element(cmd);
        tmp = tmp->next;
    }
    return (cmd);
}

t_file      *file_delete_null(t_file *file)
{
    t_file *tmp;
    
    tmp = file;
    while (tmp)
    {
        file = remove_file_null_element(file);
        tmp = tmp->next;
    }
    return (file);
}

char        *heredoc(char **file_list, char* stop, t_garbage **g, int *f)
{
        int fd;
        char *file_name;
        char *line;

        line = readline("heredoc> ");
        file_name = ft_strjoin(strdup("/tmp/file"), ft_itoa(*f), g);
        fd = open(file_name, O_CREAT | O_RDWR, 0777);
        while (strcmp(line, stop) != 0)
        {
            line = readline("heredoc> ");
            write(fd, line, strlen(line));
            write(fd, "\n", 1);
        }
            
        //file_list = add_to_file_list(file_list, file_name);
    return (file_name);
}

t_pline     *expansion(t_env_var *env, t_pline *line, t_garbage **g, char ***file_list)
{
    t_pline *tmp;
    t_file *file;
    t_command *cmd;
    int f=0;

    tmp = line;
    while (tmp)
    {
        cmd = tmp->command;
        while (cmd)
        {
            cmd->command = expander(env, cmd->command, g);
            cmd = cmd->next;
        }
        tmp->command = command_delete_null(tmp->command);
        file = tmp->file;
        while (file)
        {
            if (file->type != 3)
                file->file = expander(env, file->file, g);
            else if (file->type == 3)
            {
                file->file = heredoc(*file_list, file->file, g, &f);
            }
            file = file->next;
        }
        tmp->file = tmp->file;
        if (tmp)
            tmp = tmp->next;
    }
    return (line);
}

// char    *conv_cmd(t_command *cmd)
// {
//     char **str;
//     int i;

//     i = 0;
//     while (cmd)
//     {
//         str[i] = cmd->command;
//         i++;
//         cmd = cmd->next;
//     }
//     str[i] = 0;
//     return str;
// }

// t_line  *c_line(t_pline *p_line, t_garbage **g)
// {
//     t_line  *line;
//     t_line  *l_tmp;
//     t_pline *p_tmp;

    
//     p_tmp = p_line;
//     while (p_tmp)
//     {
//         l_tmp->file = p_line->file;
//         l_tmp->command = conv_cmd(p_line->command);
//         l_tmp = l_tmp->next;
//         p_line = p_line->next;
//     }

// }


int     sizeof_string_table(t_command *cmd)
{
    int i;
    int j;
    char **str;
    
    i = 0;
    while (cmd)
    {
        str = _split(cmd->command, ' ');
        j = 0;
        while (str[j])
        {
            i++;
            j++;
        }
        if(j == 0)
            i++;
        cmd = cmd->next;
    }
    return (i);
}

char    **conv_cmd(t_command *cmd)
{
    int i;
    int j;
    char **str;
    char **ret;
    
    i = 0;
    ret = (char **)malloc(sizeof(char *) * (sizeof_string_table(cmd) + 1));
    while (cmd)
    {
        str = _split(cmd->command, ' ');
        j = 0;
        while (str[j])
        {
            ret[i] = str[j];
            i++;
            j++;
        }
        if(j == 0)
        {
            ret[i] = str[0];
            i++;
        }
        cmd = cmd->next;
    }
    ret[i] = NULL;
    return (ret);
}

int main(int argc, char **argv, char **env)
{
    int     i;
    int     k;
    char **str;
    char *line;
    int j;
    t_file *files;
    t_command *command;
    t_pline *p_line;
    t_env_var *en;
    t_env_var *tmp;
    t_pline *temp;
    char **aff;
    char *test;
    t_garbage *g;
    //t_line  *command_line;
    
    
    p_line = NULL;
    command = NULL;
    char *cmd;
    //char **command;

    files = NULL;

    
    //signal(SIGINT, reline);
    en = NULL;
    en = clone_env(en, env, &g);
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
            str = split_pipe(line, &g);
            i = 0;
            while (str[i])
            {
                p_line = pline(p_line, files, command, str[i], &g);
                i++;
            }
            p_line = expansion(en, p_line, &g, &str);
            //p_line = heredoc(p_line, )
            aff = conv_cmd(p_line->command);
            //command_line = c_line(p_line, &g);
           // exec_pline(p_line, en, &g);
           // cmd = strdup("ef")
            // cmd = expander(en, argv[1]);
            // tmp = en;
            // while (tmp)
            // {
            //     printf("env: %s key: %s var: %s\n", tmp->env, tmp->value, tmp->var);
            //     tmp = tmp->next;
            // }
            // cmd = strdup("slimane=kajdsbnnkjdas");
            // printf ("******************************************\n");
            // en = add_var_to_env(en, cmd);
            //  aff = environment_var(en);
            i = 0;
            // printf("-- |%s|\n", aff[0]);
            // while (aff[i])
            // {
            //     printf("-- |%s|\n", aff[i]);
            //     i++;
            // }
            // tmp = en;
            // while (tmp)
            // {
            //     printf("env: |%s| key: |%s| var: |%s|\n", tmp->env, tmp->value, tmp->var);
            //     tmp = tmp->next;
            // }
            // test = search_env_var(en, "slimane");
            // printf("test: %s\n", test);
            // cmd = strdup("slimane");
            // printf("adddddiiiiiiiing\n");
            // en = remove_env_var(en, cmd);
            // tmp = en;
            // while (tmp)
            // {
            //     printf("env: |%s| key: |%s| var: |%s|\n", tmp->env, tmp->value, tmp->var);
            //     tmp = tmp->next;
            // }
            // while (env[i])
            //     printf("%s\n",env[i++]);
            // cmd = env_var(env, line);
            // printf("env var: %s\n", cmd);
             temp = p_line;
            i = 1;
            while (temp)
            {
                printf("pipeline N %d: \n",i);
                j = 1;
                aff = conv_cmd(p_line->command);
                k = 0;
                while (aff[k])
                {
                    printf("    command N %d: %s\n",j,aff[k]);
                    k++;
                    j++;
                }
                j = 1;
                while (temp->file)
                {
                    printf("    file N %d: %s Type %d\n",j,temp->file->file, temp->file->type);
                    temp->file = temp->file->next;
                    j++;
                }
                temp = temp->next;
                i++;
            }
            // i = 0;
            // while (str[i])
            // {
            //     free(str[i]);
            //     i++;
            // }
            // free(str);
            // temp = p_line;
            // while (temp)
            // {
            //     while (temp->command)
            //     {
            //         free(temp->command->command);
            //         temp->command = temp->command->next;
            //         j++;
            //     }
            //     free(temp->command);
            //     while (temp->file)
            //     {
            //         free(temp->file->file);
            //         temp->file = temp->file->next;
            //     }
            //     free(temp->file);
            //     temp = temp->next;
            // }
            // free(temp);
            //free(p_line);
            //str = NULL;
            // cmd = expander(en, p_line->file->file);
            // printf("var : %s\n", cmd);
            //p_line = temp;
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
            free(line);
            p_line = NULL;
            

        }
        //system("leaks minishell");
    }
    return (0);
}
/*
linked list :
            var=dddddd
            var
            dddddd

char *expand(char *old_token);
linked_list clone_env(char **env);
add_env to linkedlist
remove env linkedlist
search env in linked list
conver env to char ** in this format xx=ddddd
*/
/*
    >> 1expand

*/