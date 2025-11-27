/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leondubau <leondubau@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:41:43 by ldubau            #+#    #+#             */
/*   Updated: 2025/11/26 16:54:14 by leondubau        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*my_strchr(const char *s, int c)
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

char	*write_line(const char *str)
{
	int		size;
	char	*res;
	int		i;

	i = 0;
	size = 0;
	while (str[size] != '\0' && str[size] != '\n')
		size ++;
	if (str[size] == '\n')
		size ++;
	res = malloc(sizeof(char) * size + 1);
	while(i < size)
	{
		res[i] = str[i];
		i ++;
	}
	res[i] = '\0';
	return (res);
}

char	*write_stock(char *stock, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	int		size_read;
	char	*tmp;

	size_read = 1;
	while (size_read > 0 && !my_strchr(stock, '\n'))
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
	return (stock);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stock;
	char		*tmp;

	if (!stock)
		stock = my_strdup("");
	if (!stock)
		return (NULL);
	stock = write_stock(stock, fd);
	line = write_line(stock);
	if (my_strchr(stock, '\n'))
	{
		tmp = my_strdup(my_strchr(stock, '\n') + 1);
		free(stock);
		stock = tmp;
	}
	return (line);
}

#include <stdio.h>

int	main(void)
{
	char	*line;
	int		i;
	int		fd;
	fd = open("text.txt", O_RDONLY);
	i = 1;
	while (i <= 13)
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
