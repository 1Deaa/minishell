/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:23:05 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/13 22:23:06 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(int argc, char **argv, char **envp)
{
	if (argc != 1)
	{
		ft_printf(2, "env: no arguments allowed.\n");
		return ;
	}
	(void)argv;
	print_envp("", envp);
}
