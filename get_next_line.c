/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:05:52 by tkuramot          #+#    #+#             */
/*   Updated: 2023/05/24 14:11:16 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	if (fd < 0)
		return (NULL);
	return (read_fd(fd));
}

// free static remains initialized with null ??
char	*read_fd(int fd)
{
	static char	*remains;
	char		*buffer;
	char		*tmp;
	ssize_t		bytes;
	ssize_t		newline_idx;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	while (1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes] = '\0';
		tmp = remains;
		remains = ft_strjoin(remains, buffer);
		if (remains == NULL)
			return (NULL);
		if (tmp != NULL)
			free(tmp);
		newline_idx = find_chr(remains, '\n');
		if (newline_idx != find_chr(remains, '\0') || bytes == 0)
			break ;
	}
	free(buffer);
	return (split_remains_with_first_newline(&remains, newline_idx));
}

// Pass in whole string as remains,
// splitting it with first occurrence of newline and
// returns first part and update remains
char	*split_remains_with_first_newline(char **remains, ssize_t newline_idx)
{
	char	*ret;
	char	*tmp;

	if (newline_idx == 0 && find_chr(*remains, '\0') == 0)
	{
		free(*remains);
		*remains = NULL;
		return (NULL);
	}
	ret = ft_substr(*remains, 0, newline_idx + 1);
	if (ret == NULL)
		return (NULL);
	tmp = *remains;
	*remains = ft_substr(*remains, newline_idx + 1, find_chr(*remains, '\0'));
	if (*remains == NULL)
		return (NULL);
	free(tmp);
	return (ret);
}

#include <fcntl.h>

int	main(void)
{
	int fd = open("sample.txt", O_RDONLY);
	int n = 10;
	for (int i = 0; i < n; i++)
	{
		char *s = get_next_line(fd);
		printf("%s", s);
		free(s);
	}
}

// __attribute__((destructor)) static void destructor()
// {
//     system("leaks -q a.out");
// }
