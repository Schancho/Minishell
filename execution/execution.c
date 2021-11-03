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
    t_pline *iter;
    pid_t pid;
	char *path;

	//TO FIX
	// char **envv;
	// envv = environment_var(env);
	// int i;
	// i = 0;
	// // printf("-- |%s|\n", aff[0]);
	// while (envv[i])
	// {
	// 	printf("-- |%s|\n", envv[i]);
	// 	i++;
	// }

    out = dup(STDOUT_FILENO);
    in = dup(STDIN_FILENO);
    iter = p_line;

    while (iter)
    {
        pipe(fd);
        pid = fork();
        if (pid == 0)
        {
            close(fd[0]);
            if(iter->next)
                dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
			path = path_finder(p_line->command->command, lenv);//check if path true
			char **ptr = malloc(sizeof(char *) * 3);
            ptr[2] = NULL;
            ptr[0] = p_line->command->command;
            ptr[1] = p_line->command->next->command;
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
    }
    dup2(out, STDOUT_FILENO);
    close(out);
    dup2(in, STDIN_FILENO);
    close(in);
    waitpid(-1, NULL, 0);
    return(0);
}