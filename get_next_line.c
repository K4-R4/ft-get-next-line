/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:05:52 by tkuramot          #+#    #+#             */
/*   Updated: 2023/05/26 17:25:08 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			flag;
	ssize_t		n;
	char		buffer[BUFFER_SIZE + 1];
	static char	*rest[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD)
		return (NULL);
	line = (char *)malloc(sizeof(char) * 1);
	if (!line)
		return (NULL);
	*line = '\0';
	flag = 0;
	if (rest[fd])
		flag = concat_line(&line, rest[fd], &rest[fd]);
	while (!flag)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (is_eof(&line, n) || n <= 0)
			break ;
		buffer[n] = '\0';
		flag = concat_line(&line, buffer, &rest[fd]);
	}
	handle_error(&line, n, flag);
	return (line);
}

// Returns 1 when strings are successfully concatinated,
// -1 when an error occurs, 0 when line has no nl
int	concat_line(char **line, char *buffer, char **rest)
{
	int		flag;
	char	*tmp;
	size_t	n;

	flag = 0;
	n = find_chr(buffer, '\n');
	tmp = ft_strnjoin(*line, buffer, ft_strlen(*line), n + 1);
	if (!tmp)
		return (-1);
	free(*line);
	*line = tmp;
	tmp = NULL;
	if (buffer[n] == '\n')
	{
		tmp = ft_strdup(buffer + n + 1);
		if (!tmp)
			return (-1);
		flag = 1;
	}
	free(*rest);
	*rest = tmp;
	return (flag);
}

int	is_eof(char **line, ssize_t n)
{
	if (!ft_strlen(*line) && !n)
	{
		free(*line);
		*line = NULL;
		return (1);
	}
	return (0);
}

void	handle_error(char **line, ssize_t n, int flag)
{
	if (n < 0 || flag == -1)
	{
		free(*line);
		*line = NULL;
	}
}

// #include <fcntl.h>

// int	main(void)
// {
// 	int		fd;
// 	int		n;
// 	char	*s;

// 	fd = open("sample1.txt", O_RDONLY);
// 	n = 20;
// 	for (int i = 0; i < n; i++)
// 	{
// 		printf("============%d\n", i);
// 		s = get_next_line(fd);
// 		printf("%s", s);
// 		free(s);
// 	}
// }

// __attribute__((destructor)) static void destructor()
// {
//     system("leaks -q a.out");
// }
