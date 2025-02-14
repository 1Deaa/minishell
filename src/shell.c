/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:17:40 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/14 14:17:40 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(void)
{
	t_input	shell;

	shell.prompt = create_prompt();
	while (true)
	{
		shell.command = readline(shell.prompt);
		if (!shell.command)
		{
			free(shell.prompt);
			break ;
		}
		add_history(shell.command);
		free(shell.command);
	}
	rl_clear_history();
}
