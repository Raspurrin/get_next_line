#include "get_next_line.h"
// #include "get_next_line_utils.c"

#include <stdio.h>

// make sure that I can free line in strjoin and before
// returning line if buflen < BUF_SIZE

char	*get_next_line(int fd)
{
	char		*line;
	static char	buf[BUF_SIZE + 1];
	ssize_t		buflen;
	size_t		linelen;

	linelen = 0;
	
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

int	main(void)
{
	int		fd[8];
	int		i;
	char	*line;

	i = 4;
	fd[0] = open("41_no_nl", 0);
	fd[1] = open("41_with_nl", 0);
	fd[2] = open("42_no_nl", 0);
	fd[3] = open("42_with_nl", 0);
	fd[4] = open("43_no_nl", 0);
	fd[5] = open("43_with_nl", 0);
	fd[6] = open("alternate_line_nl_no_nl", 0);
	fd[7] = open("alternate_line_nl_with_nl", 0);
	while (i < 5)
	{
		line = get_next_line(fd[i]);
		printf("%s", line);
		if (!line)
			i++;
	}
	return (0);
}
