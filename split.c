#include "minishell.h"

int	ft_wdcounter(char const *str, char c)
{
	int	words;
	int	i;
	char q;
	int  test;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i])
			words++;
		while (str[i] != c && str[i] != '\0')
		{
			if (str[i] == 34 || str[i] == 39)
			{
				q = str[i++];
				while (str[i] != q)
					i++;
				i++;
			}
			else
				i++;
		}
		test = 0;
	}
	return (words);
}

static char	**memory_giver(char const *str, char c)
{
	char	**res;
	int		letters;
	int		i;
	int		j;
	char	q;

	res = (char **)malloc(sizeof(char *) * (ft_wdcounter(str, c) + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		letters = 0;
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i] != '\0')
		{
			//letters++;
			if (str[i] == 34 || str[i] == 39)
			{
				q = str[i++];
				while (str[i] != q)
				{
					i++;
					letters++;
				}
				i++;
			}
			else
			{
				i++;
				letters++;
			}
		}
		if (letters > 0)
			res[j++] = (char *)malloc(sizeof(char) * letters + 1);
	}
	res[j] = 0;
	return (res);
}

char	**ft_split(char const *str, char c)
{
	char	**res;
	int		i;
	int		j;
	int		str_number;
	int		size;
	char 	q;

	if (str == NULL)
		return (NULL);
	size = ft_wdcounter(str, c);
	res = memory_giver(str, c);
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
		{
			if (str[i] == 34 || str[i] == 39)
			{
				q = str[i++];
				while (str[i] != q)
					res[str_number][j++] = str[i++];
				i++;
			}
			else
				res[str_number][j++] = str[i++];
		}
		res[str_number][j] = '\0';
		str_number++;
	}
	return (res);
}
