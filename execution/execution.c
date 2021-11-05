#include "execution.h"

int exec_cmds(t_pline *p_line,t_env_var *lenv, int *fd, t_garbage **g)
{
	pid_t pid;
	char **tokens;
	char *path;

	tokens = conv_cmd(p_line->command);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (p_line->next)
			dup2(fd[1], STDOUT_FILENO);
		frederictions(fd, p_line->file);
		close(fd[1]);
		path = path_finder(tokens[0], lenv);
		execve(path, tokens, environment_var(lenv, g));
		exit(0);
	}
	return (0);
}

int exec_pline(t_pline *p_line, t_env_var *lenv, t_garbage **g)
{
	int in;
	int out;
	t_pline *iter;
	int nop;
	int fd[2];

    out = dup(STDOUT_FILENO);
    in = dup(STDIN_FILENO);
	iter = p_line;
	nop = 0;
	while (iter)
	{
		pipe(fd);
		exec_cmds(iter, lenv, fd, g);
		close(fd[1]);
		if(iter->next)
            dup2(fd[0], STDIN_FILENO);
		iter=iter->next;
		nop++;
	}
    dup2(out, STDOUT_FILENO);
	close(out);
    dup2(in, STDIN_FILENO);
	close(in);
	//tell parent to wait for child procees's
	//parent(?)
	while(nop--)
        wait(NULL);
	return(0);
}