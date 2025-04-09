/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 22:54:39 by mdodevsk          #+#    #+#             */
/*   Updated: 2024/12/09 23:17:57 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*share_and_extract(char **storage)
{
	int		i;
	char	*line;
	char	*rest;

	i = 0;
	if (!*storage || !**storage)
		return (NULL);
	while ((*storage)[i] != '\n' && (*storage)[i])
		i++;
	if ((*storage)[i] == '\n')
		line = ft_substr(*storage, 0, i + 1);
	else
		line = ft_substr(*storage, 0, i);
	if (!line)
		return (free(*storage), *storage = NULL, NULL);
	if ((*storage)[i] == '\n')
		rest = ft_strdup(*storage + (i + 1));
	else
		rest = ft_strdup("");
	if (!rest)
		return (free(line), free(*storage), *storage = NULL, NULL);
	free(*storage);
	*storage = rest;
	return (line);
}

char	*read_and_stock(int fd, char *storage)
{
	char	*buffer;
	int		nb_read;
	char	*temp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	nb_read = 1;
	if (!storage)
		storage = ft_strdup("");
	while (!ft_strchr(storage, '\n') && nb_read > 0)
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read == -1)
			return (free(storage), free(buffer), storage = NULL, NULL);
		buffer[nb_read] = '\0';
		temp = ft_strjoin(storage, buffer);
		if (!temp)
			return (free(storage), free(buffer), NULL);
		free(storage);
		storage = temp;
	}
	free(buffer);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[FD_MAX];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	storage[fd] = read_and_stock(fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	if (!*storage[fd])
		return (free(storage[fd]), storage[fd] = NULL, NULL);
	line = share_and_extract(&storage[fd]);
	return (line);
}

/*
int	main(int ac, char **av)
{
	char *str;
	int fd = open(av[1], O_RDONLY);
	//get_next_line(fd);
	//printf("%s\n", get_next_line(fd));
	str = get_next_line(fd);
	free(str);
	close (fd);
	return (0);
}*/