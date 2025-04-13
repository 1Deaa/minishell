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

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	shell.argv = argv;
	shell.envp = dup_envp(envp);
	shell.debug = true;
	shell_signal();
	shell_loop(&shell);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */