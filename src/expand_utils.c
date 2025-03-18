/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:34:28 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/18 20:34:29 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_expandable(char c)
{
	if (ft_isalpha(c) || c == '_' || c == '?')
		return (true);
	return (false);
}

char	*expand_word_util(t_token *token, t_shell *shell, int *i, bool *dollar)
{
	char	*str;

	str = "";
	if (token->value[*i] == '$' && token->value[*i + 1] != '\0'
		&& is_expandable(token->value[*i + 1]))
	{
		if (!(*dollar))
			str = ft_strndup(token->value, *i);
		str = ft_strjoin(str, expand(exname(*token, (*i) + 1), shell));
		*dollar = true;
	}
	(*i)++;
	return (str);
}
