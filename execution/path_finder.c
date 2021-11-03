#include "../minishell.h"


char *path_finder(char *key, t_env_var *lenv)
{
	char *PATH;
	char **paths;
	struct stat	buf;
	int i = 0;

	key = ft_strjoin("/", key);
	PATH = search_env_var(lenv, "PATH");
	paths = _split(PATH, ':');
	while (paths[i])
	{
		if (!stat(ft_strjoin(paths[i], key), &buf))
			return(ft_strjoin(paths[i], key));
		i++;
	}
	return(NULL);
}