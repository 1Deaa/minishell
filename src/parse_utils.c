/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:24:01 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/19 14:24:04 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args_tokens(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == TK_WORD || token->type == TK_DOUBLE_QUOTED
			|| token->type == TK_SINGLE_QUOTED)
			i++;
		else if (token->type == TK_PIPE)
			break ;
		else if (is_redirection(token))
			token = token->next;
		if (token)
			token = token->next;
	}
	return (i);
}

void	fill_args_tokens(t_shell *shell, t_args *args, t_pak **cur,\
	t_token **token)
{
	int		i;

	i = 0;
	while (token && *token && i < args->argc)
	{
		if ((*token)->type == TK_PIPE)
			break ;
		if (is_redirection(*token))
			parse_redir(shell, cur, token);
		if (*token)
		{
			args->argv[i++] = (*token)->value;
			*token = (*token)->next;
		}
	}
	args->argv[i] = NULL;
}

void	free_paks(t_shell *shell, t_pak *head)
{
	t_pak	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->full_cmd)
			free(head->full_cmd);
		if (head->full_path)
			free(head->full_path);
		free(head);
		head = tmp;
	}
	shell->cmds = NULL;
	if (shell->tokens)
		free_tokens(shell->tokens);
	shell->tokens = NULL;
}

int	count_paks(t_pak *head)
{
	int	count;

	count = 0;
	while (head)
	{
		count ++;
		head = head->next;
	}
	return (count);
}

int	get_fd(t_shell *shell, int oldfd, t_token *token, int type)
{
	int	fd;

	if (oldfd > 2)
		close(oldfd);
	if (!token || !token->value)
		return (ambiguous_redirect(shell, "", 1));
	if (is_redirection(token->prev) && ft_strchr(token->value, ' ')
		&& token->type == TK_WORD)
		return (ambiguous_redirect(shell, token->value, 1));
	else if (access(token->value, F_OK) == -1 && type == TK_REDIR_IN)
		return (redir_error(shell, NDIR, token->value, 127));
	else if (access(token->value, R_OK) == -1 && type == TK_REDIR_IN)
		return (redir_error(shell, NPERM, token->value, 126));
	else if (access(token->value, W_OK) == -1 && !access(token->value, F_OK)
		&& (type == TK_REDIR_OUT || type == TK_APPEND))
		return (redir_error(shell, NPERM, token->value, 126));
	if (TK_APPEND == type)
		fd = open(token->value, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (TK_REDIR_OUT == type)
		fd = open(token->value, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (TK_REDIR_IN == type && oldfd != -1)
		fd = open(token->value, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}
