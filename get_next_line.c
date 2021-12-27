/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:42:31 by mialbert          #+#    #+#             */
/*   Updated: 2021/12/27 15:57:16 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include "get_next_line_utils.c"

#include <stdio.h>

static char	*ft_trim(char *line, char *remainder)
{
	ssize_t		buflen;
	size_t		linelen;

	linelen = 0;
	while (line[linelen] != '\n')
		linelen++;
	linelen++;
	buflen = (ft_strlen(line) - linelen);
	if (buflen != 0)
		ft_strlcpy(remainder, line + linelen, buflen + 1);
	else
		remainder[0] = '\0';
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
		buf[0] = '\0';
		buflen = read(fd, buf, BUF_SIZE);
		buf[buflen] = '\0';
		if (buflen <= 0 && !line[0])
		{
			free (line);
			return (NULL);
		}
		line = ft_strjoin(line, buf);
		if (buflen < BUF_SIZE && !(ft_strchr(buf, '\n')))
		{
			buf[0] = '\0';
			return (line);
		}
	}
	line = ft_trim(line, buf);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("41_no_nl", 0);
// 	if (!fd)
// 		return (0);
// 	while (1 == 1)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		if (!line)
// 			break ;
// 	}
// 	close(fd);
// 	return (0);
// }
