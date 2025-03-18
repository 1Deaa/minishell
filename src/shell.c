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
	if (shell->command[0] != '\0' && shell->debug == true)
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
}

static char	*shell_read(char *prompt)
{
	char	*input;

	input = readline(prompt);
	if (input == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	if (ft_strlen(input) > 0)
		add_history(input);
	return (input);
}

void	shell_loop(t_shell *shell)
{
	shell->parse = NULL;
	while (0x1DEAA)
	{
		shell->command = shell_read(PROMPT);
		shell->tokens = tokenize(shell->command);
		shell->tokens = expander(shell->tokens, shell);
		if (!is_correct_syntax(shell->tokens))
			continue ;
		shell_debug(shell);
		free(shell->command);
		free_tokens(shell->tokens);
	}
	rl_clear_history();
}
