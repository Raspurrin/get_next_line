/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 21:14:26 by mialbert          #+#    #+#             */
/*   Updated: 2021/12/17 20:49:16 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"
// #include "get_next_line_utils.c"
//
// merge buff with remainder? O_o As a multi purpose variable. 
// More confusing to read tho
//
// getting the lines from read:
// 1. append the remainder to line, if remainder is empty initialise 
// line with NULL. Free remainder
// 2. if line contains \n go straight to splitting strings and skip reading
// 3. go through read with buffersize up until buf contains '\n', 
// storing it in buf
// 4. append it to line each time - ft_strjoin
// 5. Free src after using in strjoin
//																		
// splitting the remainder from the line: "for example \n\n this"       
// 6. get line length up until \n including \n							
// 7. get remainder length until end
// 8. use ft_substr to initialise both new strings						
// 9. free src after using in substr									
/**
 * text file: 
 * For example
 * 
 * 
 * 
 * this is something
 * you can do
 * 
 * BUF_SIZE = 5
 * ------------------------
 * function call 1:
 * get_next_line:
 * 		line: "for example \n\n\n"
 * 		buf:
 * ft_trim:
 * 		line: "for example \n"
 * 		buf: "\n\n"
 * 
 * function call 2:
 * get_next_line:
 * before ft_strjoin:
 * 		line: 
 * 		buf: "\n\n" - checking if buf contains new line and skipping
 * after:
 * 		line: "\n\n" - but this needs to be appended before that o-o Or after?
 * 		buf:
 * ft_trim:
 * 		line: "\n"
 * 		buf: "\n"
 * 
 * function call 3:
 * get_next_line:
 * before ft_strjoin:
 * 		line: 
 * 		buf: "\n"
 * after:
 * 		line: "\n"
 * 		buf:
 * ft_trim:
 * 		line: "\n"
 * 		buf: ""
 * 
 * function call 5:
 * get_next_line:
 * 		line: "this is something\n you"
 * 		buf:
 * ft_trim:
 * 		line: "this is something\n"
 * 		buf: "you"
 * 
 * function call 6:
 * get_next_line:
 * before ft_strjoin:
 * 		line: 
 * 		buf: "you"
 * after:
 * 		line: "you can do\n"
 * 		buf:
 * ft_trim:
 * 		line: "you can do\n"
 * 		buf: ""
 */

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_free(char *buf)
{
	free(buf);
	return (NULL);
}

char	*ft_trim(char *line, char *buf)
{
	size_t	linelen;
	size_t	buflen;

	linelen = 0;
	while (line[linelen] != '\n')
		linelen++;
	linelen++;
	buflen = ft_strlen(line) - linelen;
	buf = ft_substr(line, linelen, buflen + 1);
	line = ft_substr(line, 0, linelen + 1);
	return (buf);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buf;
	int32_t		buflen;

	buf = malloc(BUF_SIZE * sizeof(char)); // does this get rid of the remainder tho?
	line = "";
	if (buf)
		ft_strjoin(line, buf);
	while (!(ft_strchr(buf, '\n')))
	{
		ft_free(buf);
		buflen = read(fd, buf, BUF_SIZE);
		if (buflen < 0 || !buf)
			return (ft_free(buf));
		buf[buflen] = '\0';
		ft_strjoin(line, buf); // RIP for some reason this only gets rid of value kekw
		ft_free(buf);
	}
	buf = ft_trim(line, buf);
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
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	return (0);
}
