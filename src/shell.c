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

void	shell_clean(t_shell *shell)
{
	free(shell->command);
	free_tokens(shell->tokens);
	parse_clean(shell->parse);
}

void	shell_loop(t_shell *shell)
{
	shell->parse = NULL;
	while (0x1DEAA)
	{
		shell->command = shell_read(shell, PROMPT);
		shell->tokens = tokenize(shell->command);
		if (!is_correct_syntax(shell->tokens))
		{
			shell_clean(shell);
			continue ;
		}
		shell->tokens = expander(shell->tokens, shell);
		shell->parse = parser(shell->tokens);
		execute(shell, shell->parse);
		shell_debug(shell);
		shell_clean(shell);
	}
}
