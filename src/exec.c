/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halmuhis <halmuhis@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:12:56 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/06 15:36:54 by halmuhis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

static void	get_cmd(t_shell *shell, t_pak *cmd)
{
	DIR	*dir;

	dir = check_cmd(shell, cmd);
	if (!is_builtin(cmd) && cmd && cmd->full_cmd && dir)
		shell_error(shell, IS_DIR, *(cmd->full_cmd), 126);
	else if (!is_builtin(cmd) && cmd->full_path
		&& access(cmd->full_path, F_OK) == -1)
		shell_error(shell, NDIR, cmd->full_path, 1);
	else if (!is_builtin(cmd) && cmd && cmd->full_path
		&& access(cmd->full_path, X_OK) == -1)
		shell_error(shell, NPERM, cmd->full_path, 126);
	if (dir)
		closedir(dir);
}

void	*exec_pak(t_shell *shell, t_pak *cmd)
{
	int	fd[2];

	get_cmd(shell, cmd);
	if (pipe(fd) == -1)
		return (shell_error(shell, PIPERR, NULL, 1));
	if (!is_forkable(shell, cmd, fd))
	{
		if (fd[READ_END] > STDERR_FILENO)
			close(fd[READ_END]);
		if (fd[WRITE_END] > STDERR_FILENO)
			close(fd[WRITE_END]);
		return (NULL);
	}
	if (cmd->next)
	{
		cmd->next->infile = fd[READ_END];
		close(fd[WRITE_END]);
	}
	else
	{
		close(fd[WRITE_END]);
		close(fd[READ_END]);
	}
	if (cmd->infile > STDERR_FILENO)
		close(cmd->infile);
	if (cmd->outfile > STDERR_FILENO)
		close(cmd->outfile);
	return (NULL);
}

int	executer(t_shell *shell, t_pak *cmd)
{
	char	**arg;
	int		paks;

	paks = count_paks(cmd);
	while (cmd)
	{
		arg = cmd->full_cmd;
		if (arg && !ft_strcmp(*arg, "exit"))
			shell->e_status = bn_exit(shell, cmd);
		else if (!cmd->next && arg && !ft_strcmp(*arg, "cd"))
			shell->e_status = 0;//cd(shell); //TODO
		else if (!cmd->next && arg && !ft_strcmp(*arg, "export"))
			shell->e_status = export(cmd, &shell->envp);
		else if (!cmd->next && arg && !ft_strcmp(*arg, "unset"))
			shell->e_status = 0;//unset(); //TODO
		else
		{
			shell_signal_ignore();
			exec_pak(shell, cmd);
		}
		cmd = cmd->next;
	}
	wait_processes(shell, paks);
	return (shell->e_status);
}

void	pak_fork(t_shell *shell, t_pak *cmd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[WRITE_END]);
		close(fd[READ_END]);
		shell_error(shell, FORKERR, NULL, 1);
	}
	else if (pid == 0)
	{
		pak_process(shell, cmd, fd);
	}
	else if (pid > 0)
	{
		if (!cmd->next)
			shell->last_pid = pid;
	}
}

void	*is_forkable(t_shell *shell, t_pak *cmd, int fd[2])
{
	DIR	*dir;

	dir = NULL;
	if (cmd->full_cmd)
		dir = opendir(*(cmd->full_cmd));
	if (cmd->infile == -1 || cmd->outfile == -1)
		return (NULL);
	if ((cmd->full_path && access(cmd->full_path, X_OK) == 0) || \
		is_builtin(cmd))
		pak_fork(shell, cmd, fd);
	else if (!is_builtin(cmd) && ((cmd->full_path && \
		!access(cmd->full_path, F_OK)) || dir))
		shell->e_status = 126;
	else if (!is_builtin(cmd) && cmd->full_cmd)
		shell->e_status = 127;
	if (dir)
		closedir(dir);
	return ("STAR");
}
