#include "../minishell.h"

// int exec_cmds(int in, int out, t_command *command)
// {

// }


//TO FIX
// int execution(t_pline *p_line, t_env_var *env)

int execution(t_pline *p_line,char **env, t_env_var *lenv)
{
    int in;
    int out;
    int fd[2];
    int red[2];
    t_pline *iter;
    pid_t pid;
	char *path;

    out = dup(STDOUT_FILENO);
    in = dup(STDIN_FILENO);
    iter = p_line;
    int waits;


    waits = 0;
    while (iter)
    {
        pipe(fd);
        if (files_io_redirecions(fd, iter->file, red) == 1) {
            printf("open(): %s\n", strerror(errno));
            exit(EXIT_FAILURE);
            continue;
        }
        pid = fork();
        if (pid == 0)
        {
            if(iter->next || red[1] != -1)
            {
                printf("dkhe;");
                dup2(fd[1], STDOUT_FILENO);
            }
            if(red[0] != -1)
            {
                printf("gg");
                dup2(fd[0], STDIN_FILENO);
            }
            close(fd[0]);
            close(fd[1]);
			path = path_finder(iter->command->command, lenv);//check if path true
			char **ptr = malloc(sizeof(char *) * 3);
            ptr[2] = NULL;
            ptr[0] = iter->command->command;
            ptr[1] = iter->command->next->command;
            execve(path, ptr , env);
            exit(0);
        }
        else
        {
            close(fd[1]);
            if(iter->next)
                dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
        }
        iter = iter->next;
        waits++;
    }
    dup2(out, STDOUT_FILENO);
    close(out);
    dup2(in, STDIN_FILENO);
    close(in);
    while(waits--)
        wait(NULL);
    return(0);
}