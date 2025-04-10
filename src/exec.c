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

static char *get_path(t_shell *shell, t_execmd *ecmd)
{
	char	*path;

	path = find_path(shell, ecmd->argv[0]);
	if (!path)
	{
		ft_printf(STDERR_FILENO, "%s: command not found\n", ecmd->argv[0]);
		return (NULL);
	}
	return (path);
}

static void	run_child(t_shell *shell, t_execmd *ecmd, char *path)
{
	shell_signal_reset();
	execve(path, ecmd->argv, shell->envp);
	ft_printf(2, NAME": execve error\n");
	free(path);
	exit(EXIT_FAILURE);
}

static void	child_exit(t_shell *shell, int *status, char *path)
{
	if (WIFEXITED(*status))
		shell->exit = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		shell->exit = 128 + WTERMSIG(*status);
	free(path);
}

void	run_exec(t_shell *shell, t_execmd *ecmd)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = get_path(shell, ecmd);
	if (!path)
		return ;
	pid = fork();
	if (pid < 0)
	{
		ft_printf(2, NAME": fork error\n");
		free(path);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		run_child(shell, ecmd, path);
	else
	{
		waitpid(pid, &status, 0);
		child_exit(shell, &status, path);
	}
}

void	execute(t_shell *shell, t_cmd *cmd)
{
	if (!cmd)
		return ;
	
	if (cmd->type == PS_EXEC)
	{
		run_exec(shell, (t_execmd *)cmd);
	}
}