/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leondubau <leondubau@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:41:43 by ldubau            #+#    #+#             */
/*   Updated: 2025/11/24 23:02:27 by leondubau        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
# endif

size_t	len_stock(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i ++;
	if (s[i] == '\n')
		i ++;
	return (i);
}
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i ++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i ++;
	}
	str[i] = '\0';
	return (str);
}

char	*my_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i ++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j ++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cc;

	i = 0;
	cc = (char) c;
	if(!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *) &s[i]);
		i ++;
	}
	if (s[i] == cc)
		return ((char *) &s[i]);
	return (NULL);
}

char	*write_line(char *str)
{
	int		size;
	char	*res;
	int		i;

	i = 0;
	size = len_stock(str);
	res = malloc(sizeof(char) * size + 1);
	while(i < size)
	{
		res[i] = str[i];
		i ++;
	}
	res[i] = '\0';
	return (res);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	char		*line;
	static char	*stock;
	char		*tmp;
	int			size_read;

	size_read = 1;
	if (!stock)
		stock = ft_strdup("");
	if (!stock)
		return (NULL);
	while (size_read > 0 && !ft_strchr(stock, '\n'))
	{
		size_read = read(fd, buf, BUFFER_SIZE);
		if (size_read < 0)
			break;
		buf[size_read] = 0;
		tmp = my_strjoin(stock, buf);
		free(stock);
		if (!tmp)
			return (NULL);
		stock = tmp;
	}
	line = write_line(stock);
	if (ft_strchr(stock, '\n'))
	{
		tmp = ft_strdup(ft_strchr(stock, '\n') + 1);
		free(stock);
		stock = tmp;
	}
	return (line);
}

int    main(void)
{
	char	*line;
	int		i;
	int		fd;
	fd = open("text.txt", O_RDONLY);
	i = 1;
	while (i < 14)
	{
		line = get_next_line(fd);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	if (i == -1)
	{
		printf("<ERROR>\n");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
