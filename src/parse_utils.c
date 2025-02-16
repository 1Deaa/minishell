/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:15:16 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/16 19:15:18 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_exec_args(char **tokens)
{
	int	count;

	count = 0;
	while (tokens[count] != NULL && ft_strcmp(tokens[count], "|") != 0
		&& ft_strcmp(tokens[count], "<") != 0
		&& ft_strcmp(tokens[count], ">") != 0)
	{
		count++;
	}
	return (count);
}

/* ************************************************************************** */
struct s_execcmd	*parse_exec(char **tokens, int *index)
{
	struct s_execcmd	*cmd;
	int					i;

	i = 0;
	cmd = malloc(sizeof(struct s_execcmd));
	if (!cmd)
		return (NULL);
	cmd->type = EXEC;
	cmd->argv = malloc(sizeof(char *) * (count_exec_args(tokens + *index) + 1));
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	while (tokens[*index] && ft_strcmp(tokens[*index], "|") != 0
		&& ft_strcmp(tokens[*index], "<") != 0
		&& ft_strcmp(tokens[*index], ">") != 0)
	{
		cmd->argv[i++] = tokens[*index];
		(*index)++;
	}
	cmd->argv[i] = NULL;
	return (cmd);
}

/* ************************************************************************** */
struct s_cmd	*parse_pipe(char **tokens, int *index)
{
	struct s_cmd		*cmd;
	struct s_pipecmd	*pcmd;

	cmd = (struct s_cmd *)parse_exec(tokens, index);
	while (tokens[*index] && ft_strcmp(tokens[*index], "|") == 0)
	{
		pcmd = malloc(sizeof(struct s_pipecmd));
		if (!pcmd)
		{
			free(cmd);
			return (NULL);
		}
		pcmd->type = PIPE;
		pcmd->left = cmd;
		(*index)++;
		pcmd->right = parse_redir(tokens, index);
		if (!pcmd->right)
		{
			free(pcmd);
			return (NULL);
		}
		cmd = (struct s_cmd *)pcmd;
	}
	return (cmd);
}

/* ************************************************************************** */
static struct s_redircmd	*create_redircmd(struct s_cmd *cmd,
	char **tokens, int *index)
{
	struct s_redircmd	*rcmd;

	rcmd = malloc(sizeof(struct s_redircmd));
	if (!rcmd)
		return (NULL); 
	if (!tokens[*index + 1])
	{
		free(rcmd);
		return (NULL);
	}
	rcmd->type = REDIR;
	rcmd->cmd = cmd;
	rcmd->file = tokens[*index + 1];
	if (ft_strcmp(tokens[*index], "<") == 0)
		rcmd->mode = 0;
	else
		rcmd->mode = 1;
	rcmd->fd = rcmd->mode;
	*index += 2;
	return (rcmd);
}

struct s_cmd	*parse_redir(char **tokens, int *index)
{
	struct s_cmd	*cmd;

	cmd = parse_pipe(tokens, index);
	while (tokens[*index] && (ft_strcmp(tokens[*index], "<") == 0
			|| ft_strcmp(tokens[*index], ">") == 0))
	{
		cmd = (struct s_cmd *)create_redircmd(cmd, tokens, index);
		if (!cmd)
			return (NULL);
	}
	return (cmd);
}

/* ************************************************************************** */
/*
struct s_cmd	*parse_redir(char **tokens, int *index)
{
	struct s_cmd		*cmd;
	struct s_redircmd	*rcmd;

	cmd = parse_pipe(tokens, index);
	while (tokens[*index] && (ft_strcmp(tokens[*index], "<") == 0
			|| ft_strcmp(tokens[*index], ">") == 0))
	{
		rcmd = malloc(sizeof(struct s_redircmd));
		if (!rcmd)
			free(cmd);
		if (!rcmd)
			return (NULL);
		rcmd->type = REDIR;
		rcmd->cmd = cmd;
		if (!tokens[*index + 1])
			free(rcmd);
		if (!tokens[*index + 1])
			return (NULL);
		rcmd->file = tokens[*index + 1];
		if (ft_strcmp(tokens[*index], "<") == 0)
			rcmd->mode = 0;
		else
			rcmd->mode = 1;
		rcmd->fd = rcmd->mode;
		*index += 2;
		cmd = (struct s_cmd *)rcmd;
	}
	return (cmd);
}
*/
/* ************************************************************************** */