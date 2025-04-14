/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:45:02 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/13 22:45:03 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_shell *shell, char **argv, char **envp)
{
	int		size;
	char	**exp;
	int		i;

	i = -1;
	size = count_envp(envp);
	exp = (char **)malloc(sizeof(char *) * (size + 2));
	if (!envp)
		return ;
	if (!argv[1])
	{
		print_envp("declare -x", envp);
		return ;
	}
	while (++i < size)
	{
		exp[i] = ft_strdup(envp[i]);
		if (!exp[i])
		{
			free_envp(exp, i);
			return ;
		}
	}
	exp[size] = ft_strdup(argv[1]);
	exp[size + 1] = NULL;
	free_envp(shell->envp, count_envp(envp));
	shell->envp = dup_envp(exp);
	free_envp(exp, count_envp(exp));
}
