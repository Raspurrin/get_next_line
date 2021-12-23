/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:42:31 by mialbert          #+#    #+#             */
/*   Updated: 2021/12/23 21:57:14 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include "get_next_line_utils.c"

// merge remainder and buf to avoid allocation of memory for buf
// memset buf while reading
// freeing in strjoin and such

#include <stdio.h>

static char	*ft_trim(char *line, char *buf)
{
	ssize_t		buflen;
	size_t		linelen;

	linelen = 0;
	while (line[linelen] != '\n')
		linelen++;
	linelen++;
	buflen = (ft_strlen(line) - linelen);
	if (buflen != 0)
		ft_strlcpy(buf, line + linelen, buflen + 1);
	else
		ft_memset(buf, '\0', BUF_SIZE);
	line = ft_substr(line, 0, linelen + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	ssize_t		buflen;
	static char	buf[BUF_SIZE + 1];

	line = ft_calloc(1, 1);
	if (!line)
		return (NULL);
	if (buf[0] != '\0')
		line = ft_strjoin(line, buf);
	while (!(ft_strchr(buf, '\n')))
	{
		ft_memset(buf, '\0', BUF_SIZE);
		buflen = read(fd, buf, BUF_SIZE);
		if (buflen <= 0 && ft_strlen(line) == 0)
		{
			free (line);
			return (NULL);
		}
		if (buflen < BUF_SIZE && !(ft_strchr(buf, '\n')))
		{
			line = ft_strjoin(line, buf);
			ft_memset(buf, '\0', BUF_SIZE);
			return (line);
		}
		buf[buflen] = '\0';
		line = ft_strjoin(line, buf);
	}
	line = ft_trim(line, buf);
	return (line);
}

int	main(void)
{
	int	fd;

	fd = open("test.txt", 0);
	if (!fd)
		return (0);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	close(fd);
	return (0);
}
