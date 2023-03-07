/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:42:45 by rreis-de          #+#    #+#             */
/*   Updated: 2023/03/07 11:14:56 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* void    ft_exec(t_command cmd, char **env)
{
    dup2(cmd.fd_in, STDIN_FILENO);
    dup2(cmd.fd_out, STDOUT_FILENO);
    if (execve(gpath, ft_split(av[3], ' '), env) == -1)
			perror("could not execute execve\n");   
} */

int	ft_children(int ac, char **av, char **env)
{
    int i;
    char    *path;
    char    **paths;
    t_child *children;

    path = str_trim(get_path(env), '=');
    paths = ft_split(path, ':');
    i = 0;
    while (i < ac - 3)
    {
        child_add_back(&children, get_gpath(paths, string_counter(path, ':'), \
        av[i + 2]), ft_split(av[i + 2], ' '));
        i++;
    }
    child_print(children);
    return (0);   
}

int main(int ac, char **av, char **env)
{
    ft_children(ac, av, env);
    return (0);
}