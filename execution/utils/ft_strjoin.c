#include "../execution.h"

void	*_memcpy(void *dst, const void *src, size_t n)
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

char	*_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	sumlen;

	if (!s1)
		return (NULL);
	sumlen = _strlen(s1) + _strlen(s2);
	if (!(ret = malloc(sizeof(char) * (sumlen + 1))))
		return (NULL);
	_memcpy(ret, s1, _strlen(s1));
	_memcpy(ret + _strlen(s1), s2, _strlen(s2));
	ret[sumlen] = 0;
	return (ret);
}