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

char	*special_expand(char *str, t_shell *shell)
{
	char	*ret;

	ret = NULL;
	if (!ft_strcmp(str, "?"))
		ret = ft_itoa(shell->e_status);
	else if (!ft_strcmp(str, "0"))
		ret = ft_strdup(shell->argv[0]);
	else if (!ft_strcmp(str, "1"))
		ret = ft_strdup(shell->argv[1]);
	return (ret);
}

char	*exname(char *token, int *index)
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

bool	is_expandable(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (true);
	return (false);
}

bool	check_heredoc_filename(t_token *token)
{
	if (token && token->prev)
	{
		if (token->prev->type == TK_HEREDOC)
			return (true);
	}
	return (false);
}

void	expand_heredoc(t_token *current)
{
	if (current->type == TK_WORD)
		return ;
	else if (current->type == TK_SINGLE_QUOTED)
	{
		expand_single_quoted(current);
	}
	else if (current->type == TK_DOUBLE_QUOTED)
	{
		expand_heredoc_quoted(current);
	}
}
