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
