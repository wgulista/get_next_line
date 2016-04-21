/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgulista <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 12:25:22 by wgulista          #+#    #+#             */
/*   Updated: 2016/03/05 12:25:24 by wgulista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		line_len(char *save)
{
	int				i;

	i = 0;
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	return (i);
}

static int		check_line_and_eof(char **save, char *tmp)
{
	if (ft_strchr(*save, '\n'))
	{
		tmp = *save;
		*save = ft_strdup(ft_strchr(*save, '\n') + 1);
		ft_strdel(&tmp);
		return (1);
	}
	if (line_len(*save) > 0)
	{
		*save += line_len(*save);
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char		*save[256];
	char			*buff;
	char			*tmp;
	int				rd;

	if (fd < 0 || fd > 256 || line == NULL || BUFF_SIZE < 0 ||
		!(buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (-1);
	if (!save[fd])
		save[fd] = ft_strdup("");
	while (!(ft_strchr(save[fd], '\n')) &&
		(rd = read(fd, buff, BUFF_SIZE)) > 0 && rd != 0)
	{
		buff[rd] = '\0';
		tmp = save[fd];
		save[fd] = ft_strjoin(save[fd], buff);
		ft_strdel(&tmp);
	}
	ft_strdel(&buff);
	if (rd == -1 || save[fd] == NULL)
		return (-1);
	*line = ft_strsub(save[fd], 0, line_len(save[fd]));
	if (check_line_and_eof(&save[fd], tmp) == 1)
		return (1);
	return (rd ? 1 : 0);
}
