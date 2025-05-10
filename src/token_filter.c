/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_filter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:30:39 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/10 12:30:41 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	combine_tokens(t_token *curr, t_token *next)
{
	char	*value;

	value = ft_strjoin(curr->value, next->value);
	if (!value)
		return ;
	free(next->value);
	curr->value = value;
	curr->combine = next->combine;
	curr->next = next->next;
	if (next->next)
		(next->next)->prev = curr;
	free(next);
}

static void	delete_empty_token(t_token **head, t_token *prev, t_token *target)
{
	if (prev)
		prev->next = target->next;
	else
		*head = target->next;
	if (target->next)
		(target->next)->prev = prev;
	free(target->value);
	free(target);
}

t_token	*filter_tokens(t_token *head)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*next;

	prev = NULL;
	curr = head;
	while (curr)
	{
		next = curr->next;
		if ((!curr->value || !(curr->value[0])) && curr->type == TK_WORD)
			delete_empty_token(&head, prev, curr);
		else
			prev = curr;
		curr = next;
	}
	curr = head;
	while (curr)
	{
		if (true == curr->combine && curr->next)
			combine_tokens(curr, curr->next);
		else
			curr = curr->next;
	}
	return (head);
}
