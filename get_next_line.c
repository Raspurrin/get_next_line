/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:43:34 by mialbert          #+#    #+#             */
/*   Updated: 2021/12/21 20:56:37 by mialbert         ###   ########.fr       */
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
	size_t		remlen;
	size_t		linelen;

	linelen = 0;
	line = remainder;
	buf = ft_calloc(BUF_SIZE + 1, sizeof(char));
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
			// if (!buf)
			// {
			// 	free (buf);
			// 	if (remainder)
			// 		free (remainder);
			// 	return (NULL);
			// }
			if (buflen <= 0)
			{
				free (buf);
				return (NULL);
			}
			if (buflen < BUF_SIZE)
			{
				line = ft_strjoin(line, buf);
				// free (buf);
				return (line);
			}

			buf[buflen] = '\0';
			line = ft_strjoin(line, buf);
		}
	}
	// if (buf == NULL)
	// {
	// 	free (buf);
	// 	if (remainder)
	// 		free (remainder);
	// 	return (NULL);
	// }
	while (line[linelen] != '\n')
		linelen++;
	linelen++;
	remlen = (ft_strlen(line) - linelen);
	// if (buflen != 0)
	remainder = ft_substr(line, linelen, remlen + 1);
	line = ft_substr(line, 0, linelen + 1);
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
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	close(fd);
// 	return (0);
// }