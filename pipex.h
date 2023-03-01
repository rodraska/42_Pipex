/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:10:32 by rreis-de          #+#    #+#             */
/*   Updated: 2023/03/01 15:16:21 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

char	**ft_split(char const *s, char c);
char	*word(char const *str, int *ptr_i, char c);
int     string_counter(char const *str, char c);
int     ft_strlen(char *str);

char    *str_trim(char *src);
char    *path_join(char *s1, char *s2);
int     get_path(int ac, char **av, char **env);


#endif
