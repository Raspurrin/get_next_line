/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:42:31 by mialbert          #+#    #+#             */
/*   Updated: 2021/12/27 20:35:06 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include "get_next_line_utils.c"

#include <stdio.h>

int	gnl_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/**
 * @brief Trims everything after a newline char into the remainder 
 * and the rest into line.
 * example: line = "Something is here\\nAnd"
 * Result:
 * line = "Something is here\\n"
 * remainder = "And"
 * @param line ex: "Something is here\\nAnd"
 * @param remainder This will store the remainder of the line.
 * @return The line up till and including the newline char.
 */
static char	*ft_trim(char *line, char *remainder)
{
	ssize_t		buflen;
	size_t		linelen;

	linelen = 0;
	while (line[linelen] != '\n' && line[linelen])
		linelen++;
	if (line[linelen] == '\n')
		linelen++;
	buflen = (gnl_strlen(line) - linelen);
	if (buflen != 0)
		gnl_strlcpy(remainder, line + linelen, buflen + 1);
	else
		remainder[0] = '\0';
	line = gnl_substr(line, 0, linelen + 1);
	return (line);
}

/**
 * @brief Reads the full buffersize until finding a newline char
 * and appends this to line each time.
 * @param line Will hold all characters being read in this function.
 * @param buf Holds buffersize amount of chars every single read.
 * @param fd The file descriptor being read from.
 * @return A line including a newline character and possibly characters
 * afterwards or NULL if nothing has been read.
 */
static char	*read_line(char	*line, char *buf, int fd)
{
	ssize_t		buflen;

	while (!(gnl_strchr(buf, '\n')))
	{
		buflen = read(fd, buf, BUF_SIZE);
		buf[buflen] = '\0';
		if (buflen <= 0 && !line[0])
		{
			free (line);
			return (NULL);
		}
		line = gnl_strjoin(line, buf);
		if (buflen < BUF_SIZE && !(gnl_strchr(buf, '\n')))
			return (line);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	buf[BUF_SIZE + 1];

	line = malloc(1 * sizeof(char));
	line[0] = '\0';
	if (!line)
		return (NULL);
	if (buf[0] != '\0')
		line = gnl_strjoin(line, buf);
	line = read_line(line, buf, fd);
	if (!line)
		return (NULL);
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
