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

static bool	is_first(t_token *node)
{
	if (is_special(node) && !is_redirection(node))
	{
		printf(NAME": syntax error unexpected token '%s'\n", node->value);
		return (true);
	}
	return (false);
}

static bool	is_adjacent(t_token *prev, t_token *curr)
{
	if (is_special(prev) && is_special(curr))
	{
		printf(NAME": syntax error unexpected token '%s'\n", curr->value);
		return (true);
	}
	return (false);
}

static bool	is_closed_quote(t_token *node)
{
	int	i;

	i = 0;
	if (node->type == TK_DOUBLE_QUOTED || node->type == TK_SINGLE_QUOTED)
	{
		i = ft_strlen(node->value);
		if (i == 1 || node->value[i - 1] != node->value[0])
		{
			printf(NAME": syntax error missing closing quote\n");
			return (false);
		}
	}
	return (true);
}

static bool	is_last(t_token *node)
{
	if (node->type == TK_PIPE || is_redirection(node))
	{
		printf(NAME": syntax error unexpected token 'newline'\n");
		return (true);
	}
	return (false);
}

bool	is_correct_syntax(t_token *tokens)
{
	t_token	*current;
	t_token	*prev;

	current = tokens;
	if (!current)
		return (true);
	if (is_first(current))
		return (false);
	prev = current;
	current = current->next;
	while (current)
	{
		if (is_adjacent(prev, current))
			return (false);
		if (!is_closed_quote(current))
			return (false);
		prev = current;
		current = current->next;
	}
	if (is_last(prev))
		return (false);
	return (true);
}
