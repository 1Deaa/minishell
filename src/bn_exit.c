/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:23:15 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/30 13:23:15 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	many_args(t_shell *shell)
{
	shell->exit = false;
	ft_printf(2, "%s: %s: too many arguments\n", C_NAME, "exit");
	return (1);
}

static int	check_num(const char *str, long *nbr)
{
	int		sign;

	sign = 1;
	*nbr = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -sign;
	if (*str == '-' || *str == '+')
		str++;
	if (!ft_isdigit(*str))
		return (-1);
	while (ft_isdigit(*str))
	{
		*nbr = 10 * *nbr + (*str - '0');
		str++;
	}
	if (*str && !ft_isspace(*str))
		return (-1);
	*nbr *= sign;
	return (0);
}

int	bn_exit(t_shell *shell, t_pak *pak)
{
	long	num[2];

	if (!pak->next)
	{
		if (!pak->prev)
			shell->exit = true;
	}
	if (!pak->full_cmd || !pak->full_cmd[1])
		return (shell->e_status);
	if (pak->full_cmd[2])
		return (many_args(shell));
	num[1] = check_num(pak->full_cmd[1], &num[0]);
	if (-1 == num[1])
	{
		ft_printf(2, "%s: %s: %s: numeric argument required\n", C_NAME,
			"exit", pak->full_cmd[1]);
		return (2);
	}
	num[0] %= 256 + 256 * (num[0] < 0);
	return (num[0]);
}
