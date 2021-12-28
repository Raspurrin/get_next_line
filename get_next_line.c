/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:42:31 by mialbert          #+#    #+#             */
/*   Updated: 2021/12/28 14:41:49 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_utils.c"

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
 * @brief Reads BUF_SIZE amount of chars every loop until finding a '\\n'
 * and appends this from buf to line each time.
 * @param line Will hold all characters being read in this function.
 * @param buf Temporary storage for every read.
 * @return A line (including a '\\n'), the last line of the file 
 * or NULL if nothing was read.
 */
static char	*read_line(char *line, char *buf, int fd)
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

/**
 * @brief Get the next line every time the function has been called.
 * line - will hold the line to be returned (including '\\n' if available)
 * buf - temporary storage for BUF_SIZE amount of chars 
 * remainder - Holds the remainder of the line after '\\n' 
 * (same variable as buf but renamed in ft_trim)
 */
char	*get_next_line(int fd)
{
	char		*line;
	static char	buf[BUF_SIZE + 1];

	line = malloc(1 * sizeof(char));
	if (!line)
		return (NULL);
	line[0] = '\0';
	if (buf[0] != '\0')
		line = gnl_strjoin(line, buf);
	line = read_line(line, buf, fd);
	if (!line)
		return (NULL);
	line = ft_trim(line, buf);
	return (line);
}
