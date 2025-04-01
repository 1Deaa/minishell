/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:23:49 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/13 22:55:20 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(const char *value)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
	{
		perror(NAME": failed to allocate memory for token!");
		return (NULL);
	}
	node->value = ft_strdup(value);
	if (!node->value)
	{
		perror(NAME": ft_strdup allocation error!");
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
		(*head)->prev = NULL;
	}
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		node->prev = current;
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
		printf("TOKEN: %s\tTYPE: %d\n", current->value, current->type);
		current = current->next;
	}
}

void	assign_token_types(t_token *tokens)
{
	while (tokens)
	{
		if (!ft_strcmp(tokens->value, "|"))
			tokens->type = TK_PIPE;
		else if (!ft_strcmp(tokens->value, "<"))
			tokens->type = TK_REDIR_IN;
		else if (!ft_strcmp(tokens->value, ">"))
			tokens->type = TK_REDIR_OUT;
		else if (!ft_strcmp(tokens->value, ">>"))
			tokens->type = TK_APPEND;
		else if (!ft_strcmp(tokens->value, "<<"))
			tokens->type = TK_HEREDOC;
		else if (tokens->value[0] == '\'')
			tokens->type = TK_SINGLE_QUOTED;
		else if (tokens->value[0] == '"')
			tokens->type = TK_DOUBLE_QUOTED;
		else
			tokens->type = TK_WORD;
		tokens = tokens->next;
	}
}
