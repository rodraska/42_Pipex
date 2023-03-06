/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:10:32 by rreis-de          #+#    #+#             */
/*   Updated: 2023/03/06 11:55:03 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>

char	**ft_split(char const *s, char c);
char	*word(char const *str, int *ptr_i, char c);
int		string_counter(char const *str, char c);
int		ft_strlen(char *str);
void	ft_free(char **arr);

char	*str_trim(char *src, int c);
char	*path_join(char *s1, char *s2);
int		ft_child(char **av, int *fd, char *gpath, char **env);
int		ft_child2(char **av, int *fd, char *gpath, char **env);
int		ft_children(char **av, char *path, char **paths, char **env);
char	*get_path(char **env);
char	*get_gpath(char **paths, int npths, char *full_cmd);
int		ft_geral(int ac, char **av, char **env);

#endif
