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

static void	free_token_node(t_token *node)
{
	if (!node)
		return;
	free(node->value);
	free(node);
}

t_token *retokenize(t_token *head)
{
	 t_token *curr = head;
	 t_token *new_head = head;
 
	 while (curr && curr->type == TK_WORD) {
		 // Save next pointer before we replace curr
		 t_token *next_orig = curr->next;
 
		 // Generate a new sublist for curr->value
		 t_token *sub = tokenizer(curr->value, REMAKE);
 
		 if (sub) {
			 // Find tail of new sublist
			 t_token *sub_tail = sub;
			 while (sub_tail->next)
				 sub_tail = sub_tail->next;
 
			 // Splice sublist into main list in place of curr
 
			 // 1) Link previous node
			 if (curr->prev) {
				 curr->prev->next = sub;
				 sub->prev = curr->prev;
			 } else {
				 // curr was head
				 new_head = sub;
				 sub->prev = NULL;
			 }
 
			 // 2) Link next node
			 if (next_orig) {
				 next_orig->prev = sub_tail;
				 sub_tail->next = next_orig;
			 } else {
				 sub_tail->next = NULL;
			 }
 
			 // Free the old token node (but not sublist)
			 free_token_node(curr);
 
			 // Advance curr to the node after the inserted sublist
			 curr = sub_tail->next;
		 } else {
			 // If tokenizer returned NULL, skip replacement
			 curr = next_orig;
		 }
	 }
 
	 return new_head;
}
 