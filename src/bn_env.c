/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:23:05 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/13 22:23:06 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(char **envp)
{
	print_envp("", envp);
	return (0);
}

char	*get_home(t_shell *shell)
{
	char	*home;

	home = get_envp(shell->envp, "HOME");
	if (!home)
	{
		ft_printf(2, "%s: %s: HOME not set\n", C_NAME, "cd");
		return (NULL);
	}
	return (home);
}
