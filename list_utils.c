/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:55:12 by rreis-de          #+#    #+#             */
/*   Updated: 2023/03/07 11:17:35 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_child   *child_last(t_child *children)
{
    t_child *last;
    
    last = children;
    while (children != NULL)
    {
        last = children;
        children = children->next;
    }
    return (children);
}

void    child_add_back(t_child **children, char *gpath, char **args)
{
    t_child *new;
    t_child *last;

    new = child_new(gpath, args);
    if (*children)
    {
        last = child_last(*children);
        (*children)->next = new;
    }
    else
        *children = new;
}

t_child	*child_new(char *gpath, char **args)
{
	t_child	*child;

	child = (t_child *)malloc(sizeof(*child));
	if (!child)
		return (NULL);
	child->gpath = gpath;
	child->args = args;
	child->next = NULL;
	return (child);
}

void    child_print(t_child *children)
{
    int i;

    while (children)
    {
        i = 0;
        printf("gpath: %s\n", children->gpath);
        printf("args: ");
        while (children->args[i])
        {
            printf("%s ", children->args[i]);
            i++;
        }
        printf("\n");
        children = children->next;
    }
}