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

static int	many_args(t_shell *shell)
{
	shell->exit = false;
	ft_printf(2, "%s: %s: too many arguments\n", C_NAME, "exit");
	return (1);
}

int	bn_exit(t_shell *shell, t_pak *pak)
{
	if (!pak->next)
	{
		if (!pak->prev)
			shell->exit = true;
		shell->e_status = 0;
	}
	if (!pak->full_cmd || !pak->full_cmd[1])
		return (0);
	if (pak->full_cmd[2])
		return (many_args(shell));
	return (1);
}
