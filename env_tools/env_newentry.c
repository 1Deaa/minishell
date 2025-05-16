/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_newentry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:25:09 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/16 13:25:10 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_tools.h"

static void	fill_entry(char *entry, char *name, char *value)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (name[i] != '\0')
	{
		entry[i] = name[i];
		i++;
	}
	entry[i] = '=';
	i++;
	j = 0;
	while (value[j] != '\0')
	{
		entry[i] = value[j];
		i++;
		j++;
	}
	entry[i] = '\0';
}

char	*env_newentry(char *name, char *value)
{
	size_t	len;
	char	*entry;

	if (!name || !value)
		return (NULL);
	len = ft_strlen(name) + ft_strlen(value);
	entry = (char *)malloc(sizeof(char) * (len + 1 + 1));
	if (!entry)
	{
		write(2, "Memory allocation failed inside env_newentry\n", 46);
		return (NULL);
	}
	fill_entry(entry, name, value);
	return (entry);
}
