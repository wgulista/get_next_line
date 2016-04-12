/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgulista <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 12:25:22 by wgulista          #+#    #+#             */
/*   Updated: 2016/03/21 12:25:23 by wgulista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					get_next_line(int fd, char **line)
{
	static char		*rest;
	char			buff[BUFF_SIZE + 1];
	int				rd;

	if (fd <= 0 || line == NULL || BUFF_SIZE < 1)
		return (-1);
	rest = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));
	*line = (char*)malloc(sizeof(char) * (ft_strlen(rest) + BUFF_SIZE + 1));
	while ((rd = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[rd] = '\0';
		ft_strncat(*line, buff, ft_strlen(buff));
	}
	if (rd == 0 && (rest = ft_strchr(*line, '\n')))
	{
		*rest = '\0';
		return (1);
	}
	if (rd == -1)
		return (-1);
	return (0);
}
