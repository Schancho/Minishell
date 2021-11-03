#include "../../minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t sn;

	sn = n;
	if (!dst && !src)
		return (NULL);
	if (src == dst)
		return (dst);
	while (n--)
		*(unsigned char *)dst++ = *(unsigned char *)src++;
	return (dst - sn);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	sumlen;

	if (!s1)
		return (NULL);
	sumlen = ft_strlen(s1) + ft_strlen(s2);
	if (!(ret = malloc(sizeof(char) * (sumlen + 1))))
		return (NULL);
	ft_memcpy(ret, s1, ft_strlen(s1));
	ft_memcpy(ret + ft_strlen(s1), s2, ft_strlen(s2));
	ret[sumlen] = 0;
	return (ret);
}