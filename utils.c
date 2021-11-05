#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	int	count;

	if (str == NULL)
		return (0);
	count = 0;
	while (str[count])
		count++;
	return (count);
}


char	*ft_strcat(char *dest, const char *src)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (dest != NULL)
	{
		while (dest[i] != '\0')
			++i;
	}
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		++j;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, char const *src)
{
	char *s;

	if (src == NULL)
		return (dest);
	s = dest;
	while ((*s++ = *src++))
		;
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2, t_garbage **g)
{
	char	*str;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc((len + 1));
	garbage(g, str);
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	return (str);
}

int	_wdcounter(char const *str, char c)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i])
			words++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (words);
}

static char	**_memory_giver(char const *str, char c)
{
	char	**res;
	int		letters;
	int		i;
	int		j;

	res = (char **)malloc(sizeof(char *) * (_wdcounter(str, c) + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		letters = 0;
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i] != '\0')
		{
			letters++;
			i++;
		}
		if (letters > 0)
			res[j++] = (char *)malloc(sizeof(char) * letters + 1);
	}
	res[j] = 0;
	return (res);
}

char	**_split(char const *str, char c)
{
	char	**res;
	int		i;
	int		j;
	int		str_number;
	int		size;

	if (str == NULL)
		return (NULL);
	size = _wdcounter(str, c);
	res = _memory_giver(str, c);
	if (res == NULL)
		return (NULL);
	i = 0;
	str_number = 0;
	while (str_number < size)
	{
		while (str[i] == c && str[i])
			i++;
		j = 0;
		while (str[i] != c && str[i])
			res[str_number][j++] = str[i++];
		res[str_number][j] = '\0';
		str_number++;
	}
	return (res);
}