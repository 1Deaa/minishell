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

extern int	g_status;

void	get_cmd(t_pak *cmd)
{
	DIR	*dir;

	dir = check_cmd(cmd);
	if (!is_builtin(cmd) && cmd && cmd->full_cmd && dir)
		shell_error(IS_DIR, *(cmd->full_cmd), 126);
	else if (!is_builtin(cmd) && cmd->full_path
		&& access(cmd->full_path, F_OK) == -1)
		shell_error(NDIR, cmd->full_path, 127);
	else if (!is_builtin(cmd) && cmd && cmd->full_path
		&& access(cmd->full_path, X_OK) == -1)
		shell_error(NPERM, cmd->full_path, 126);
	if (dir)
		closedir(dir);
}

void	*exec_pak(t_shell *shell, t_pak *cmd)
{
	int	fd[2];

	get_cmd(cmd);
	if (pipe(fd) == -1)
		return (shell_error(PIPERR, NULL, 1));
	if (!is_forkable(shell, cmd, fd))
		return (NULL);
	close(fd[WRITE_END]);
	if (cmd->next && cmd->next->infile == 0)
		cmd->next->infile = fd[READ_END];
	else
		close(fd[READ_END]);
	if (cmd->infile > 2)
		close(cmd->infile);
	if (cmd->outfile > 2)
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
			g_status = 0;//bn_exit(cmd); //TODO
		else if (!cmd->next && arg && !ft_strcmp(*arg, "cd"))
			g_status = 0;//bn_cd(shell); //TODO
		else if (!cmd->next && arg && !ft_strcmp(*arg, "export"))
			g_status = 0;//export(); //TODO
		else if (!cmd->next && arg && !ft_strcmp(*arg, "unset"))
			g_status = 0;//unset(); //TODO
		else
		{
			shell_signal_ignore();
			exec_pak(shell, cmd);
		}
		cmd = cmd->next;
	}
	while (0 < paks--)
		waitpid(-1, &g_status, 0);
	return (g_status);
}

void	pak_fork(t_shell *shell, t_pak *cmd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[WRITE_END]);
		close(fd[READ_END]);
		shell_error(FORKERR, NULL, 1);
	}
	else if (pid == 0)
		pak_process(shell, cmd, fd);
}

void	*is_forkable(t_shell *shell, t_pak *cmd, int fd[2])
{
	DIR	*dir;

	dir = NULL;
	if (cmd->full_cmd)
		dir = opendir(*(cmd->full_cmd));
	if (cmd->infile == -1 || cmd->outfile == -1)
		return (NULL);
	if ((cmd->full_path && access(cmd->full_path, X_OK) == 0) || is_builtin(cmd))
		pak_fork(shell, cmd, fd);
	else if (!is_builtin(cmd) && ((cmd->full_path
		&& !access(cmd->full_path, F_OK)) || dir))
		g_status = 126;
	else if (!is_builtin(cmd) && cmd->full_cmd)
		g_status = 127;
	if (dir)
		closedir(dir);
	return ("STAR");
}
