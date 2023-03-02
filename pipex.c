/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:14:02 by rreis-de          #+#    #+#             */
/*   Updated: 2023/03/02 15:04:18 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *str_trim(char *src, int c)
{
	char    *dest;
    int     i;
    int     j;

    j = 0;
    while (src[j] != c)
        j++;
    j++;
    i = ft_strlen(src) - j;
    dest = (char *)malloc(sizeof(char) * i);
    i = 0;
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

void    free_arr(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
}

int get_path(int ac, char **av, char **env)
{
    int     outfd;
    int     i;
    char    *path;
    char    **paths;
    char    *gpath;
    char    *full_cmd;
    char    **args;
    char    *cmd;
    int     nargs;
    int     npths;

    path = str_trim(env[24], '=');
    paths = ft_split(path, ':');
    full_cmd = av[2];
    args = ft_split(full_cmd, ' ');
    cmd = args[0];
    nargs = string_counter(full_cmd, ' ');
    npths = string_counter(path, ':');
    ac = 0;

    outfd = open("outfile", O_CREAT | O_TRUNC | O_RDWR, 0644);
    //printf("%s\n", path);
    i = 0;
    while (i < npths)
    {
        paths[i] = path_join(paths[i], cmd);
        if (access(paths[i], F_OK) == 0)
        {
            gpath = paths[i];
            //printf("gpath: %s\n", gpath);
            break ;
        }
        //printf("%s\n", paths[i]);
        i++;
    }
    //printf("%s\n", full_cmd);
    //printf("%s\n", cmd);
    
    int fd[2];
    if (pipe(fd) == -1)
        return (1);
    int pid1 = fork();
    if (pid1 < 0)
        return (2);
    
    //printf("ola\n");
    //printf("gpath: %s\n", gpath);
    if (pid1 == 0)
    {
        //child process 1 (first command)
        //printf("gpath: %s\n", gpath);
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        //printf("start of execve call 1\n");
        if (execve(gpath, args, env) == -1)
            perror("could not execute execve 1\n");
        printf("something went wrong 1\n");
    }

    int pid2 = fork();
    if (pid2 < 0)
        return (3);
    
    char *args2[] = {"grep", "rtt"};
    if (pid2 == 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        dup2(outfd, STDOUT_FILENO);
        close(fd[0]);
        //printf("start of execve call 2\n");
        if (execve("/usr/bin/grep", args2, env) == -1)
            perror("could not execute execve 2\n");
        printf("something went wrong 2\n");
    }
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    
    /* printf("start of execve call\n");
    if (execve(gpath, args, env) == -1)
        perror("could not execute execve\n");
    printf("something went wrong\n"); */
    return (0);
}

int main(int ac, char **av, char **env)
{
    get_path(ac, av, env);
    
    return (0);
}