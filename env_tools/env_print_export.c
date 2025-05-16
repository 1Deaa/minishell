/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:09:48 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/16 11:10:04 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_tools.h"

/*
prints ENVP with PREFIX for export
*/
void	env_print_export(const char *prefix, char **envp)
{
	int		i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		printf("%s %s\n", prefix, envp[i]);
		i++;
	}
}
