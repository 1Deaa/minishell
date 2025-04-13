/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:35:23 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/12 12:35:24 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	ft_open(const char *path, int flags, int mode)
// {
// 	if (mode > 0)
// 		return (open(path, flags, mode));
// 	else
// 		return (open(path, flags));
// }

// void	run_redir(t_shell *shell, t_redircmd *rcmd)
// {
// 	int	file;
// 	int	old_fd;

// 	old_fd = dup(rcmd->fd);
// 	file = ft_open(rcmd->file, rcmd->flags, rcmd->mode);
// 	dup2(file, rcmd->fd);
// 	close(file);
// 	execute(shell, rcmd->cmd);
// 	dup2(old_fd, rcmd->fd);
// 	close(old_fd);
// }
