/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:27:35 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/17 14:27:37 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(struct s_cmd *cmd)
{
	struct s_execcmd	*exec;
	int					i;
	bool				newline;

	if (cmd->type != EXEC)
		return ;
	i = 1;
	newline = true;
	exec = (struct s_execcmd *)cmd;
	while (exec->argv[i] && strcmp(exec->argv[i], "-n") == 0)
	{
		newline = false;
		i++;
	}
	while (exec->argv[i])
	{
		printf("%s", exec->argv[i]);
		if (exec->argv[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
/*
int	main(void)
{
	struct s_execcmd cmd;
	cmd.type = EXEC;
	char *args[] = {"echo", "Hello", NULL};
	cmd.argv = args;
	echo((struct s_cmd *)&cmd);
	return (0);
}*/