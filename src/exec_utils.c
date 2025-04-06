/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:37:48 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/01 22:37:49 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	direct_access(const char *command)
{
	if (ft_strchr(command, '/') == 0)
	{
		if (access(command, X_OK) == 0)
		{
			return (true);
		}
	}
	return (false);
}

static char	**get_paths(t_shell *shell)
{
	char	**paths;
	char	*path_env;

	path_env = get_envp(shell->envp, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	return (paths);
}

char	*find_command_path(t_shell *shell, const char *command)
{
	char	**paths;
	char	*exp;
	char	*ret;
	int		i;

	if (direct_access(command))
		return (ft_strdup(command));
	paths = get_paths(shell);
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		exp = ft_strjoin(paths[i], "/");
		exp = ft_strjoin(exp, (char *)command);
		if (access(exp, X_OK) == 0)
		{
			ret = ft_strdup(exp);
			free_envp(paths, i + 1);
			return (ret);
		}
		free(exp);
	}
	return (NULL);
}
