/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:42:52 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/18 15:53:54 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_shlvl(t_shell *shell)
{
	char	*shlvl;

	shell->shlvl = ft_atoi(env_grab(shell->envp, "SHLVL")) + 1;
	shlvl = ft_itoa(shell->shlvl);
	env_update(shell->envp, "SHLVL", shlvl);
	free(shlvl);
}

void	shell_init(t_shell *shell)
{
	shell->debug = false;
	if (shell->argv[1] && !ft_strcmp(shell->argv[1], "debug"))
		shell->debug = true;
	shell->exit = false;
	shell->e_status = 0;
	shell->last_pid = 0;
	update_shlvl(shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	shell.argv = argv;
	shell.envp = env_dup(envp);
	shell_init(&shell);
	shell_signal();
	shell_loop(&shell);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */