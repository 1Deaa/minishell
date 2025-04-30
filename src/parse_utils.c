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

extern int	g_status;

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
