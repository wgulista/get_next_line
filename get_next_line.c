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
	static char		*save;
	char			buff[BUFF_SIZE + 1];
	int				rd;

	if (fd <= 0 || line == NULL || BUFF_SIZE <= 0)
		return (-1);
	*line = ft_strnew(BUFF_SIZE + 1);
	save = ft_strnew(BUFF_SIZE + 1);
	while ((save = ft_strchr(*line, '\n')) == NULL
		&& (rd = read(fd, buff, BUFF_SIZE)) > 0 && rd != 0)
	{
		buff[rd] = '\0';
		if (buff[rd] != '\n')
			ft_strncat(*line, buff, ft_strlen(buff));
	}
	if ((save = ft_strchr(*line, '\n')))
	{
		*save = '\0';
		return (1);
	}
	if (rd == 0)
		return (0);
	return (-1);
}
