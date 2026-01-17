/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjose-hi <fjose-hi@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 20:09:20 by fjose-hi          #+#    #+#             */
/*   Updated: 2025/11/17 14:18:00 by fjose-hi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*fill_line_buffer(int fd, char *stash, char *buff)
{
	ssize_t	b_read;
	char	*tmp;

	b_read = 1;
	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	while (!ft_strchr(stash, '\n') && b_read > 0)
	{
		b_read = read(fd, buff, BUFFER_SIZE);
		if (b_read == -1)
			return (free(stash), NULL);
		buff[b_read] = '\0';
		tmp = ft_strjoin(stash, buff);
		free(stash);
		if (!tmp)
			return (NULL);
		stash = tmp;
	}
	return (stash);
}

static char	*extract_line(char *stash)
{
	size_t	i;

	if (!stash || !*stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	return (ft_substr(stash, 0, i));
}

static char	*set_line(char *stash)
{
	size_t	i;
	char	*new_stash;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	new_stash = ft_substr(stash, i + 1, ft_strlen(stash) - (i + 1));
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*stash[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	stash[fd] = fill_line_buffer(fd, stash[fd], buff);
	free(buff);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	stash[fd] = set_line(stash[fd]);
	return (line);
}
/*
#include <stdio.h>

int	main(void)
{
	int		fd1;
	int		fd2;
	char	*l1;
	char	*l2;

	fd1 = open("read_error.txt", O_RDONLY);
	fd2 = open("variable_nls.txt", O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
		return (perror("Erro ao abrir arquivo"), 1);
	while (1)
	{
		l1 = get_next_line(fd1);
		l2 = get_next_line(fd2);
		if (!l1 && !l2)
			break ;
		if (l1)
		{
			printf("Teste1: %s", l1);
			free(l1);
		}
		if (l2)
		{
			printf("Teste2: %s", l2);
			free(l2);
		}
	}
	close(fd1);
	close(fd2);
}
*/
/*
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;

	if (argc < 2)
	{
		printf("Uso: %s <arquivo>, <arquivo2>, ...\n", argv[0]);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd < 0)
		{
			perror(argv[i]);
			i++;
			continue ;
		}
		while ((line = get_next_line(fd)) != NULL)
		{
			printf("%s", line);
			free(line);
		}
		close(fd);
		i++;
	}
	return (0);
}
*/
