#include <stdio.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char **argv)
{
	int i = 0;
	int fd;
	char *line;

	fd = open("123",O_CREAT | O_RDWR, 0666);
	line = readline("heredoc> ");
	 //line = "heloo world";
	 write(fd, line, strlen(line));
	 close(fd);
	return(0);
}
