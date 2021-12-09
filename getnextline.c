/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 21:14:26 by mialbert          #+#    #+#             */
/*   Updated: 2021/12/09 01:17:43 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "getnextline.h"

#include <stdio.h>

// int	ft_strlen(const char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }

// void	*ft_memcpy(void *dst, const void *src, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < n && dst != src)
// 	{
// 		((uint8_t *)dst)[i] = ((uint8_t *)src)[i];
// 		i++;
// 	}
// 	return (dst);
// }

// char	*ft_strdup(const char *str)
// {
// 	size_t	len;
// 	char	*out;

// 	len = ft_strlen((char *)str) + 1;
// 	out = malloc(len * sizeof(char));
// 	if (!out)
// 		return (NULL);
// 	ft_memcpy(out, str, len);
// 	return (out);
// }

char	*get_next_line(int fd)
{
	char	c;
	char	*buf;
	// char	*dup;
	size_t	i;

	i = 0;
	c = 'x';
	if (!fd)
		return (NULL);
	buf = malloc(BUF_SIZE + 1 * sizeof(char));
	while (i < BUF_SIZE && c != 0 && c != '\n')
	{
		if (read(fd, &c, 1))
			buf[i] = c;
		else if (i == 0)
			return (NULL);
		i++;
	}
	buf[i] = '\0';
	// dup = ft_strdup(buf);
	// buf += i;
	// printf("dup: %s\n", dup);
	return (buf);
}

int	main(void)
{
	int		fd;

	fd = open("test.txt", 0);
	if (!fd)
		return (0);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return (0);
}
