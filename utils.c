/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:32:41 by rreis-de          #+#    #+#             */
/*   Updated: 2023/03/07 16:46:51 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*str_trim(char *src, int c)
{
	char	*dest;
	int		len;
	int		i;
	int		j;

	j = 0;
	len = 0;
	while (src[j] != c)
		j++;
	j++;
	len = ft_strlen(src) - j;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*path_join(char *s1, char *s2)
{
	int		i;
	int		k;
	int		len1;
	int		len2;
	char	*new;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = (char *)malloc(len1 + len2 + 2);
	if (!new)
		return (NULL);
	i = -1;
	k = -1;
	while (++i < len1)
		new[i] = s1[i];
	new[i++] = '/';
	while (++k < len2)
		new[i++] = s2[k];
	new[i] = 0;
	return (new);
}

void	ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return ;
}
