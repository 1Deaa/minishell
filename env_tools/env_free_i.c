/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:52:27 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/16 10:52:28 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_tools.h"

/*
frees ENVP of size N
*/
void	*env_free_i(char **envp, size_t n)
{
	size_t	i;

	
	if (!envp)
		return (NULL);
	i = env_count(envp);
	if (n > i)
		n = i;
	i = 0;
	while (envp && i < n)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	return (NULL);
}
