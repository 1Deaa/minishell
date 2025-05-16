/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_entry_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:27:20 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/16 15:27:21 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_tools.h"

char	*env_entry_value(char *entry)
{
	char	*value;
	size_t	i;

	i = 0;
	if (!entry || !ft_strchr(entry, '='))
		return (NULL);
	while (entry[i] != '=')
		i++;
	i++;
	value = ft_strdup(entry + i);
	return (value);
}
