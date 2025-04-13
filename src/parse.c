/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:20:45 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/22 11:20:46 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_exec(t_token **token)
{
	t_execmd	*ecmd;
	int			argc;

	argc = 0;
	ecmd = (t_execmd *)malloc(sizeof(t_execmd));
	ecmd->type = PS_EXEC;
	ecmd->argv = (char **)malloc(sizeof(char *) *(count_exec_args(*token) + 1));
	while (*token && is_exec(*token))
	{
		ecmd->argv[argc++] = (char *)ft_strdup((*token)->value); //TODO
		*token = (*token)->next;
	}
	ecmd->argv[argc] = NULL;
	return ((t_cmd *)ecmd);
}

t_cmd	*parse_simple_command(t_token **token)
{
	t_cmd		*cmd;
	t_redircmd	*rcmd;

	cmd = parse_exec(token);
	while (*token && is_redirection(*token))
	{
		if (!*token || !((*token)->next->next
				&& (*token)->next->next->type == TK_PIPE))
			break ;
		rcmd = (t_redircmd *)malloc(sizeof(t_redircmd)); //TODO
		rcmd->type = PS_REDIR;
		rcmd->cmd = cmd;
		*token = (*token)->next;
		rcmd->file = (char *)ft_strdup((*token)->value); //TODO
		*token = (*token)->next;
		rcmd->mode = O_WRONLY | O_CREAT | O_TRUNC; //TODO
		rcmd->fd = 1; //TODO
		cmd = (t_cmd *)rcmd;
	}
	return (cmd);
}

t_cmd	*parse_pipeline(t_token **token)
{
	t_cmd		*cmd;
	t_pipecmd	*pcmd;

	cmd = parse_simple_command(token);
	while (*token && (*token)->type == TK_PIPE)
	{
		*token = (*token)->next;
		pcmd = (t_pipecmd *)malloc(sizeof(t_pipecmd)); //TODO
		pcmd->type = PS_PIPE;
		pcmd->left = cmd;
		pcmd->right = parse_simple_command(token);
		cmd = (t_cmd *)pcmd;
	}
	return (cmd);
}

t_cmd	*parse_full_command(t_token **token)
{
	t_cmd		*cmd;
	t_redircmd	*rcmd;

	cmd = parse_pipeline(token);
	while (*token && is_redirection(*token))
	{
		rcmd = (t_redircmd *)malloc(sizeof(t_redircmd)); //TODO
		rcmd->type = PS_REDIR;
		rcmd->cmd = cmd;
		configure_redir(rcmd, (*token)->value);
		*token = (*token)->next;
		rcmd->file = (char *)ft_strdup((*token)->value); //TODO
		*token = (*token)->next;
		cmd = (t_cmd *)rcmd;
	}
	return (cmd);
}

t_cmd	*parser(t_token *tokens)
{
	t_token	*current;
	t_cmd	*ast;

	current = tokens;
	ast = parse_full_command(&current);
	return (ast);
}
