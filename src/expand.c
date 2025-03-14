/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:36:47 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/14 15:23:52 by drahwanj         ###   ########.fr       */
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
		if (token->value[i] == '$' && token->value[i + 1] != '\0')
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

static void	expand_quoted(t_token *token)
{
	unsigned int	i;
	char			*ret;

	ret = NULL;
	i = 0;
	while (token->value && token->value[i] != '\0')
	{
		if (token->value[i] == '$' && token->value[i + 2] != '\0')
		{
			i++;
			while (token->value[i]
				&& (ft_isalpha(token->value[i]) || token->value[i] == '_'))
			{
				i++;
			}
			ret = ft_strjoin(ret, "EXPAND!");
		}
		else
		{
			ret = ft_charjoin(ret, token->value[i]);
			i++;
		}
	}
	free(token->value);
	token->value = ret;
}
/* ************************************************************************** */

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
			expand_quoted(current);
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