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

	len = 0;
	while (s != NULL && *s++ != '\0')
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
	*tmp = '\0';
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

ssize_t	find_chr(char *s, char c)
{
	ssize_t index;

	index = 0;
	while (s != NULL && *s != '\0' && *s++ != c)
		index++;
	return index;
}
