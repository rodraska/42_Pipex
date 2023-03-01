/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:14:02 by rreis-de          #+#    #+#             */
/*   Updated: 2023/03/01 15:17:01 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *str_trim(char *src)
{
	char    *dest;
    int     i;
    int     j;

    i = ft_strlen(src) - 5;
    dest = (char *)malloc(sizeof(char) * i);
    i = 0;
    j = 5;
    while (src[i])
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
	return (dest);
}

char    *path_join(char *s1, char *s2)
{
    int i;
    int k;
    int len1;
    int len2;
    char    *new;

    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    new = (char *)malloc(len1 + len2 + 2);
    if (!new)
        return (NULL);
    i = -1;
    k = -1;
    while (++i < len1)
        new[i] = s1[i];
    new[i++]= '/';
    while (++k < len2)
        new[i++] = s2[k];
    new[i] = 0;
    return (new);    
}

int get_path(int ac, char **av, char **env)
{
    int     i;
    char    *path;
    char    **paths;
    char    *full_cmd;
    char    *cmd;
    int     nargs;
    int     npths;

    path = str_trim(env[24]);
    paths = ft_split(path, ':');
    full_cmd = av[2];
    cmd = ft_split(full_cmd, ' ')[0];
    nargs = string_counter(full_cmd, ' ');
    npths = string_counter(path, ':');

    printf("%s\n", path);
    i = 0;
    while (i < npths)
    {
        //printf("%s\n", paths[i]);
        printf("%s\n", path_join(paths[i], cmd));
        i++;
    }
    printf("%s\n", full_cmd);
    printf("%s\n", cmd);
    i = 1;
    while (i < nargs)
    {
        printf("%s\n", ft_split(full_cmd, ' ')[i]);
        i++;
    }
    return (0);
}

int main(int ac, char **av, char **env)
{
    get_path(ac, av, env);
    return (0);
}