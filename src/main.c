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

extern int g_status;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	shell.argv = argv;
	shell.envp = dup_envp(envp);
	shell.debug = false;
	g_status = 0;
	shell_signal();
	shell_loop(&shell);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */