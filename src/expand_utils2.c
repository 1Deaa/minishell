/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:58:10 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/14 13:58:11 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_heredoc_quoted(t_token *token)
{
	int		i;
	char	*exp;

	i = 0;
	i++;
	while (token->value[i] && token->value[i] != '"')
		i++;
	exp = ft_strndup((token->value) + 1, i - 1);
	free(token->value);
	token->value = exp;
}
