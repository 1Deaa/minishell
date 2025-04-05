/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:20:04 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/19 23:20:05 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirection(t_token *node)
{
	if (node->type == TK_APPEND || node->type == TK_HEREDOC
		|| node->type == TK_REDIR_IN || node->type == TK_REDIR_OUT)
		return (true);
	return (false);
}

bool	is_special(t_token *node)
{
	if (node->type == TK_PIPE || is_redirection(node))
		return (true);
	else
		return (false);
}
