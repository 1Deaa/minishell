/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:42:52 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/13 18:42:53 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_input	shell;

	setup_signal_handlers();
	shell.prompt = create_prompt();
	while (true)
	{
		shell.command = readline(shell.prompt);
		if (!shell.command)
		{
			free(shell.prompt);
			break ;
		}
		free(shell.command);
	}
	return (EXIT_SUCCESS);
}
