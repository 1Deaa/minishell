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
	shell_signal_handlers();
	shell_loop(DEBUG);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */