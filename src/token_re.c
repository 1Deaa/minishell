/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_re.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:21:49 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/03 15:21:49 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_token_node(t_token *node)
{
	if (!node)
		return ;
	free(node->value);
	free(node);
}

t_token	*splice_in_sublist(t_token *old_token, t_token *sub)
{
	t_token	*next_orig;
	t_token	*tail;

	next_orig = old_token->next;
	tail = sub;
	while (tail->next)
		tail = tail->next;
	if (old_token->prev)
	{
		old_token->prev->next = sub;
		sub->prev = old_token->prev;
	}
	else
		sub->prev = NULL;
	if (next_orig)
	{
		next_orig->prev = tail;
		tail->next = next_orig;
	}
	else
		tail->next = NULL;
	free_token_node(old_token);
	return (tail->next);
}

t_token	*remove_and_free_token(t_token *token)
{
	t_token	*prev;
	t_token	*next;

	prev = token->prev;
	next = token->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free_token_node(token);
	return (next);
}

t_token	*retokenize(t_token *head)
{
	t_token	*curr;
	t_token	*new_head;
	t_token	*sublist;
	t_token	*next;

	curr = head;
	new_head = head;
	while (curr && curr->type == TK_WORD)
	{
		sublist = tokenizer(curr->value, REMAKE);
		if (sublist)
		{
			next = splice_in_sublist(curr, sublist);
			if (curr == new_head)
				new_head = sublist;
		}
		else
		{
			next = remove_and_free_token(curr);
			if (curr == new_head)
				new_head = next;
		}
		curr = next;
	}
	return (new_head);
}
