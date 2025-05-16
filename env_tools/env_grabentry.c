/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_grabentry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:47:12 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/16 11:47:12 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_tools.h"

/*
returns a pointer to NAME inside ENVP, null if not found
*/
char	*env_grabentry(char **envp, const char *name)
{
	int		i;
	size_t	len;

	if (!envp || !name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}
