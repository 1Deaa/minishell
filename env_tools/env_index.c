/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_index.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:56:33 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/16 11:56:33 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_tools.h"

/*
return index of NAME inside envp, -1 if not found.
*/
int	env_index(char **envp, char *name)
{
	int		i;
	size_t	len;

	if (!envp || !name)
		return (-1);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}
