/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaouid <laouid.ferdaous@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 10:43:56 by flaouid           #+#    #+#             */
/*   Updated: 2020/01/11 11:23:50 by flaouid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char				*ft_strchr(char *str, int c)
{
	unsigned int	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return ((char*)str + i);
	return (NULL);
}

char				*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	str = (char*)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	str[len] = '\0';
	while (len--)
	{
		str[i] = s[start + i];
		i++;
	}
	return (str);
}

char				*ft_strdup(const char *s1)
{
	int				i;
	char			*dest;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t				ft_strlen(const char *s)
{
	int				i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
