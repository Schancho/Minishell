#include "minishell.h"

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