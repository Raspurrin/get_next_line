/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:56:40 by mialbert          #+#    #+#             */
/*   Updated: 2021/12/14 23:24:18 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_bzero(void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((uint8_t *)src)[i++] = '\0';
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;

	ptr = malloc(num * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, num * size);
	return (ptr);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = ft_strlen((char *)src);
	i = 0;
	if (size == 0)
		return (len);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	return (len);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && dst != src)
	{
		((uint8_t *)dst)[i] = ((uint8_t *)src)[i];
		i++;
	}
	return (dst);
}

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*out;

	len = ft_strlen((char *)str) + 1;
	out = malloc(len * sizeof(char));
	if (!out)
		return (NULL);
	ft_memcpy(out, str, len);
	return (out);
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (!dst && !src)
		return (NULL);
	if (src > dst)
		return (ft_memcpy(dst, src, n));
	while (n-- > 0)
		((uint8_t *)dst)[n] = ((uint8_t *)src)[n];
	return (dst);
}

char	*ft_strchr(const char *str, int32_t c)
{
	char	*str2;

	if (c < 0 || c > 255)
		return ((char *)str);
	str2 = (char *)str;
	while (*str2 != c && *str2)
		str2++;
	if (*str2 == c)
		return (str2);
	return (0);
}

char	*ft_strjoin(char const *str1, char const *str2)
{
	size_t	str1len;
	size_t	str2len;
	char	*out;

	if (!str1 || !str2)
		return (0);
	str1len = ft_strlen(str1);
	str2len = ft_strlen(str2);
	out = ft_calloc((str1len + str2len + 1), sizeof(char));
	if (!out)
		return (0);
	ft_strlcpy(out, str1, str1len + 1);
	ft_strlcpy(out + str1len, str2, str2len + 1);
	return (out);
}

char	*ft_substr(char const *str, uint32_t start, size_t len)
{
	char	*out;
	size_t	slen;

	slen = ft_strlen(str);
	if (!str)
		return (NULL);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		return (ft_strdup(str + start));
	out = malloc((len + 1) * sizeof(char));
	if (!out)
		return (NULL);
	ft_memcpy(out, str + start, len);
	out[len] = '\0';
	return (out);
}
