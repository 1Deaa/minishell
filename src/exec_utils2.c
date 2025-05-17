/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:55:06 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/10 12:55:07 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_fork(int infile, int outfile, int fd[2])
{
	if (fd[READ_END] > STDERR_FILENO)
		close(fd[READ_END]);
	if (fd[WRITE_END] > STDERR_FILENO)
		close(fd[WRITE_END]);
	if (infile > STDERR_FILENO)
		close(infile);
	if (outfile > STDERR_FILENO)
		close(outfile);
}

void	close_pak_infile(t_pak *pak)
{
	if (pak && pak->infile > STDERR_FILENO && pak->infile != -1)
		close(pak->infile);
}

void	update_underscore_env(t_shell *shell, t_pak *cmd)
{
	int		i;

	i = 0;
	if (!cmd || !cmd->full_cmd || !cmd->full_cmd[i])
		return ;
	while (cmd && cmd->full_cmd && cmd->full_cmd[i])
		i++;
	env_update(shell->envp, "_", cmd->full_cmd[i - 1]);
}

void	close_inoutfiles(int infile, int outfile)
{
	if (infile > STDERR_FILENO)
		close(infile);
	if (outfile > STDERR_FILENO)
		close(outfile);
}
