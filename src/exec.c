/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:12:56 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/01 22:12:56 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_exec(t_shell *shell, t_execmd *ecmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execve(find_path(shell, ecmd->argv[0]), ecmd->argv, shell->envp);
		//TODO: fix potential memory leak
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

void	execute(t_shell *shell, t_cmd *cmd)
{
	if (NULL == cmd)
		return ;
	if (cmd->type == PS_EXEC)
	{
		run_exec(shell, (t_execmd *)cmd);
	}
}
