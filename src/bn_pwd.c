/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:08:54 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/13 22:08:54 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(int argc, char **argv, char **envp)
{
	char	*env;

	(void)argv;
	(void)argc;
	env = get_envp(envp, "PWD");
	if (!env)
		return ;
	ft_printf(1, "%s\n", env);
}
