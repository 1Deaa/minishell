/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:46:48 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/10 19:32:52 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_special(t_token *node)
{
	if (node->type == TK_PIPE || node->type == TK_REDIR_IN
		|| node->type == TK_REDIR_OUT || node->type == TK_APPEND
		|| node->type == TK_HEREDOC || node->type == TK_AMPERSAND)
		return (true);
	else
		return (false);
}

bool	is_correct_syntax(t_token *tokens)
{
	t_token	*current;
	t_token	*prev;

	current = tokens;
	if (!current)
		return (true);
	if (is_special(current))
		return (false);
	prev = current;
	current = current->next;
	while (current)
	{
		if (is_special(prev) && is_special(current))
			return (false);
		prev = current;
		current = current->next;
	}
	if (prev->type == TK_PIPE)
		return (false);
	return (true);
}
