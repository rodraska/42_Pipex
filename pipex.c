/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:14:02 by rreis-de          #+#    #+#             */
/*   Updated: 2023/03/07 12:49:59 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_geral(int ac, char **av, char **env)
{
	int		outfd;
	int		infd;
	char	*path;
	char	**paths;

	path = str_trim(get_path(env), '=');
	paths = ft_split(path, ':');
	ac = 0;
	infd = open(av[1], O_RDONLY, 0444);
	outfd = open(av[4], O_CREAT | O_TRUNC | O_RDWR, 0644);
	ft_children(av, path, paths, env);
	free(path);
	ft_free(paths);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	ft_geral(ac, av, env);
	return (0);
}
