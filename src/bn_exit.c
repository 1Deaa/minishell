/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:23:15 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/30 13:23:15 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static int	many_args(t_shell *shell, t_pak *pak)
{
	shell->exit = false;
	ft_printf(2, "%s: %s: too many arguments\n", NAME, "exit");
	if (!pak->next)
	{
		shell->last_ncmd = true;
		shell->l_status = 1;
	}
	return (1);
}

int	bn_exit(t_shell *shell, t_pak *pak)
{
	if (!pak->next)
		shell->exit = true;
	if (!pak->full_cmd || !pak->full_cmd[1])
		return (0);
	if (pak->full_cmd[2])
		return (many_args(shell, pak));
	return (1);
}
