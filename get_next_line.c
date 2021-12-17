/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 21:01:25 by mialbert          #+#    #+#             */
/*   Updated: 2021/12/17 22:01:56 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include "get_next_line_utils.c"

#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*buf;
	size_t		buflen;
	size_t		linelen;

	linelen = 0;
	if (remainder)
		line = remainder;
	else
		line = "";
	buf = malloc(BUF_SIZE * sizeof(char));
	if (!buf || fd < 0)
	{
		free(buf);
		return (NULL);
	}
	if (!(ft_strchr(line, '\n')))
	{
		while (!(ft_strchr(buf, '\n')))
		{
			buflen = read(fd, buf, BUF_SIZE);
			if (buflen == 0)
			{
				free (buf);
				free (remainder);
				return (line);
			}
			if (buflen <= 0)
			{
				free (buf);
				free (remainder);
				return (NULL);
			}
			buf[buflen] = '\0';
			line = ft_strjoin(line, buf);
		}
	}
	while (line[linelen] != '\n')
		linelen++;
	linelen++;
	buflen = (ft_strlen(line) - linelen);
	remainder = ft_substr(line, linelen, buflen + 1);
	line = ft_substr(line, 0, linelen + 1);
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
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return (0);
}