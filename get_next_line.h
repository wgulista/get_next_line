/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgulista <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 12:25:30 by wgulista          #+#    #+#             */
/*   Updated: 2016/03/05 12:25:31 by wgulista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft/includes/libft.h"

# define BUFF_SIZE 1

typedef struct		s_gnl
{
	char			*save;
	char			*buff;
	char			*tmp;
	int				rd;
}					t_gnl;

int					get_next_line(const int fd, char **line);

#endif
