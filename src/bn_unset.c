/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:51:54 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/16 13:51:56 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_shell *shell, t_pak *cmd)
{
	int	i;

	i = 1;
	close_pak_infile(cmd);
	while (cmd->full_cmd[i])
	{
		shell->envp = env_del(shell->envp, cmd->full_cmd[i]);
		i++;
	}
	return (0);
}
