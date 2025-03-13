/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:36:47 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/14 00:01:37 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_word(t_token *token)
{
	unsigned int	i;
	char			*temp;
	bool			dollar;

	dollar = false;
	i = 0;
	temp = NULL;
	while (token->value && token->value[i] != '\0')
	{
		if (token->value[i] == '$')
		{
			if (!dollar)
				temp = ft_strndup(token->value, i);
			temp = ft_strjoin(temp, "EXPAND!");
			dollar = true;
		}
		i++;
	}
	if (dollar)
	{
		free(token->value);
		token->value = temp;
	}
}

/*static void	expand_quoted(t_token *token)
{
	TODO
}*/

t_token	*expander(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == TK_WORD)
		{
			expand_word(current);
		}
		else if (current->type == TK_DOUBLE_QUOTED)
		{
		}
		current = current->next;
	}
	return (tokens);
}

/*
***********OLD**********
static void	expand_word(t_token *token)
{
	unsigned int	i;
	char			*temp;
	char			*new_temp;
	bool			dollar;

	dollar = false;
	i = 0;
	while (token->value && token->value[i] != '\0')
	{
		if (token->value[i] == '$')
		{
			if (dollar == false)
				temp = ft_strndup(token->value, i);
			else
			{
				new_temp = ft_strndup(temp, ft_strlen(temp));
				free(temp);
				temp = new_temp;
			}
			temp = ft_strjoin(temp, "EXPAND!");
			dollar = true;
		}	
		i++;
	}
	if (dollar == true)
	{
		free(token->value);
		token->value = temp;
	}
}*/