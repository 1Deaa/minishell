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

static bool	is_first(t_shell *shell, t_token *node)
{
	if (!ft_strcmp(node->value, "'") || !ft_strcmp(node->value, "\""))
	{
		shell_error(shell, QUOTE, "", 1);
		return (true);
	}
	if (is_special(node) && !is_redirection(node))
	{
		ft_printf(2, C_NAME": syntax error unexpected token '%s'\n",
			node->value);
		shell->e_status = 2;
		return (true);
	}
	return (false);
}

static bool	is_adjacent(t_shell *shell, t_token *prev, t_token *curr)
{
	if (prev->type == TK_PIPE && is_redirection(curr))
		return (false);
	if (is_special(prev) && is_special(curr))
	{
		shell_error(shell, NEARERR, curr->value, 2);
		return (true);
	}
	return (false);
}

static bool	is_closed_quote(t_shell *shell, t_token *node)
{
	int	i;

	i = 0;
	if (node->type == TK_DOUBLE_QUOTED || node->type == TK_SINGLE_QUOTED)
	{
		i = ft_strlen(node->value);
		if (i == 1 || node->value[i - 1] != node->value[0])
		{
			shell_error(shell, QUOTE, "", 1);
			return (false);
		}
	}
	return (true);
}

static bool	is_last(t_shell *shell, t_token *node)
{
	if (node->type == TK_PIPE || is_redirection(node))
	{
		shell_error(shell, NEARERR, "`newline'", 2);
		return (true);
	}
	return (false);
}

bool	is_correct_syntax(t_shell *shell, t_token *tokens)
{
	t_token	*current;
	t_token	*prev;

	current = tokens;
	if (!current)
		return (true);
	if (is_first(shell, current))
		return (false);
	prev = current;
	current = current->next;
	while (current)
	{
		if (is_adjacent(shell, prev, current))
			return (false);
		if (!is_closed_quote(shell, current))
			return (false);
		prev = current;
		current = current->next;
	}
	if (is_last(shell, prev))
		return (false);
	return (true);
}
