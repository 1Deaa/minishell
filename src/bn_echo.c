/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:27:35 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/17 14:27:37 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_pak *cmd)
{
	char	**argv;
	int		i;

	argv = cmd->full_cmd;
	i = 1;
	while (argv && argv[i])
	{
		ft_printf(1, "%s\n", argv[i]);
		i++;
	}
	return (0);
}
