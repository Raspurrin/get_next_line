/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 21:01:25 by mialbert          #+#    #+#             */
/*   Updated: 2021/12/19 18:17:38 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include "get_next_line_utils.c"

#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*remainder = "";
	char		*line;
	char		*buf;
	ssize_t		buflen;
	size_t		linelen;

	linelen = 0;
	line = remainder;
	buflen = 1;
	buf = ft_calloc(BUF_SIZE + 1, sizeof(char));
	if (!buf || fd < 0)
	{
		free(buf);
		return (NULL);
	}
	if (!(ft_strchr(line, '\n')))
	{
		while (!(ft_strchr(buf, '\n') && buf[buflen]))
		{
			buflen = read(fd, buf, BUF_SIZE);
			if (!buf)
			{
				free (buf);
				if (remainder)
					free (remainder);
				return (NULL);
			}
			if (buflen == 0)
			{
				free (buf);
				if (line)
					return (line);
				return (NULL);
			}
			if (buflen < 0)
			{
				free (buf);
				return (NULL);
			}
			buf[buflen] = '\0';
			line = ft_strjoin(line, buf);
		}
	}
	if (buf == NULL)
	{
		free (buf);
		if (remainder)
			free (remainder);
		return (NULL);
	}
	while (line[linelen] != '\n')
		linelen++;
	if (line[linelen] == '\n')
	{
		linelen++;
		buflen = (ft_strlen(line) - linelen);
		remainder = ft_substr(line, linelen, buflen + 1);
		line = ft_substr(line, 0, linelen + 1);
	}
	return (line);
}

// int	main(void)
// {
// 	int		fd;

// 	fd = open("test.txt", 0);
// 	if (!fd)
// 		return (0);
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	close(fd);
// 	return (0);
// }