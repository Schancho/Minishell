#include "execution.h"


int frederictions(int *fd, t_file * iter)
{
    while(iter)
    {
        if (iter->type == F_INPUT)
        {
            close(fd[0]);
            fd[0] = open(iter->file, O_RDONLY);
			dup2(fd[0], STDIN_FILENO);
            if (fd[0] == -1)
                return(1);
        }
        else if(iter->type == F_OUTPUT)
        {
            close(fd[1]);
            fd[1] = open(iter->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			dup2(fd[1], STDOUT_FILENO);
            if (fd[1] == -1)
                return(1);
        }
        else if(iter->type == F_APPEND)
        {
            close(fd[1]);
            fd[1] = open(iter->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
			dup2(fd[1], STDOUT_FILENO);
            if (fd[1] == -1)
                return(1);
        }
        iter = iter->next;
    }
    return(0);
}
