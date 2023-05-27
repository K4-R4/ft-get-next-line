/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuramot <tkuramot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:05:55 by tkuramot          #+#    #+#             */
/*   Updated: 2023/05/27 18:27:08 by tkuramot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

# if !BUFFER_SIZE || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX - 1
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

char	*get_next_line(int fd);
char	*read_new_line(int fd, char *line, char **rest);
int		concat_line(char **line, char *buffer, char **rest);
size_t	find_chr(char *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strnjoin(char const *s1, char const *s2, size_t n1, size_t n2);
char	*ft_strdup(const char *s1);

#endif
