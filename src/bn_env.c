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

int	env(char **envp, t_pak *pak)
{
	close_pak_infile(pak);
	env_print("", envp);
	return (0);
}

int	chdir_home(t_shell *shell)
{
	char	*home;
	int		ret;

	home = env_grab(shell->envp, "HOME");
	if (!home)
	{
		ft_printf(2, "%s: %s: HOME not set\n", C_NAME, "cd");
		return (1);
	}
	ret = chdir(home);
	return (ret);
}
