/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:17:40 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/14 00:09:45 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shell_debug(t_shell *shell)
{
	if (shell->command)
		printf("INPUT: %s\n~·~\n", shell->command);
	if (shell->tokens)
		print_tokens(shell->tokens);
	if (is_correct_syntax(shell->tokens))
		printf("~·~\nCORRECT SYNTAX!\n");
	else
		printf("WRONG SYNTAX!\n");
}

void	shell_loop(int mode)
{
	t_shell	shell;

	shell.prompt = PROMPT;
	shell.parse = NULL;
	while (0x1DEAA)
	{
		shell.command = readline(shell.prompt);
		if (!shell.command)
			break ;
		shell.tokens = tokenize(shell.command);
		shell.tokens = expander(shell.tokens);
		if (DEBUG == mode)
			shell_debug(&shell);
		add_history(shell.command);
		free(shell.command);
		free_tokens(shell.tokens);
	}
	rl_clear_history();
}
