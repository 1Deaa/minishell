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

static char	*expand(char *name, t_shell *shell)
{
	char	*ret;

	(void)shell;
	ret = NULL;
	if (!ft_strcmp(name, "0") || !ft_strcmp(name, "1") || !ft_strcmp(name, "?"))
	{
		ret = special_expand(name, shell);
		free(name);
		if (!ret)
			return (ft_strdup(""));
		return (ret);
	}
	if (!ft_strcmp(name, ""))
	{
		free(name);
		return (ft_strdup("$"));
	}
	ret = ft_strdup(getenv(name));
	if (!ret)
	{
		free(name);
		return (ft_strdup(""));
	}
	free(name);
	return (ret);
}

static char	*exname(char *token, int *index)
{
	char	*ret;
	int		i;

	ret = NULL;
	i = (*index) + 1;
	while (is_expandable(token[++(*index)]))
	{
		if (token[*index] == '?' || token[*index] == '0'
			|| token[*index] == '1')
		{
			(*index)++;
			break ;
		}
	}
	ret = ft_strndup(token + i, (*index) - i);
	if (!ret)
		return (ft_strdup(""));
	return (ret);
}

static void	expand_quoted(t_token *token, t_shell *shell)
{
	int		i;
	char	*str;
	char	*exp;

	i = 0;
	str = NULL;
	exp = NULL;
	while (token->value[i])
	{
		while (token->value[i] == '$' && token->value[i + 2] != '\0')
		{
			exp = expand(exname(token->value, &i), shell);
			str = ft_strjoin(str, exp);
			free(exp);
		}
		str = ft_charjoin(str, token->value[i]);
		i++;
	}
	free(token->value);
	token->value = str;
}

static void	expand_word(t_token *token, t_shell *shell)
{
	int		i;
	char	*str;
	char	*exp;

	i = 0;
	str = NULL;
	exp = NULL;
	while (token->value[i])
	{
		while (token->value[i] == '$' && token->value[i + 1] != '\0')
		{
			exp = expand(exname(token->value, &i), shell);
			str = ft_strjoin(str, exp);
			free(exp);
		}
		str = ft_charjoin(str, token->value[i]);
		i++;
	}
	free(token->value);
	token->value = str;
}

t_token	*expander(t_token *tokens, t_shell *shell)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == TK_WORD)
		{
			expand_word(current, shell);
		}
		else if (current->type == TK_DOUBLE_QUOTED)
		{
			expand_quoted(current, shell);
		}
		current = current->next;
	}
	return (tokens);
}
