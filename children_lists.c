/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_lists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:42:45 by rreis-de          #+#    #+#             */
/*   Updated: 2023/03/06 15:22:49 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    ft_exec(t_command cmd, char **env)
{
    dup2(cmd.fd_in, STDIN_FILENO);
    dup2(cmd.fd_out, STDOUT_FILENO);
    if (execve(gpath, ft_split(av[3], ' '), env) == -1)
			perror("could not execute execve\n");
    
    
}

int	ft_children(char **av, char *path, char **paths, char **env)
{
	int		fd[2];
    t_command child1;
    t_command child2;
    
    child1.next = child2;
    child2.next = NULL;
    child1.args = ft_split(av[2], ' ');
    child1.args = ft_split(av[3], ' ');
    child1.gpath = get_gpath(paths, string_counter(path, ':'), av[2]);
    child2.gpath = get_gpath(paths, string_counter(path, ':'), av[3]);
    child1.fd_in = open(av[1], O_RDONLY, 0444);
    child1.fd_out = fd[1];
    child2.fd_in = fd[0];
    child2.fd_out = open(av[4], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (pipe(fd) == -1)
		return (5);
	ft_child1(av, fd, env);
	ft_child2(av, fd, env);
	close(fd[0]);
	close(fd[1]);
	while (waitpid(-1, NULL, WNOHANG))
	{
	}
	return (0);
}