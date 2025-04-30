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

extern int	g_status;

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
		shell->l_status = 127;
		shell_error(NCMD, *(cmd->full_cmd), shell->l_status);
		if (!cmd->next)
			shell->last_ncmd = true;
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

void	*pak_redir(t_pak *cmd, int fd[2])
{
	if (cmd->infile != STDIN_FILENO)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			return (shell_error(DUPERR, NULL, 1));
		close(cmd->infile);
	}
	if (cmd->outfile != STDOUT_FILENO)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			return (shell_error(DUPERR, NULL, 1));
		close(cmd->outfile);
	}
	else if (cmd->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		return (shell_error(DUPERR, NULL, 1));
	close(fd[WRITE_END]);
	return ("STAR");
}

void	*pak_process(t_shell *shell, t_pak *cmd, int fd[2])
{
	pak_redir(cmd, fd);
	close(fd[READ_END]);
	shell_signal_reset();
	if (!is_builtin(cmd) && cmd->full_cmd)
		execve(cmd->full_path, cmd->full_cmd, shell->envp);
	else if (is_builtin(cmd) && cmd->full_cmd && \
		!ft_strcmp(*(cmd->full_cmd), "pwd"))
		g_status = pwd();
	else if (is_builtin(cmd) && cmd->full_cmd && \
		!ft_strcmp(*(cmd->full_cmd), "echo"))
		g_status = echo(cmd);
	else if (is_builtin(cmd) && cmd->full_cmd && \
		!ft_strcmp(*(cmd->full_cmd), "env"))
		g_status = env(shell->envp);
	free_paks(shell, cmd);
	exit(g_status);
}
