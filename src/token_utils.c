/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:23:49 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/09 07:18:03 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token	*new_token(const char *value)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
	{
		perror("memory allocation error!");
		return (NULL);
	}
	node->value = ft_strdup(value);
	if (!node->value)
	{
		perror("ft_strdup allocation error!");
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

void	add_token(t_token **head, const char *value)
{
	t_token	*node;
	t_token	*current;

	node = new_token(value);
	if (!node)
		return ;
	if (*head == NULL)
	{
		*head = node;
	}
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = node;
	}
}

void	free_tokens(t_token	*token)
{
	t_token	*current;

	while (token)
	{
		current = token;
		token = token->next;
		free(current->value);
		free(current);
	}
}

void	print_tokens(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		printf("TOKEN: %s\n", current->value);
		current = current->next;
	}
}
