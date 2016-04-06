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

static char     *add_to_line(char *line, int cur, char *buff, int *start)
{
	char          *new_elem;
  	int           old_len;
 
  	old_len = (line) ? ft_strlen(line) : 0;
  	new_elem = ft_memalloc((old_len + cur + 1) * sizeof(*new_elem));
  	ft_strncpy(new_elem, line ? line : "", old_len);
  	ft_strncpy(new_elem + old_len, buff + *start, cur);
  	new_elem[old_len + cur] = 0;
  	if (line)
    	free(line);
  	*start += cur + 1;
  	return (new_elem);
}
 
int            get_next_line(const int fd, char **line)
{
  	static char   buff[BUFF_SIZE + 1];
 	static int    in_buf = 0;
 	static int    start;
  	int           cur;
 
  	*line = 0;
  	cur = 0;
  	while (1)
    {
      	if (start >= in_buf)
        {
          	start = 0;
          	if (!(in_buf = read(fd, buff, BUFF_SIZE)))
            	return (-1);
        	if (in_buf == -1)
          		return (-1);
        	cur = 0;
        }
      	if (buff[start + cur] == '\n')
      	{
      		*line = add_to_line(*line, cur, buff, &start);
      		return (1);
      	}
      	if (start + cur == in_buf - 1)
        	*line = add_to_line(*line, cur + 1, buff, &start);
      	cur++;
    }
    return (0);
}
