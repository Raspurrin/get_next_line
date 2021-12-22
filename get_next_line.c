#include "get_next_line.h"
// #include "get_next_line_utils.c"

// merge remainder and buf to avoid allocation of memory for buf
// memset buf while reading
// freeing in strjoin and such

#include <stdio.h>

char	*get_next_line(int fd)
{
	char		*line;
	static char	buf[BUF_SIZE + 1];
	ssize_t		buflen;
	size_t		linelen;

	linelen = 0;
	line = "";
	if (buf[0] != '\0')
		line = ft_strjoin(line, buf);
	while (!(ft_strchr(buf, '\n')))
	{
		ft_memset(buf, '\0', BUF_SIZE);
		buflen = read(fd, buf, BUF_SIZE);
		if (buflen <= 0 && ft_strlen(line) == 0)
			return (NULL);
		if (buflen < BUF_SIZE && !(ft_strchr(buf, '\n'))) // case of multiple new lines?
		{
			line = ft_strjoin(line, buf);
			ft_memset(buf, '\0', BUF_SIZE);
			return (line);
		}
		buf[buflen] = '\0';
		line = ft_strjoin(line, buf);
	}
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

// int	main(void)
// {
// 	int		fd;

// 	fd = open("test.txt", 0);
// 	if (!fd)
// 		return (0);
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	close(fd);
// 	return (0);
// }
