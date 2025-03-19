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

char	*expand(char *var_name, t_shell *shell)
{
	char	*ret;

	ret = ft_strdup(getenv(var_name));
	if (ft_strcmp(var_name, "1") == 0)
		ret = ft_strdup(shell->argv[1]);
	if (ft_strcmp(var_name, "0") == 0)
		ret = ft_strdup(shell->argv[0]);
	if (ft_strcmp(var_name, "?") == 0)
		ret = NULL;
	if (!ret)
		ret = ft_strdup("");
	free(var_name);
	return (ret);
}

char	*exname(t_token token, int index)
{
	char	*var_name;
	int		i;

	i = index;
	while (token.value[i] && is_expandable(token.value[i])
		&& token.value[i] != '\0')
		i++;
	var_name = ft_strndup((token.value) + index, i - index);
	if (!var_name)
		var_name = ft_strdup("");
	return (var_name);
}

void	expand_word(t_token *token, t_shell *shell)
{
	int		i;
	char	*temp;
	bool	dollar;

	dollar = false;
	i = 0;
	temp = NULL;
	while (token->value && token->value[i] != '\0')
	{
		if (token->value[i] == '$' && token->value[i + 1] != '\0'
			&& is_expandable(token->value[i + 1]))
		{
			if (!dollar)
				temp = ft_strndup(token->value, i);
			temp = ft_strjoin(temp, expand(exname(*token, i + 1), shell));
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

void	expand_quoted(t_token *token, t_shell *shell)
{
	int		i;
	char	*ret;

	ret = NULL;
	i = 0;
	while (token->value && token->value[i] != '\0')
	{
		if (token->value[i] == '$' && is_expandable(token->value[i + 1])
			&& token->value[i + 2] != '\0')
		{
			i++;
			ret = ft_strjoin(ret, expand(exname(*token, i), shell));
			while (token->value[i] && is_expandable(token->value[i]))
				i++;
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
