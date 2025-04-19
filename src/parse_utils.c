/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:24:01 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/19 14:24:04 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	count_word_tokens(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type == TK_WORD)
	{
		i++;
		token = token->next;
	}
	return (i);
}
