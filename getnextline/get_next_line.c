/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaouid <laouid.ferdaous@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 12:45:24 by flaouid           #+#    #+#             */
/*   Updated: 2019/12/04 16:40:09 by flaouid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		*ft_strcpy(char *dst, const char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char			*ft_strjoin(const char *s1, const char *s2)
{
	char		*dest;
	unsigned int	length;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	length = ft_strlen(s1);
	dest = (char*)malloc(length + ft_strlen(s2) + 1);
	if (dest == NULL)
		return (NULL);
	ft_strcpy(dest, s1);
	ft_strcpy(dest + length, s2);
	free((char *)s1);
	return (dest);
}

static char		*ft_refresh(char *prevbuffer, int i)
{
	char		*tmp;

	if (prevbuffer[i] == '\n')
		tmp = ft_strdup(prevbuffer + i + 1);
	else
		tmp = ft_strdup(prevbuffer + i);
	free(prevbuffer);
	return (tmp);
}

int			ft_done(int ret, char **buffer, char **prevbuffer)
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
		if (*prevbuffer)
			free(*prevbuffer);
	}
	return (ret);
}
int			get_next_line(int fd, char **line)
{
	int		i;
	int		ret;
	char		*buffer;
	static char	*prevbuffer = NULL;

	if (fd < 0 || line == 0 || BUFF_SIZE <= 0 || (i = 0) || 
	!(buffer = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (ft_done(-1, &buffer, &prevbuffer));
	if (!prevbuffer)
		if (!(prevbuffer = malloc(sizeof(char) * 1)))
			return (ft_done(-1, &buffer, &prevbuffer));
	while (((!ft_strchr(buffer, '\n')) && (ret = read(fd, buffer, BUFF_SIZE))))
	{
		buffer[ret] = '\0';
		if (ret == -1)
			return (ft_done(-1, &buffer, &prevbuffer));
		prevbuffer = ft_strjoin(prevbuffer, buffer);
	}
	while (prevbuffer[i] && prevbuffer[i] != '\n')
		i++;
	*line = ft_substr(prevbuffer, 0, i);
	prevbuffer = ft_refresh(prevbuffer, i);
	free(buffer);
	return (prevbuffer[0] || ret ? 1 : 0);	
}