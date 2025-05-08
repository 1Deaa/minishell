/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 06:25:06 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/23 06:25:07 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

DIR	*check_cmd(t_shell *shell, t_pak *cmd)
{
	DIR	*dir;

	dir = NULL;
	if (cmd && cmd->full_cmd)
		dir = opendir(*(cmd->full_cmd));
	if (cmd && cmd->full_cmd && ft_strchr(*(cmd->full_cmd), '/') && !dir)
	{
		free(cmd->full_path);
		cmd->full_path = ft_strdup(*(cmd->full_cmd));
	}
	if (cmd && !cmd->full_path && cmd->full_cmd && !dir && !is_builtin(cmd))
	{
		shell_error(shell, NCMD, *(cmd->full_cmd), 127);
	}
	return (dir);
}

bool	is_builtin(t_pak *cmd)
{
	char	*name;

	if (!cmd || !cmd->full_cmd || !cmd->full_cmd[0])
		return (false);
	name = cmd->full_cmd[0];
	if (ft_strchr(name, '/'))
		return (false);
	if (!ft_strcmp(name, "pwd")
		|| !ft_strcmp(name, "cd")
		|| !ft_strcmp(name, "echo")
		|| !ft_strcmp(name, "env")
		|| !ft_strcmp(name, "export")
		|| !ft_strcmp(name, "exit")
		|| !ft_strcmp(name, "unset"))
		return (true);
	return (false);
}

void	*pak_redir(t_shell *shell, t_pak *cmd, int fd[2])
{
	if (cmd->infile == -1 || cmd->outfile == -1)
	{
		if (cmd->next)
			close(fd[WRITE_END]);
		if (cmd->prev)
			close(fd[READ_END]);
		return (NULL);
	}
	if (pak_redir_util(shell, cmd, fd) == NULL)
		return (NULL);
	if (!cmd->prev)
		close(fd[READ_END]);
	if (!cmd->next)
		close(fd[WRITE_END]);
	return ("STAR");
}

void	*pak_process(t_shell *shell, t_pak *cmd, int fd[2])
{
	if (pak_redir(shell, cmd, fd) == NULL)
	{
		free_paks(shell, shell->cmds);
		exit(shell->e_status);
	}
	shell_signal_reset();
	if (fd[READ_END] > STDERR_FILENO)
		close(fd[READ_END]);
	if (fd[WRITE_END] > STDERR_FILENO)
		close(fd[WRITE_END]);
	if (!is_builtin(cmd) && cmd->full_cmd)
		execve(cmd->full_path, cmd->full_cmd, shell->envp);
	else if (is_builtin(cmd) && cmd->full_cmd && \
		!ft_strcmp(*(cmd->full_cmd), "pwd"))
		shell->e_status = pwd();
	else if (is_builtin(cmd) && cmd->full_cmd && \
		!ft_strcmp(*(cmd->full_cmd), "echo"))
		shell->e_status = echo(cmd);
	else if (is_builtin(cmd) && cmd->full_cmd && \
		!ft_strcmp(*(cmd->full_cmd), "env"))
		shell->e_status = env(shell->envp);
	free_paks(shell, shell->cmds);
	exit(shell->e_status);
}

void	wait_processes(t_shell *shell, int count)
{
	t_proc	process;

	while (0 < count)
	{
		process.pid = waitpid(-1, &(process.status), 0);
		if (process.pid == shell->last_pid)
		{
			if (WIFEXITED(process.status))
				shell->e_status = WEXITSTATUS(process.status);
			else if (WIFSIGNALED(process.status))
				shell->e_status = 128 + WTERMSIG(process.status);
			else
				shell->e_status = process.status;
		}
		count--;
	}
}
