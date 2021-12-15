/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 21:14:26 by mialbert          #+#    #+#             */
/*   Updated: 2021/12/15 10:37:43 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include "get_next_line_utils.c"

#include <stdio.h>

static void	*ft_free(char *buf)
{
	free(buf);
	return (NULL);
}

static char	*ft_trim(char *remainder, char *line, size_t buflen)
{
	size_t	i;

	i = 0;
	while (line[i] != '\n')
		i++;
	buflen = i + 1;
	while (line[buflen])
		buflen++;
	if ((buflen - i - 1) > 0)
		remainder = ft_substr(line, i + 1, (i + buflen - 1));
	line = ft_substr(line, 0, i + 1);
	return (remainder);
}

char	*get_next_line(int fd)
{
	size_t		buflen;
	char		*line;
	char		*buf;
	static char	*remainder;

	if (remainder)
		line = remainder;
	else
		line = "";
	buf = malloc(BUF_SIZE * sizeof(char));
	if (!buf || fd < 0)
		return (ft_free(buf));
	while (!(ft_strchr(buf, '\n')))
	{
		buflen = read(fd, buf, BUF_SIZE);
		if (buflen <= 0)
			return (ft_free(buf));
		buf[buflen] = '\0';
		line = ft_strjoin(line, buf);
	}
	remainder = ft_trim(remainder, line, buflen);
	return (line);
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
