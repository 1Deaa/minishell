/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:49:44 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/16 17:49:44 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_tools.h"

void	env_update(char **envp, char *name, char *value)
{
	int		index;
	char	*new;

	index = env_index(envp, name);
	if (index == -1)
		return ;
	new = env_newentry(name, value);
	if (!new)
		return ;
	free(envp[index]);
	envp[index] = new;
}
