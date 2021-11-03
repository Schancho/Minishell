#include "../minishell.h"

int files_io_redirecions(int *fd, t_file * iter, int *red)
{
    red[0] = -1;
    red[1] = -1;

    while(iter)
    {
        if (iter->type == F_INPUT)
        {
            close(fd[0]);
            fd[0] = open(iter->file, O_RDONLY);
            red[0] = fd[0];
            if (fd[0] == -1)
                return(1);
        }
        else if(iter->type == F_OUTPUT)
        {
            close(fd[1]);
            fd[1] = open(iter->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            red[1] = fd[1];
            if (fd[1] == -1)
                return(1);
        }
        else if(iter->type == F_APPEND)
        {
            close(fd[1]);
            fd[1] = open(iter->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
            red[1] = fd[1];
            if (fd[1] == -1)
                return(1);
        }
        iter = iter->next;
    }
    return(0);
}