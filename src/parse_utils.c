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

int	count_word_tokens(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type == TK_WORD)
	{
		i++;
		token = token->next;
	}
	return (i);
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
	free_tokens(shell->tokens);
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

int	get_fd(t_shell *shell, int oldfd, char *file, int type)
{
	int	fd;

	if (oldfd > 2)
		close(oldfd);
	if (!file)
		return (-1);
	if (access(file, F_OK) == -1 && type == TK_REDIR_IN)
		shell_error(shell, NDIR, file, 127);
	else if (access(file, R_OK) == -1 && type == TK_REDIR_IN)
		shell_error(shell, NPERM, file, 126);
	else if (access(file, W_OK) == -1 && access(file, F_OK) == 0 && \
		(type == TK_REDIR_OUT || type == TK_APPEND))
		shell_error(shell, NPERM, file, 126);
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