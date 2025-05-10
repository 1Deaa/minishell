/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:51:11 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/16 14:51:12 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_error(t_shell *shell, int err_type, char *param, int err)
{
	shell->e_status = err;
	if (err_type == NDIR)
		ft_printf(2, "%s: No such file or directory: ", C_NAME);
	else if (err_type == IS_DIR)
		ft_printf(2, "%s: Is a directory: ", C_NAME);
	else if (err_type == NOT_DIR)
		ft_printf(2, "%s: Not a directory: ", C_NAME);
	else if (err_type == NPERM)
		ft_printf(2, "%s: permission denied: ", C_NAME);
	ft_printf(2, "%s\n", param);
	return (-1);
}

void	*shell_error(t_shell *shell, int err_type, char *param, int err)
{
	shell->e_status = err;
	if (err_type == QUOTE)
		ft_printf(2, "%s: error while looking for matching quote!", C_NAME);
	else if (err_type == NPERM)
		ft_printf(2, "%s: permission denied: ", C_NAME);
	else if (err_type == NCMD)
		ft_printf(2, "%s: command not found: ", C_NAME);
	else if (err_type == DUPERR)
		ft_printf(2, "%s: dup2 failed\n", C_NAME);
	else if (err_type == FORKERR)
		ft_printf(2, "%s: fork failed\n", C_NAME);
	else if (err_type == PIPERR)
		ft_printf(2, "%s: error creating pipe\n", C_NAME);
	else if (err_type == NEARERR)
		ft_printf(2, "%s: syntax error near unexpected token: ", C_NAME);
	else if (err_type == MEM)
		ft_printf(2, "%s: no memory left on device\n", C_NAME);
	ft_printf(2, "%s\n", param);
	return (NULL);
}

void	print_heredoc_warning(char *line, char *delimiter)
{
	if (!line)
		ft_printf(2, "%s: %s: here-document delimited by end-of-file \
(wanted `%s')\n", C_NAME, "warning", delimiter);
}

int	ambiguous_redirect(t_shell *shell, char *name, int err)
{
	shell->e_status = err;
	ft_printf(2, "%s: %s: ambiguous redirect\n", C_NAME, name);
	return (-1);
}

void	*pak_redir_util(t_shell *shell, t_pak *cmd, int fd[2])
{
	if (cmd->infile != STDIN_FILENO)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			return (shell_error(shell, DUPERR, NULL, 1));
		close(cmd->infile);
	}
	else if (cmd->prev)
	{
		if (dup2(fd[READ_END], STDIN_FILENO) == -1)
			return (shell_error(shell, DUPERR, NULL, 1));
		close(fd[READ_END]);
	}
	if (cmd->outfile != STDOUT_FILENO)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			return (shell_error(shell, DUPERR, NULL, 1));
		close(cmd->outfile);
	}
	else if (cmd->next)
	{
		if (dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
			return (shell_error(shell, DUPERR, NULL, 1));
		close(fd[WRITE_END]);
	}
	return ("STAR");
}
