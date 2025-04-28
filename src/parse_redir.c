/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halmuhis <halmuhis@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:02:25 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/28 14:59:43 by halmuhis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	get_fd(int oldfd, char *file, int type)
{
	int	fd;

	if (oldfd > 2)
		close(oldfd);
	if (!file)
		return (-1);
	if (access(file, F_OK) == -1 && type == TK_REDIR_IN)
		shell_error(NDIR, file, 127);
	else if (access(file, R_OK) == -1 && type == TK_REDIR_IN)
		shell_error(NPERM, file, 126);
	else if (access(file, W_OK) == -1 && access(file, F_OK) == 0 && \
		(type == TK_REDIR_OUT || type == TK_APPEND))
		shell_error(NPERM, file, 126);
	if (TK_APPEND == type)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (TK_REDIR_OUT == type)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (TK_REDIR_IN == type && oldfd != -1)
		fd = open(file, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

int	parse_redir_out(t_pak **curr, t_token **token)
{
	(*token) = (*token)->next;
	(*curr)->outfile = get_fd((*curr)->outfile, (*token)->value, TK_REDIR_OUT);
	(*token) = (*token)->next;
	if (!(*curr) || (*curr)->outfile == -1)
	{
		g_status = 1;
		return (-1);
	}
	return (0);
}

int	parse_redir_app(t_pak **curr, t_token **token)
{
	(*token) = (*token)->next;
	(*curr)->outfile = get_fd((*curr)->outfile, (*token)->value, TK_APPEND);
	(*token) = (*token)->next;
	if (!(*curr) || (*curr)->outfile == -1)
	{
		g_status = 1;
		return (-1);
	}
	return (0);
}

int	parse_redir_in(t_pak **curr, t_token **token)
{
	(*token) = (*token)->next;
	(*curr)->infile = get_fd((*curr)->infile, (*token)->value, TK_REDIR_IN);
	(*token) = (*token)->next;
	if (!(*curr) || (*curr)->outfile == -1)
	{
		g_status = 1;
		return (-1);
	}
	return (0);
}

int	parse_redir(t_pak **curr, t_token **token)
{
	if ((*token)->type == TK_REDIR_OUT)
	{
		if (parse_redir_out(curr, token) < 0)
			return (-1);
	}
	else if ((*token)->type == TK_REDIR_IN)
	{
		if (parse_redir_in(curr, token) < 0)
			return (-1);
	}
	else if ((*token)->type == TK_APPEND)
	{
		if (parse_redir_app(curr, token) < 0)
			return (-1);
	}
	else if ((*token)->type == TK_HEREDOC)
	{
		(*token) = (*token)->next;
		(*curr)->infile = handle_heredoc((*token)->value);
		(*token) = (*token)->next;
		if (!(*curr) || (*curr)->infile == -1)
		{
			g_status = 1;
			return (-1);
		}
	}
	return (0);
}
