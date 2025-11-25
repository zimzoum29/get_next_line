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

char    *ft_extract_line(char *str, int fd)
{
        char    *buff;
        int     i;
        
        buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
        if (!buff)
                return (NULL);
        while (!ft_strchr(str, '\n') && i != 0)
        {
                i = read(fd, buff, BUFFER_SIZE);
                buff[i] = '\0';
                ft_strjoin(str, buff);
        }
        return (str);
}

char    *get_next_line(int fd)
{
        char    *str;

        if (fd < 0 || BUFFER_SIZE < 1)
                return (NULL);
        str = ft_extract_line(str, fd);
        return (str);
}

#include <stdio.h>
#include <fcntl.h>
int main(void)
{
        int fd = open("test.txt", O_RDONLY);
        char *str;
        str = get_next_line(fd);
        printf("%s", str);
}