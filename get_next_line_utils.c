/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:05:49 by tkuramot          #+#    #+#             */
/*   Updated: 2023/05/22 22:30:11by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (*s++ != '\0')
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	dstsize;
	char	*ret;
	char	*tmp;

	dstsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret = (char *)malloc(sizeof(char) * dstsize);
	if (ret == NULL)
		return (NULL);
	tmp = ret;
	while (s1 != NULL && *s1 != '\0')
		*tmp++ = *s1++;
	while (s2 != NULL && *s2 != '\0')
		*tmp++ = *s2++;
	return (ret);
}

char	*ft_substr(char const *s, unsigned int start, ssize_t len)
{
	ssize_t	s_len;
	char	*ret;
	char	*tmp;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
		len = 0;
	if (s_len < len)
		len = s_len;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	tmp = ret;
	s += start;
	while (len-- > 0)
		*tmp++ = *s++;
	return (ret);
}

// Returns true when char c is found char *s, otherwise false
// Update index according to found char c's index
ssize_t	find_chr(char *s, int c, ssize_t siz)
{
	ssize_t index;

	index = 0;
	while (siz-- > 0 && *s++ != c)
		index++;
	return index;
}

char	*extract_line(char *line, ssize_t bytes)
{
	static char	*data;
	static ssize_t		data_len;
	char		*tmp;
	ssize_t		newline_index;

	tmp = data;
	data = ft_strjoin(data, line);
	data_len += bytes;
	free(tmp);
	newline_index = find_chr(data, '\n', data_len);
	if (newline_index < data_len)
	{
		tmp = line;
		line = ft_substr(data, 0, newline_index + 1);
		free(tmp);
		tmp = data;
		data = ft_substr(data, newline_index + 1, data_len - newline_index);
		data_len = data_len - newline_index - 1;
		free(tmp);
		return line;
	}
	if (newline_index == data_len && bytes == 0)
	{
		tmp = data;
		data = NULL;
		return tmp;
	}
	return (NULL);
}
