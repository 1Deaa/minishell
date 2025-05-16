/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:18:01 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/09 00:18:02 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	try_direct_path(char *command)
{
	if (ft_strchr(command, '/'))
		if (access(command, X_OK) == 0)
			return (true);
	return (false);
}

static char	*create_command_path(char *path, char *command)
{
	char	*ret;

	if (!ft_strcmp(command, ""))
		return (NULL);
	ret = ft_strjoin(ft_strdup(path), "/");
	ret = ft_strjoin(ret, command);
	if (!ret)
		return (NULL);
	return (ret);
}

static char	**create_paths(t_shell *shell)
{
	char	*path_var;
	char	**ret;

	path_var = get_envp(shell->envp, "PATH");
	if (!path_var)
		return (NULL);
	ret = ft_split(path_var, ':');
	return (ret);
}

char	*find_path(t_shell *shell, char *command)
{
	char	**paths;
	char	*ret;
	int		i;

	i = -1;
	if (try_direct_path(command))
		return (ft_strdup(command));
	paths = create_paths(shell);
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		ret = create_command_path(paths[i], command);
		if (!ret)
			continue ;
		if (access(ret, X_OK) == 0)
		{
			free_split(paths);
			return (ret);
		}
		free(ret);
	}
	free_split(paths);
	return (NULL);
}
