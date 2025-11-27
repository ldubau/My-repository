/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leondubau <leondubau@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:14:09 by leondubau         #+#    #+#             */
/*   Updated: 2025/11/26 16:54:32 by leondubau        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
# endif

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

char	*get_next_line(int fd);
char	*write_stock(char *stock, int	fd);
char	*write_line(const char *str);
char	*my_strchr(const char *s, int c);
char	*my_strjoin(const char *s1, const char *s2);
char	*my_strdup(const char *s1);
size_t	my_strlen(const char *s);

#endif

