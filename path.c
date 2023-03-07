/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:38:14 by rreis-de          #+#    #+#             */
/*   Updated: 2023/03/07 10:38:42 by rreis-de         ###   ########.fr       */
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
