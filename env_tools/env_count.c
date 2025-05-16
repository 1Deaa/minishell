/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:03:15 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/16 11:03:17 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_tools.h"

/*
count args inside ENVP
*/
size_t	env_count(char **envp)
{
	size_t	count;

	count = 0;
	while (envp && envp[count])
	{
		count++;
	}
	return (count);
}
