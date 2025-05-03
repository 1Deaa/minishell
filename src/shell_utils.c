/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:57:57 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/20 15:57:57 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

/*
FREE ENVIRONMENT VARIABLES
FREE READLINE HISTORY
 *
 * add more...
 *
PRINT EXIT
EXIT
 */
void	shell_exit(t_shell *shell)
{
	free_envp(shell->envp, count_envp(shell->envp));
	rl_clear_history();
	printf("exit\n");
	exit(shell->e_status);
}

void	shell_debug(t_shell *shell)
{
	if (shell->command[0] != '\0' && shell->debug == true)
	{
		printf(BOLD"┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("┃"YELLOW"         DEBUG-SCREEN        "RESET BOLD"┃\n");
		printf("┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		if (shell->command)
			printf("INPUT: %s\n━━━\n", shell->command);
		if (shell->tokens)
			print_tokens(shell->tokens);
		if (is_correct_syntax(shell, shell->tokens))
			printf("━━━\nSYNTAX: "GREEN"correct ✔\n"RESET BOLD);
		else
			printf("SYNTAX: "RED"failure!\n"RESET BOLD);
		if (shell->e_status == 0)
			printf("━━━\nEXIT STATUS: "GREEN"%d ✔\n"RESET, shell->e_status);
		else
			printf("━━━\nEXIT STATUS: "RED"%d\n"RESET, shell->e_status);
		print_paks(shell->cmds);
	}
}

char	*shell_read(t_shell *shell)
{
	char	*input;

	shell_signal();
	if (shell->e_status == 0)
		input = readline(WPROMPT);
	else
		input = readline(XPROMPT);
	if (g_signal == SIGINT)
		shell->e_status = 130;
	if (input == NULL)
		shell_exit(shell);
	if (ft_strlen(input) > 0)
		add_history(input);
	return (input);
}
