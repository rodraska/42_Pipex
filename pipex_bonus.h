/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:06:58 by rreis-de          #+#    #+#             */
/*   Updated: 2023/03/07 11:14:15 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_child
{
    char    **args;
    char    *gpath;
    struct s_child *next;
}   t_child;

char	**ft_split(char const *s, char c);
char	*word(char const *str, int *ptr_i, char c);
int		string_counter(char const *str, char c);
int		ft_strlen(char *str);

char	*str_trim(char *src, int c);
char	*path_join(char *s1, char *s2);
void	ft_free(char **arr);

char	*get_path(char **env);
char	*get_gpath(char **paths, int npths, char *full_cmd);

int     ft_children(int ac, char **av, char **env);

t_child	*child_new(char *gpath, char **args);
void    child_add_back(t_child **children, char *gpath, char **args);
t_child   *child_last(t_child *children);
void    child_print(t_child *children);

#endif