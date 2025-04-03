/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:00:40 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/22 22:00:41 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_exec(t_token *token)
{
	if (token->type == TK_DOUBLE_QUOTED
		|| token->type == TK_WORD
		|| token->type == TK_SINGLE_QUOTED)
		return (true);
	return (false);
}

int	count_exec_args(t_token *token)
{
	t_token	*curr;
	int		count;

	count = 0;
	curr = token;
	while (curr && is_exec(token))
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

void	print_ast(t_cmd *cmd, int depth, bool is_last, bool parent_last[])
{
	if (!cmd)
		return ;
	print_indent(depth, parent_last);
	print_branch(depth, is_last);
	if (cmd->type == PS_EXEC)
		print_exec((t_execmd *)cmd);
	else if (cmd->type == PS_PIPE)
		print_pipe((t_pipecmd *)cmd, depth, parent_last);
	else if (cmd->type == PS_REDIR)
		print_redir((t_redircmd *)cmd, depth, parent_last);
}

void	print_ast_tree(t_cmd *ast)
{
	bool	parent_last[100];

	ft_memzero(parent_last, sizeof(parent_last));
	print_ast(ast, 0, true, parent_last);
}
