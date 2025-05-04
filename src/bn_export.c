/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halmuhis <halmuhis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:45:02 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/04 12:58:55 by halmuhis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	chek_var(char *str)
{
	int	i;

	i = 0;
	if (!str || ft_isdigit(str[0]))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (str[i] < 33)
			return (0);
		i++;
	}
	return (1);
}

int	export(t_pak *cmd)
{
	int	i;
	char	*var;
	char	*value;

	i = 0;
	var = NULL;
	value = NULL;
	while (cmd->full_cmd && cmd->full_cmd[i])
	{
		if (ft_strchr(cmd->full_cmd[i], '='))
		{
			if (!chek_var(cmd->full_cmd[i]))
			{
				printf("export: `%s': not a valid identifier\n", cmd->full_cmd[i]);
				return (1);
			}
			printf("export: %s\n", cmd->full_cmd[i]);
		}
		i++;
	}
	return (1);
}
