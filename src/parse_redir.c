/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halmuhis <halmuhis@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:02:25 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/28 17:39:59 by halmuhis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_redir_out(t_shell *shell, t_pak **curr, t_token **token)
{
	(*token) = (*token)->next;
	if ((*curr)->infile != -1 && (*curr)->outfile != -1)
		(*curr)->outfile = get_fd(shell, (*curr)->outfile,
				*token, TK_REDIR_OUT);
	if (*token)
		(*token) = (*token)->next;
	if (!(*curr) || (*curr)->outfile == -1)
	{
		shell->e_status = 1;
		if (*curr)
			(*curr)->outfile = -1;
	}
	else
	{
		if ((*curr)->infile > 0)
			shell->e_status = 0;
	}
	return (0);
}

int	parse_redir_app(t_shell *shell, t_pak **curr, t_token **token)
{
	(*token) = (*token)->next;
	if ((*curr)->infile != -1 && (*curr)->outfile != -1)
		(*curr)->outfile = get_fd(shell, (*curr)->outfile, *token, TK_APPEND);
	if (*token)
		(*token) = (*token)->next;
	if (!(*curr) || (*curr)->outfile == -1)
	{
		shell->e_status = 1;
		if (*curr)
			(*curr)->outfile = -1;
	}
	else
	{
		if ((*curr)->infile > 0)
			shell->e_status = 0;
	}
	return (0);
}

int	parse_redir_in(t_shell *shell, t_pak **curr, t_token **token)
{
	(*token) = (*token)->next;
	if ((*curr)->infile != -1 && (*curr)->outfile != -1)
		(*curr)->infile = get_fd(shell, (*curr)->infile, *token, TK_REDIR_IN);
	if (*token)
		(*token) = (*token)->next;
	if (!(*curr) || (*curr)->infile == -1)
	{
		shell->e_status = 1;
		if (*curr)
			(*curr)->infile = -1;
	}
	else
	{
		if ((*curr)->outfile > 0)
			shell->e_status = 0;
	}
	return (0);
}

int	parse_redir(t_shell *shell, t_pak **curr, t_token **token)
{
	if ((*token)->type == TK_REDIR_OUT)
	{
		parse_redir_out(shell, curr, token);
	}
	else if ((*token)->type == TK_REDIR_IN)
	{
		parse_redir_in(shell, curr, token);
	}
	else if ((*token)->type == TK_APPEND)
	{
		parse_redir_app(shell, curr, token);
	}
	else if ((*token)->type == TK_HEREDOC)
	{
		parse_heredoc(shell, curr, token);
	}
	return (0);
}

int	parse_heredoc(t_shell *shell, t_pak **curr, t_token **token)
{
	int	old_infile;

	(*token) = (*token)->next;
	if ((*curr)->infile > STDERR_FILENO)
		close((*curr)->infile);
	old_infile = (*curr)->infile;
	(*curr)->infile = handle_heredoc((*token)->value);
	if (old_infile == -1)
		close((*curr)->infile);
	if (old_infile == -1)
		(*curr)->infile = old_infile;
	if (*token)
		(*token) = (*token)->next;
	if (!(*curr) || (*curr)->infile == -1)
	{
		shell->e_status = 1;
		if (*curr)
			(*curr)->infile = -1;
	}
	else
	{
		if ((*curr)->outfile > 0)
			shell->e_status = 0;
	}
	return (0);
}
