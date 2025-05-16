/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_entry_grab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:47:42 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/16 16:47:43 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_tools.h"

/*
returns a pointer to value of NAME
*/
char	*env_entry_grab(char *entry)
{
	char	*value;
	size_t	i;

	i = 0;
	if (!entry || !ft_strchr(entry, '='))
		return (NULL);
	while (entry[i] != '=')
		i++;
	i++;
	value = entry + i;
	return (value);
}
