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

int count_exec_args(t_token *token)
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

static void print_ast(t_cmd *cmd, int depth, bool is_last, bool parent_last[])
{
    if (!cmd)
        return;
    for (int i = 0; i < depth - 1; i++)
        printf("%s   ", parent_last[i] ? " " : "│");
    if (depth > 0)
        printf("%s── ", is_last ? "└" : "├");
    if (cmd->type == PS_EXEC)
    {
        t_execmd *ecmd = (t_execmd *)cmd;
        printf("EXEC:");
        for (int i = 0; ecmd->argv[i]; i++)
            printf(" %s", ecmd->argv[i]);
        printf("\n");
    }
    else if (cmd->type == PS_PIPE)
    {
        t_pipecmd *pcmd = (t_pipecmd *)cmd;
        printf("PIPE\n");

        parent_last[depth] = !pcmd->right;
        print_ast(pcmd->left, depth + 1, false, parent_last);
        print_ast(pcmd->right, depth + 1, true, parent_last);
    }
    else if (cmd->type == PS_REDIR)
    {
        t_redircmd *rcmd = (t_redircmd *)cmd;
        printf("REDIR: file = %s, fd = %d, mode = %d\n", rcmd->file, rcmd->fd, rcmd->mode);

        parent_last[depth] = true;
        print_ast(rcmd->cmd, depth + 1, true, parent_last);
    }
}

void print_ast_tree(t_cmd *ast)
{
    bool parent_last[100] = {false};
    print_ast(ast, 0, true, parent_last);
}
