/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tigondra <tigondra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:58:33 by tigondra          #+#    #+#             */
/*   Updated: 2025/11/25 15:15:51 by tigondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Lit dans fd et remplit/étend stash jusqu'à trouver '\n' ou EOF */
static char	*ft_read(int fd, char *str)
{
	char	*buf;
	ssize_t	bytes;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(str, '\n') && bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buf);
			free(str);
			return (NULL);
		}
		buf[bytes] = '\0';
		if (bytes == 0)
			break ;
		str = ft_strjoin_gnl(str, buf);
		if (!str)
		{
			free(buf);
			return (NULL);
		}
	}
	free(buf);
	if (!str || str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	return (str);
}

/* Extrait UNE ligne (avec '\n' si présent) à partir de stash */
static char	*gnl_extract_line(const char *str)
{
	size_t	i;
	char	*line;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

/* Nettoie stash: enlève la ligne déjà renvoyée, garde le reste */
static char	*gnl_clean_stash(char *str)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*new_str;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	i++; /* passer le '\n' */
	len = ft_strlen(str + i);
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	j = 0;
	while (str[i + j])
	{
		new_str[j] = str[i + j];
		j++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_read(fd, str);
	if (!str)
		return (NULL);
	line = gnl_extract_line(str);
	if (!line)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	str = gnl_clean_stash(str);
	return (line);
}
