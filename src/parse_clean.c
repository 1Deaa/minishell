/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 05:31:18 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/27 05:31:20 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_clean_exec(t_execmd *exec)
{
	int	i;

	i = 0;
	if (exec->argv != NULL)
	{
		while (exec->argv[i] != NULL)
		{
			free(exec->argv[i]);
			i++;
		}
		free(exec->argv);
	}
	free(exec);
}

static void	parse_clean_pipe(t_pipecmd *pipe)
{
	if (pipe->left != NULL)
		parse_clean(pipe->left);
	if (pipe->right != NULL)
		parse_clean(pipe->right);
	free(pipe);
}

static void	parse_clean_redir(t_redircmd *redir)
{
	if (redir->cmd != NULL)
		parse_clean(redir->cmd);
	if (redir->file != NULL)
		free(redir->file);
	free(redir);
}

void	parse_clean(t_cmd *cmd)
{
	t_execmd	*exec;
	t_pipecmd	*pipe;
	t_redircmd	*redir;

	if (cmd == NULL)
		return ;
	if (cmd->type == PS_EXEC)
	{
		exec = (t_execmd *)cmd;
		parse_clean_exec(exec);
	}
	else if (cmd->type == PS_PIPE)
	{
		pipe = (t_pipecmd *)cmd;
		parse_clean_pipe(pipe);
	}
	else if (cmd->type == PS_REDIR)
	{
		redir = (t_redircmd *)cmd;
		parse_clean_redir(redir);
	}
}
