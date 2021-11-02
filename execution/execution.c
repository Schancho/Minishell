#include "../minishell.h"

// int exec_cmds(int in, int out, t_command *command)
// {

// }

int execution(t_pline *p_line, char **env)
{
    int in;
    int out;
    int fd[2];
    t_pline *iter;
    pid_t pid;

    out = dup(STDOUT_FILENO);
    in = dup(STDIN_FILENO);
    iter = p_line;
    while (iter->next)
    {
        pipe(fd);
        pid = fork();
        if (pid == 0)
        {
            close(fd[0]);
            if(iter->next->next)
                dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            char **ptr = malloc(sizeof(char *) * 3);
            ptr[2] = NULL;
            ptr[0] = p_line->command->command;
            ptr[1] = p_line->command->next->command;
            // printf("path: %s, args: %s %s\n", ptr[0], ptr[0], ptr[1]);
            execve(p_line->command->command, ptr ,env);
            exit(0);
        }
        else
        {
            close(fd[1]);
            if(iter->next->next)
                dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
        }
        iter = iter->next;
    }
    dup2(out, STDOUT_FILENO);
    close(out);
    dup2(in, STDIN_FILENO);
    close(in);
    waitpid(-1, NULL, 0);
    return(0);
}