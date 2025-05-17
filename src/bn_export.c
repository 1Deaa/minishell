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

static bool	is_valid_identifier(char *value)
{
	int	i;

	if (!value || !value[0])
	{
		ft_printf(2, "%s: %s: `%s': not a valid identifier\n",
			C_NAME, "export", value);
		return (false);
	}
	if (!ft_isalpha(value[0]) && value[0] != '_')
	{
		ft_printf(2, "%s: %s: `%s': not a valid identifier\n",
			C_NAME, "export", value);
		return (false);
	}
	i = 0;
	while (value[++i])
	{
		if (!ft_isalnum(value[i]) && !ft_strchr("_= ", value[i]))
		{
			ft_printf(2, "%s: %s: `%s': not a valid identifier\n",
				C_NAME, "export", value);
			return (false);
		}
	}
	return (true);
}

static bool	print_export(t_shell *shell, t_pak *cmd)
{
	if (cmd && cmd->full_cmd && !cmd->full_cmd[1])
	{
		env_print_export("declare -x", shell->envp);
		return (true);
	}
	return (false);
}

static void	add_value(t_shell *shell, char *val)
{
	char	*name;
	char	*value;
	char	*entry;

	name = env_entry_name(val);
	value = env_entry_value(val);
	if (!ft_strchr(val, '=') && !env_grab(shell->envp, name))
	{
		shell->envp = env_app(shell->envp, val);
		free(name);
		free(value);
		return ;
	}
	if (!env_grabentry(shell->envp, name))
	{
		entry = env_newentry(name, value);
		if (!entry)
			return ;
		shell->envp = env_app(shell->envp, entry);
	}
	env_update(shell->envp, name, value);
	free(name);
	free(value);
	free(val);
}

int	export(t_shell *shell, t_pak *cmd)
{
	int		i;
	char	*value;

	close_pak_infile(cmd);
	if (print_export(shell, cmd))
		return (0);
	i = 0;
	while (cmd && cmd->full_cmd && cmd->full_cmd[++i])
	{
		value = ft_strdup(cmd->full_cmd[i]);
		if (!value || !is_valid_identifier(value))
		{
			shell->e_status = 1;
			continue ;
		}
		add_value(shell, value);
	}
	return (shell->e_status);
}

/*static	int	add_env_var(char *new_var, int env_index, char ***env)
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
		ft_printf(2, "failed to alloc");
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

int	export(t_pak *cmd, char ***envp, bool flag)
{
	int	i;

	i = 1;
	if (flag)
		close_pak_infile(cmd);
	if (!cmd->full_cmd[1])
	{
		env_print_export("declare -x", *envp);
		return (0);
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
}*/
