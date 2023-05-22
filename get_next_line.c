/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:05:52 by tkuramot          #+#    #+#             */
/*   Updated: 2023/05/22 23:24:46 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*line;
	ssize_t	bytes;

	if (fd < 0)
		return (NULL);
	line = (char *)malloc(BUFFER_SIZE);
	if (line == NULL)
		return (NULL);
	bytes = read(fd, line, BUFFER_SIZE);
	while (bytes > 0)
	{
		extract_line(line, bytes);
		bytes = read(fd, line, BUFFER_SIZE);
	}
	return (NULL);
}

#include <fcntl.h>

int	main(void)
{
	int fd = open("sample.txt", O_RDONLY);
	printf("%s\n", get_next_line(fd));
}