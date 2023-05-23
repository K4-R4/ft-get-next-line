/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:05:52 by tkuramot          #+#    #+#             */
/*   Updated: 2023/05/23 22:05:31 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	if (fd < 0)
		return (NULL);
	return (read_fd(fd));
}

// returning empty str after eof
char	*read_fd(int fd)
{
	static char	*remaining_data;
	char		*buffer;
	char		*ret;
	ssize_t		bytes;
	ssize_t		newline_index;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	while (1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes] = '\0';
		remaining_data = ft_strjoin(remaining_data, buffer);
		newline_index = find_chr(remaining_data, '\n');
		if (newline_index != find_chr(remaining_data, '\0') || bytes == 0)
			break;
	}
	// split func
	ret = ft_substr(remaining_data, 0, newline_index + 1);
	// printf("%lu %lu\n", newline_index, find_chr(remaining_data, '\0'));
	remaining_data = ft_substr(remaining_data, newline_index + 1,
			find_chr(remaining_data, '\0'));
	return ret;
}

#include <fcntl.h>

int	main(void)
{
	int fd = open("sample.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
}