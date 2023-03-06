/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:30:19 by rreis-de          #+#    #+#             */
/*   Updated: 2023/03/06 14:36:15 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_child1(char **av, int *fd, char *gpath, char **env)
{
	int	pid;
	int	infd;

	infd = open(av[1], O_RDONLY, 0444);
	pid = fork();
	if (pid < 0)
		return (2);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(infd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		if (execve(gpath, ft_split(av[2], ' '), env) == -1)
			perror("could not execute execve\n");
	}
	return (pid);
}

int	ft_child2(char **av, int *fd, char *gpath, char **env)
{
	int	pid;
	int	outfd;

	outfd = open(av[4], O_CREAT | O_TRUNC | O_RDWR, 0644);
	pid = fork();
	if (pid < 0)
		return (3);
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		dup2(outfd, STDOUT_FILENO);
		if (execve(gpath, ft_split(av[3], ' '), env) == -1)
			perror("could not execute execve\n");
	}
	return (pid);
}

int	ft_children(char **av, char *path, char **paths, char **env)
{
	int		fd[2];
	char	*gpath1;
	char	*gpath2;

	gpath1 = get_gpath(paths, string_counter(path, ':'), av[2]);
	gpath2 = get_gpath(paths, string_counter(path, ':'), av[3]);
	if (pipe(fd) == -1)
		return (5);
	ft_child1(av, fd, gpath1, env);
	ft_child2(av, fd, gpath2, env);
	close(fd[0]);
	close(fd[1]);
	while (waitpid(-1, NULL, WNOHANG))
	{
	}
	free(gpath1);
	free(gpath2);
	return (0);
}
