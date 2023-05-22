/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:05:52 by tkuramot          #+#    #+#             */
/*   Updated: 2023/05/23 00:34:53 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*ret;
	char	*buffer;
	ssize_t	bytes;

	if (fd < 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE);
	if (buffer == NULL)
		return (NULL);
	bytes = read(fd, buffer, BUFFER_SIZE);
	ret = extract_line(buffer, bytes);
	while (bytes > 0 && ret == NULL)
	{
		ret = extract_line(buffer, bytes);
		bytes = read(fd, buffer, BUFFER_SIZE);
	}
	return (ret);
}

#include <fcntl.h>

int	main(void)
{
	int fd = open("sample.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
}