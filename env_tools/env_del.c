/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:55:02 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/16 11:55:02 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_tools.h"

static void	env_fill(char **new_env, char **envp, int target_index)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (envp && envp[i])
	{
		if (i != target_index)
		{
			new_env[j++] = envp[i];
		}
		i++;
	}
	new_env[j] = NULL;
}

char	**env_del(char **envp, char *name)
{
	int		target_index;
	char	*target;
	char	**new_env;
	size_t	size;

	size = env_count(envp);
	target_index = env_index(envp, name);
	if (target_index == -1 || size == 0)
		return (envp);
	target = env_grab(envp, name);
	new_env = (char **)malloc(sizeof(char *) * size);
	if (!new_env)
	{
		write(2, "Memory allocation failed inside env_del\n", 41);
		return (envp);
	}
	env_fill(new_env, envp, target_index);
	free(target);
	free(envp);
	return (new_env);
}
