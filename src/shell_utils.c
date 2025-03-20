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

void	shell_debug(t_shell *shell)
{
	if (shell->command[0] != '\0' && shell->debug == true)
	{
		printf("┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		printf("┃         DEBUG-SCREEN        ┃\n");
		printf("┃━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┃\n");
		if (shell->command)
			printf("INPUT: %s\n━━━\n", shell->command);
		if (shell->tokens)
			print_tokens(shell->tokens);
		if (is_correct_syntax(shell->tokens))
			printf("━━━\nSYNTAX: correct!\n");
		else
			printf("SYNTAX: failure!\n");
		printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	}
}

char	*shell_read(char *prompt)
{
	char	*input;

	input = readline(prompt);
	if (input == NULL)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (ft_strlen(input) > 0)
		add_history(input);
	return (input);
}
