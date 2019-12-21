/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugusti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 19:26:00 by aaugusti          #+#    #+#             */
/*   Updated: 2019/12/21 12:15:01 by aaugusti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

/*
**	A wrapper around free. Just to be able to return a value and free in the
**	same line.
**
**	@param {void *} b - The block of memory to free
**	@param {int} to_return
**
**	@returns to_return without any changes
*/

int	gnl_free(void *b, int to_return)
{
	free(b);
	return (to_return);
}

/*
**	Read a single line from a filedescriptor. The line to be read is stored in
**	the string pointer 'line'.
**
**	@param {int} fd - the filedescriptor to read from.
**	@param {char **} line - a pointer to a string where the line will be stored
**
**	@returns {int} - is 1 if a line is read, 0 if EOF is reached and -1 when an
**		error is encuontered.
*/

int	get_next_line(int fd, char **line)
{
	static char	buf[20000][BUFFER_SIZE + 1];
	ssize_t		readret;
	char		*res;
	bool		force_ret;

	readret = 0;
	force_ret = false;
	res = gnl_strdup(buf[fd], &force_ret);
	while (true)
	{
		if (!force_ret)
			if (gnl_strlcat(&res, buf[fd]))
				return (-1);
		*line = res;
		if (gnl_hasnewline(buf[fd]) || force_ret)
			return (gnl_shiftbuf(buf[fd], 1));
		readret = read(fd, buf[fd], BUFFER_SIZE);
		if (readret < 0)
			return (-1);
		if (!readret)
			return (gnl_shiftbuf(buf[fd], 0));
		buf[fd][readret] = 0;
	}
	return (1);
}
