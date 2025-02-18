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

static void	shell_debug(t_shell *shell)
{
	if (shell->command)
		printf("INPUT: %s\n", shell->command);
	if (shell->parse)
		print_cmd(shell->parse, 0);
}

void	shell_loop(int mode)
{
	t_shell	shell;

	shell.prompt = create_prompt();
	shell.parse = NULL;
	while (true)
	{
		shell.command = readline(shell.prompt);
		if (!shell.command)
		{
			free(shell.prompt);
			break ;
		}
		shell.tokens = tokenize(shell.command);
		shell.parse = parser(shell.tokens);
		run_cmd(shell.parse);
		if (DEBUG == mode)
		{
			shell_debug(&shell);
		}
		add_history(shell.command);
		free(shell.command);
	}
	rl_clear_history();
}
