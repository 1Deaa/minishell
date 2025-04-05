/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:00:45 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/05 18:00:45 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_envp(char **envp)
{
	int	count;

	count = 0;
	while (envp && envp[count])
		count++;
	return (count);
}

void	free_envp(char **envp, int count)
{
	int	i;
	int	temp;
	
	if (!envp)
		return ;
	temp = count_envp(envp);
	if (count > temp)
		count = temp;
	i = 0;
	while (i < count)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

char	**dup_envp(char **envp)
{
	char	**env_copy;
	int		count;
	int		i;

	i = 0;
	count = count_envp(envp);
	env_copy = malloc(sizeof(char *) * (count + 1));
	if (!env_copy)
		return (NULL);
	while (i < count)
	{
		env_copy[i] = ft_strdup(envp[i]);
		if (!env_copy[i])
		{
			free_envp(env_copy, i);
			return (NULL);
		}
		i++;
	}
	env_copy[count] = NULL;
	return (env_copy);
}

char	*get_envp(char **envp, const char *name)
{
	int		i;
	size_t	len;

	if (!envp || !name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}
