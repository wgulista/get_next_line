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

static int		ft_check_len(char *save)
{
	int				i;

	i = 0;
	if (save == NULL)
		return (-1);
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	return (i);
}

static int		check_line(t_gnl *gnl)
{
	if (ft_strchr(gnl->save, '\n'))
	{
		gnl->tmp = ft_strdup(ft_strchr(gnl->save, '\n') + 1);
		ft_strdel(&gnl->save);
		gnl->save = ft_strdup(gnl->tmp);
		ft_strdel(&gnl->tmp);
		return (1);
	}
	return (0);
}

static int		check_eof(t_gnl *gnl, char **line)
{
	if (ft_check_len(gnl->save) > 0)
	{
		*line = ft_strdup(gnl->save);
		ft_strdel(&gnl->save);
		return (1);
	}
	ft_strdel(line);
	ft_strdel(&gnl->save);
	return (0);
}

static void		ft_read_fd(t_gnl *gnl, const int fd)
{
	if (!gnl->save)
		gnl->save = ft_strnew(1);
	while (!(ft_strchr(gnl->save, '\n')) &&
		(gnl->rd = read(fd, gnl->buff, BUFF_SIZE)) > 0 && gnl->rd != 0)
	{
		gnl->buff[gnl->rd] = '\0';
		gnl->tmp = ft_strjoin(gnl->save, gnl->buff);
		ft_strdel(&gnl->save);
		gnl->save = ft_strdup(gnl->tmp);
		ft_strdel(&gnl->tmp);
		if (ft_strchr(gnl->save, '\n'))
			break ;
	}
	ft_strdel(&gnl->tmp);
	ft_strdel(&gnl->buff);
}

int				get_next_line(int const fd, char **line)
{
	static t_gnl	gnl;

	if (fd < 0 || !(line) ||
		!(gnl.buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (-1);
	ft_read_fd(&gnl, fd);
	if (gnl.rd == -1 || gnl.save == NULL)
	{
		ft_strdel(&gnl.save);
		return (-1);
	}
	*line = ft_strsub(gnl.save, 0, ft_check_len(gnl.save));
	if (check_line(&gnl) == 1)
		return (1);
	if (gnl.rd == 0 && ft_strchr(gnl.save, '\n') == NULL)
		return (check_eof(&gnl, line));
	return (0);
}
