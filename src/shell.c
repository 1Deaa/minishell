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

extern int	g_status;

void	shell_clean(t_shell *shell)
{
	free(shell->command);
	free_paks(shell, shell->cmds);
}

void	shell_loop(t_shell *shell)
{
	shell->cmds = NULL;
	while (0x1DEAA)
	{
		shell->command = shell_read(shell);
		shell->tokens = tokenizer(shell->command);
		if (!is_correct_syntax(shell->tokens))
		{
			free(shell->command);
			free_tokens(shell->tokens);
			continue ;
		}
		shell->tokens = expander(shell->tokens, shell);
		shell->cmds = parser(shell, shell->tokens);
		g_status = executer(shell, shell->cmds);
		if (shell->last_ncmd)
			g_status = shell->l_status;
		if (g_status > 255)
			g_status = g_status / 255;
		shell_debug(shell);
		shell_clean(shell);
		if (shell->exit == true)
			shell_exit(shell);
	}
}
