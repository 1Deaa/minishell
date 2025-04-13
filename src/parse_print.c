/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 05:14:54 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/27 05:14:55 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_indent(int depth, bool parent_last[])
{
	int	i;

	i = 0;
	while (i < depth - 1)
	{
		if (parent_last[i])
			printf("    ");
		else
			printf("│   ");
		i++;
	}
}

void	print_branch(int depth, bool is_last)
{
	if (depth > 0)
	{
		if (is_last)
			printf("└── ");
		else
			printf("├── ");
	}
}

void	print_exec(t_execmd *ecmd)
{
	int	i;

	printf("EXEC:");
	i = 0;
	while (ecmd->argv[i])
	{
		printf(" %s", ecmd->argv[i]);
		i++;
	}
	printf("\n");
}

void	print_pipe(t_pipecmd *pcmd, int depth, bool parent_last[])
{
	printf("PIPE\n");
	parent_last[depth] = pcmd->right == NULL;
	print_ast(pcmd->left, depth + 1, false, parent_last);
	print_ast(pcmd->right, depth + 1, true, parent_last);
}

void	print_redir(t_redircmd *rcmd, int depth, bool parent_last[])
{
	printf("REDIR: file = %s, fd = %d, flags = %d mode = %d\n",
		rcmd->file, rcmd->fd, rcmd->flags, rcmd->mode);
	parent_last[depth] = true;
	print_ast(rcmd->cmd, depth + 1, true, parent_last);
}
