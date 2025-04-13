/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:45:02 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/13 22:45:03 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(int argc, char **argv, char **envp)
{
	(void)argc;
	if (!envp)
		return ;
	if (!argv[1])
	{
		print_envp("declare -x", envp);
		return ;
	}
}
