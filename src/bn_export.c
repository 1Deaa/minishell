/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halmuhis <halmuhis@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:45:02 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/06 15:43:47 by halmuhis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	add_env_var(char *new_var, int env_index, char ***env)
{
	int		i;
	char	**new_env;
	int		count;

	if (env_index >= 0)
	{
		free((*env)[env_index]);
		(*env)[env_index] = ft_strdup(new_var);
		return (0);
	}
	count = count_envp(*env);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (1);
	i = -1;
	while (++i < count)
		new_env[i] = (*env)[i];
	new_env[i] = ft_strdup(new_var);
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}

static char	*get_var_name(char *str)
{
	char	*equal_pos;
	int		len;
	char	*name;

	equal_pos = ft_strchr(str, '=');
	if (!equal_pos)
		len = ft_strlen(str);
	else
		len = equal_pos - str;
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
	{
		ft_printf(2, "faild to alloc");
		exit(1);
	}
	ft_strncpy(name, str, len);
	name[len] = '\0';
	return (name);
}

static int	find_env_var(char *cmd, char **envp)
{
	int			i;
	char		*var_name;

	i = 0;
	var_name = get_var_name(cmd);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, ft_strlen(var_name)) == 0
			&& envp[i][ft_strlen(var_name)] == '=')
		{
			free(var_name);
			return (i);
		}
		i++;
	}
	free(var_name);
	return (-1);
}

static int	check_var(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]) || str[0] == '=')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (str[i++] < 33)
			return (0);
	}
	return (1);
}

int	export(t_pak *cmd, char ***envp)
{
	int	i;

	i = 1;
	if (!cmd->full_cmd[1])
	{
		print_envp("", *envp);
		return (1);
	}
	while (cmd->full_cmd[i])
	{
		if (check_var(cmd->full_cmd[i]))
		{
			if (ft_strchr(cmd->full_cmd[i], '='))
				add_env_var(cmd->full_cmd[i], find_env_var(cmd->full_cmd[i],
						*envp), envp);
		}
		else
			ft_printf(2, "export: `%s': not a valid identifier\n",
				cmd->full_cmd[i]);
		i++;
	}
	return (1);
}
