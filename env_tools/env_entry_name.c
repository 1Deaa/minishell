/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_entry_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:26:55 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/16 15:26:55 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_tools.h"

char	*env_entry_name(char *entry)
{
	char	*name;
	size_t	i;

	i = 0;
	if (!entry)
		return (NULL);
	while (entry[i] != '\0' && entry[i] != '=')
		i++;
	name = ft_strndup(entry, i);
	return (name);
}
