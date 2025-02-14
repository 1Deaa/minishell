/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:02:49 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/14 15:02:50 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*init_s_cmd(t_find_cmd_path *shell)
{
	shell->start = getenv("PATH");
	if (!shell->start)
		return (NULL);
	shell->end = ft_strchr(shell->start, ':');
	shell->path = "";
	return (shell->path);
}

static char	*make_path(char *start, int len, char *cmd)
{
	char	*path;
	int		i;

	i = -1;
	path = (char *)malloc(len + 2 + ft_strlen(cmd) + 1);
	if (!path)
		return (NULL);
	while (++i < len)
	{
		path[i] = *(start + i);
	}
	path[i] = '/';
	path[i + 1] = '\0';
	ft_strcat(path, cmd);
	return (path);
}

char	*find_cmd_path(char *cmd)
{
	t_find_cmd_path	temp;

	if (init_s_cmd(&temp) == NULL)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (temp.end && temp.path)
	{
		temp.path = make_path(temp.start, temp.end - temp.start, cmd);
		if (access(temp.path, X_OK) == 0)
			return (temp.path);
		if (temp.path)
			free(temp.path);
		temp.start = temp.end + 1;
		temp.end = ft_strchr(temp.start, ':');
	}
	if (temp.path && *(temp.start))
	{
		temp.path = make_path(temp.start, ft_strlen(temp.start), cmd);
		if (access(temp.path, X_OK) == 0)
			return (temp.path);
		if (temp.path)
			free(temp.path);
	}
	return (NULL);
}
