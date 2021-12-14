/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 21:14:26 by mialbert          #+#    #+#             */
/*   Updated: 2021/12/14 23:37:58 by mialbert         ###   ########.fr       */
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
	size_t		blen;
	size_t		i;

	i = 0;
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
	while (!(ft_strchr(buf, '\n')))
	{
		blen = read(fd, buf, BUF_SIZE);
		if (blen <= 0)
		{
			free (buf);
			return (NULL);
		}
		buf[blen] = '\0';
		line = ft_strjoin(line, buf);
	}
	while (line[i] != '\n')
		i++;
	blen = i + 1;
	while (line[blen])
		blen++;
	if ((blen - i - 1) > 0)
		remainder = ft_substr(line, i + 1, (i + blen - 1));
	line = ft_substr(line, 0, i + 1);
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
// 	return (0);
// }
