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

void	*check_to_fork(t_shell *shell, t_pak *cmd, int fd[2]);
int		execute(t_shell *shell, t_pak *cmd);
void	*exec_cmd(t_shell *shell, t_pak *cmd);
bool	is_builtin(t_pak *cmd);
void	child_builtin(t_shell *shell, t_pak *cmd, int len);
void	*child_redir(t_pak *cmd, int fd[2]);
void	*child_process(t_shell *shell, t_pak *cmd, int fd[2]);
void	exec_fork(t_shell *shell, t_pak *cmd, int fd[2]);

int	executer(t_shell *shell, t_pak *cmd)
{
	char	**arg;
	int		len;
	int	i;

	i = count_paks(cmd);
	while (cmd)
	{
		arg = cmd->full_cmd;
		if (arg)
			len = ft_strlen(*arg);
		if (arg && !ft_strncmp(*arg, "exit", len) && len == 4)
			g_status = 0;//bn_exit(cmd); //TODO
		else if (!cmd->next && arg && !ft_strncmp(*arg, "cd", len) && len == 2)
			g_status = 0;//bn_cd(shell); //TODO
		else
		{
			shell_signal_ignore();
			exec_cmd(shell, cmd);
		}
		cmd = cmd->next;
	}
	while (i-- > 0)
		waitpid(-1, &g_status, 0);
	return (g_status);
}

void	*exec_cmd(t_shell *shell, t_pak *cmd)
{
	int	fd[2];

	//get_cmd(shell, cmd); //TODO
	if (pipe(fd) == -1)
		return (shell_error(PIPERR, NULL, 1));
	if (!check_to_fork(shell, cmd, fd))
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

bool	is_builtin(t_pak *cmd)
{
	int	len;

	if (!cmd->full_cmd)
		return (false);
	if ((cmd->full_cmd && ft_strchr(*(cmd->full_cmd), '/')) || (cmd->full_path
		&& ft_strchr(cmd->full_path, '/')))
		return (false);
	len = ft_strlen(*(cmd->full_cmd));
	if (!ft_strncmp(*(cmd)->full_cmd, "pwd", len) && len == 3)
		return (true);
	if (!ft_strncmp(*(cmd->full_cmd), "cd", len) && len == 2)
		return (true);
	if (!ft_strncmp(*(cmd->full_cmd), "env", len) && len == 3)
		return (true);
	if (!ft_strncmp(*(cmd->full_cmd), "export", len) && len == 6)
		return (true);
	if (!ft_strncmp(*(cmd->full_cmd), "unset", len) && len == 5)
		return (true);
	if (!ft_strncmp(*(cmd->full_cmd), "exit", len) && len == 4)
		return (true);
	if (!ft_strncmp(*(cmd->full_cmd), "echo", len) && len == 4)
		return (true);
	return (false);
}

void	child_builtin(t_shell *shell, t_pak *cmd, int len)
{
	shell_signal_reset();
	if (!is_builtin(cmd) && cmd->full_cmd)
		execve(cmd->full_path, cmd->full_cmd, shell->envp);
	else if (cmd->full_cmd && !ft_strncmp(*(cmd->full_cmd), "pwd", len) \
		&& len == 3)
		g_status = 0;//bn_pwd(); //TODO
	else if (is_builtin(cmd) && cmd->full_cmd && \
		!ft_strncmp(*(cmd->full_cmd), "echo", len) && len == 4)
		g_status = 0;//bn_echo(cmd); //TODO
	else if (is_builtin(cmd) && cmd->full_cmd && \
		!ft_strncmp(*(cmd->full_cmd), "env", len) && len == 3)
		g_status = 0;//bn_env(); //TODO
}

void	*child_redir(t_pak *cmd, int fd[2])
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

void	*child_process(t_shell *shell, t_pak *cmd, int fd[2])
{
	int	len;

	len = 0;
	if (cmd->full_cmd)
		len = ft_strlen(*(cmd->full_cmd));
	child_redir(cmd, fd);
	close(fd[READ_END]);
	child_builtin(shell, cmd, len);
	free_paks(cmd);
	cmd = NULL;
	exit(g_status);
}

void	exec_fork(t_shell *shell, t_pak *cmd, int fd[2])
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
		child_process(shell, cmd, fd);
}

void	*check_to_fork(t_shell *shell, t_pak *cmd, int fd[2])
{
	DIR	*dir;

	dir = NULL;
	if (cmd->full_cmd)
		dir = opendir(*(cmd->full_cmd));
	if (cmd->infile == -1 || cmd->outfile == -1)
		return (NULL);
	if ((cmd->full_path && access(cmd->full_path, X_OK) == 0) || is_builtin(cmd))
		exec_fork(shell, cmd, fd);
	else if (!is_builtin(cmd) && ((cmd->full_path
		&& access(cmd->full_path, F_OK)) == 0 || dir))
		g_status = 126;
	else if (!is_builtin(cmd) && cmd->full_cmd)
		g_status = 127;
	if (dir)
		closedir(dir);
	return ("STAR");
}
