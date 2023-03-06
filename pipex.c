/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:14:02 by rreis-de          #+#    #+#             */
/*   Updated: 2023/03/06 12:03:23 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' \
		&& env[i][2] == 'T' && env[i][3] == 'H')
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	*get_gpath(char **paths, int npths, char *full_cmd)
{
	char	*gpath;
	char	*new_path;
	char	**args;
	char	*cmd;
	int		i;

	args = ft_split(full_cmd, ' ');
	cmd = args[0];
	i = 0;
	while (i < npths)
	{
		new_path = path_join(paths[i], cmd);
		if (access(new_path, F_OK) == 0)
		{
			gpath = new_path;
			ft_free(args);
			return (gpath);
		}
		free(new_path);
		i++;
	}
	ft_free(args);
	return (NULL);
}

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
