/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:15:16 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/16 19:15:18 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static struct s_execcmd	*create_execcmd(char **tokens, int *index)
{
	struct	s_execcmd	*cmd;
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

static struct s_cmd	*exec_redir(struct s_cmd *cmd,
	char **tokens, int *index)
{
	struct s_cmd	*parsed_cmd;

	parsed_cmd = cmd;
	while (tokens[*index] && (ft_strcmp(tokens[*index], "<") == 0
			|| ft_strcmp(tokens[*index], ">") == 0))
	{
		parsed_cmd = (struct s_cmd *)create_redircmd(parsed_cmd, tokens, index);
		if (!parsed_cmd)
			return (NULL);
	}
	return (parsed_cmd);
}

struct s_cmd	*parse_exec(char **tokens, int *index)
{
	struct s_execcmd	*cmd;
	struct s_cmd		*parsed_cmd;

	cmd = create_execcmd(tokens, index);
	if (!cmd)
		return (NULL);
	parsed_cmd = (struct s_cmd *)cmd;
	parsed_cmd = exec_redir(parsed_cmd, tokens, index);
	if (!parsed_cmd)
		return (NULL);
	return (parsed_cmd);
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
