/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 00:36:28 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/17 00:36:30 by drahwanj         ###   ########.fr       */
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

struct s_redircmd	*create_redircmd(struct s_cmd *cmd,
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
/* ************************************************************************** */

static void	print_exec(struct s_cmd *cmd)
{
	struct s_execcmd	*ecmd;
	int					i;

	i = -1;
	ecmd = (struct s_execcmd *)cmd;
	printf("EXEC: ");
	while (ecmd->argv[++i])
		printf("%s ", ecmd->argv[i]);
	printf("\n");
}
/* ************************************************************************** */

void	print_cmd(struct s_cmd *cmd, int indent)
{
	struct s_pipecmd	*pcmd;
	struct s_redircmd	*rcmd;
	int					i;

	i = -1;
	if (!cmd)
		return ;
	while (++i < indent)
		printf("  ");
	if (EXEC == cmd->type)
		print_exec(cmd);
	else if (PIPE == cmd->type)
	{
		pcmd = (struct s_pipecmd *)cmd;
		printf("PIPE:\n");
		print_cmd(pcmd->left, indent + 1);
		print_cmd(pcmd->right, indent + 1);
	}
	else if (REDIR == cmd->type)
	{
		rcmd = (struct s_redircmd *)cmd;
		printf("REDIR: %s (mode=%d, fd=%d)\n",
			rcmd->file, rcmd->mode, rcmd->fd);
		print_cmd(rcmd->cmd, indent + 1);
	}
}
/* ************************************************************************** */
