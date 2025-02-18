/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 00:18:14 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/19 00:18:15 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_cmd(struct s_cmd *parse)
{
	struct s_execcmd *ecmd;
	pid_t	pid;
	char		*address;

	if (!parse)
		return ;
	if (parse->type == EXEC)
	{
		ecmd = (struct s_execcmd *)parse;
		if (!ecmd->argv[0])
			return ;
		pid = fork();
		if (pid == -1)
		{
			perror("fork\n");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			address = find_cmd_path(ecmd->argv[0]);
			if (!address)
			{
				printf("Command not found!\n");
				exit(EXIT_FAILURE);
			}
			execve(find_cmd_path(ecmd->argv[0]), ecmd->argv, __environ);
			perror("execve\n");
			exit(EXIT_FAILURE);
		}
		else
			waitpid(pid, NULL, 0);
	}
}
/* ************************************************************************** */
