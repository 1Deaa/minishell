/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:17:40 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/09 07:30:09 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shell_debug(t_shell *shell)
{
	if (shell->command)
		printf("INPUT: %s\n", shell->command);
	if (shell->tokens)
		print_tokens(shell->tokens);
}

void	shell_loop(int mode)
{
	t_shell	shell;

	(void)mode;
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
		if (DEBUG == mode)
		{
			shell_debug(&shell);
		}
		add_history(shell.command);
		free(shell.command);
		free_tokens(shell.tokens);
	}
	rl_clear_history();
}
