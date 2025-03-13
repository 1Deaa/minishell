/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:46:48 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/13 21:46:32 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_redirection(t_token *node)
{
	if (node->type == TK_APPEND || node->type == TK_HEREDOC
		|| node->type == TK_REDIR_IN || node->type == TK_REDIR_OUT)
		return (true);
	return (false);
}

static bool	is_special(t_token *node)
{
	if (node->type == TK_PIPE || is_redirection(node)
		|| node->type == TK_AMPERSAND)
		return (true);
	else
		return (false);
}

static bool	is_closed_quote(t_token *node)
{
	int		i;

	i = 0;
	if (node->type == TK_DOUBLE_QUOTED || node->type == TK_SINGLE_QUOTED)
	{
		i = ft_strlen(node->value);
		if (i == 1)
			return (false);
		if (node->value[(i - 1)] != node->value[0])
			return (false);
	}
	return (true);
}

bool	is_correct_syntax(t_token *tokens)
{
	t_token	*current;
	t_token	*prev;

	current = tokens;
	if (!current)
		return (true);
	if (is_special(current) && !is_redirection(current))
		return (false);
	prev = current;
	current = current->next;
	while (current)
	{
		if (is_special(prev) && is_special(current))
			return (false);
		if (!is_closed_quote(current))
			return (false);
		prev = current;
		current = current->next;
	}
	if (prev->type == TK_PIPE || is_redirection(prev))
		return (false);
	return (true);
}
