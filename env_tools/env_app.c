/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_app.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:54:33 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/16 10:54:34 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_tools.h"

static void	append_value(char **append, char **envp, char *value)
{
	size_t	i;

	i = 0;
	while (envp && envp[i])
	{
		append[i] = envp[i];
		i++;
	}
	append[i] = value;
	append[i + 1] = NULL;
}

/*
INFO: append VALUE to envp
MEMORY: heap allocation, envp must be heap allocated
RETURN: new pointer to list of already allocated values including VALUE
*/
char	**env_app(char **envp, char *value)
{
	char	**append;
	size_t	argc;

	argc = env_count(envp);
	if (!value)
		return (envp);
	append = (char **)malloc(sizeof(char *) * (argc + 1 + 1));
	if (!append)
	{
		write(2, "Memory allocation failed inside env_app\n", 41);
		return (envp);
	}
	append_value(append, envp, value);
	free(envp);
	return (append);
}
