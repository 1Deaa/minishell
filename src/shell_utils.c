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

/*
FREE ENVIRONMENT VARIABLES
FREE READLINE HISTORY
 *
 * add more...
 *
PRINT EXIT
EXIT
*/
static void	shell_exit(t_shell *shell)
{
	free_envp(shell->envp, count_envp(shell->envp));
	rl_clear_history();
	printf("exit\n");
	exit(EXIT_SUCCESS);
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
		if (is_correct_syntax(shell->tokens))
			printf("━━━\nSYNTAX: "GREEN"correct ✔\n"RESET BOLD);
		else
			printf("SYNTAX: "RED"failure!\n"RESET BOLD);
		printf("━━━\nAST:\n");
		print_ast_tree(shell->parse);
		printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"RESET);
	}
}

char	*shell_read(t_shell *shell, char *prompt)
{
	char	*input;

	input = readline(prompt);
	if (input == NULL)
	{
		shell_exit(shell);
	}
	if (ft_strlen(input) > 0)
		add_history(input);
	return (input);
}
