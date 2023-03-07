/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:42:45 by rreis-de          #+#    #+#             */
/*   Updated: 2023/03/07 16:46:20 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int ft_exec(t_child *child, char **env)
{
    int pid;

    pid = fork();
    if (pid < 0)
        return (2);
    if (pid == 0)
    {
        close(child->fd[0]);
        dup2(child->in_fd, STDIN_FILENO);
        dup2(child->fd[1], STDOUT_FILENO);
        close(child->fd[1]);
        if (execve(child->gpath, child->args, env) == -1)
            perror("could not execute execve\n");
    }
    if (child->next)
        child->next->in_fd = dup(child->fd[0]);
    close(child->fd[0]);
    close(child->fd[1]);
    return (pid);
}

int execute_children(int ac, char **av, char **env, t_child *children)
{
    children->in_fd = open(av[1], O_RDONLY, 0444);
    while (children)
    {
        if (pipe(children->fd) == -1)
            return (2);
        if (children == child_last(children))
            children->fd[1] = open(av[ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
        ft_exec(children, env);
        children = children->next;
    }
    while (waitpid(-1, NULL, WNOHANG));
    return (0);
}

int make_children(int ac, char **av, char **env)
{
    int i;
    char *path;
    char **paths;
    t_child *children;

    children = NULL;
    path = str_trim(get_path(env), '=');
    paths = ft_split(path, ':');
    i = 2;
    while (i <= ac - 2)
    {
        child_add_back(&children, get_gpath(paths, string_counter(path, ':'), av[i]), ft_split(av[i], ' '));
        i++;
    }
    execute_children(ac, av, env, children);
    free(path);
    ft_free(paths);
    ft_free_children(&children);
    return (0);
}

int main(int ac, char **av, char **env)
{
    make_children(ac, av, env);
    return (0);
}