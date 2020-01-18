/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaouid <laouid.ferdaous@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:45:24 by flaouid           #+#    #+#             */
/*   Updated: 2020/01/18 14:53:42 by flaouid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void				ft_bzero(void *s, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		((unsigned char*)s)[i] = 0;
		i++;
	}
}

void				*ft_calloc(size_t nbr, size_t size)
{
	void			*str;

	if (!(str = malloc(size * nbr)))
		return (0);
	ft_bzero(str, nbr * size);
	return (str);
}

char				*ft_refresh(char *prevbuffer, int i)
{
	char			*tmp;

	if (prevbuffer[i])
		tmp = ft_strdup(prevbuffer + i + 1);
	else
		tmp = NULL;
	free(prevbuffer);
	return (tmp);
}

int					ft_done(int ret, char **buffer, char **prevbuffer)
{
	if (ret >= 0 && (*buffer || *prevbuffer))
	{
		if (*buffer)
			free(*buffer);
		if (ret == 0 && *prevbuffer)
			free(*prevbuffer);
	}
	if (ret == -1)
	{
		if (!*buffer)
			free(*buffer);
		if (!*prevbuffer)
			free(*prevbuffer);
	}
	return (ret);
}

int					get_next_line(int fd, char **line)
{
	int				i;
	int				ret;
	char			*buffer;
	static char		*prevbuffer;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || (i = 0) ||
	!(buffer = (char *)ft_calloc(sizeof(char), (BUFFER_SIZE + 1))))
		return (ft_done(-1, &buffer, &prevbuffer));
	if (!prevbuffer)
		if (!(prevbuffer = (char *)ft_calloc(sizeof(char), 1)))
			return (ft_done(-1, &buffer, &prevbuffer));
	while (!ft_strchr(buffer, '\n') && (ret = read(fd, buffer, BUFFER_SIZE)))
	{
		if (ret == -1)
			return (ft_done(-1, &buffer, &prevbuffer));
		buffer[ret] = '\0';
		prevbuffer = ft_strjoin(prevbuffer, buffer);
	}
	while (prevbuffer[i] && prevbuffer[i] != '\n')
		i++;
	*line = ft_substr(prevbuffer, 0, i);
	prevbuffer = ft_refresh(prevbuffer, i);
	if (prevbuffer || ret)
		return (ft_done(1, &buffer, &prevbuffer));
	return (ft_done(0, &buffer, &prevbuffer));
}
