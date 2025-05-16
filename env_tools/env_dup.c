/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:50:09 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/16 10:50:11 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_tools.h"

/*
INFO: duplicate ENVP
MEMORY: heap allocation, envp must be freed by user
RETURN: pointer to a newly allocated copy of ENVP
*/
char	**env_dup(char **envp)
{
	char	**dupl;
	size_t	argc;
	size_t	i;

	argc = env_count(envp);
	if (argc == 0 || !envp)
		return (NULL);
	dupl = (char **)malloc(sizeof(char *) * (argc + 1));
	if (!dupl)
	{
		write(2, "Memory allocation failed inside env_dup\n", 41);
		return (NULL);
	}
	i = -1;
	while (envp[++i])
	{
		dupl[i] = ft_strdup(envp[i]);
		if (!dupl[i])
		{
			write(2, "Memory allocation failed inside env_dup\n", 41);
			return (env_free_i(dupl, i));
		}
	}
	dupl[i] = NULL;
	return (dupl);
}
