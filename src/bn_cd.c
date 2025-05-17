/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halmuhis <halmuhis@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:29:28 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/12 13:32:15 by halmuhis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	handle_cd_errors(t_pak *cmd)
{
	int	i;

	i = 0;
	while (cmd->full_cmd && cmd->full_cmd[i])
		i++;
	if (i > 2)
	{
		ft_printf(2, "%s: cd: too many arguments\n", C_NAME);
		return (true);
	}
	return (false);
}

static char	*get_cwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_printf(2, "%s: cd: error retrieving current directory\n");
		return (NULL);
	}
	return (cwd);
}

int	change_dir(t_shell *shell, t_pak *cmd)
{
	char	*home;
	char	*pwd;

	if (!cmd->full_cmd[1])
	{
		home = env_grab(shell->envp, "HOME");
		if (!home)
		{
			ft_printf(2, "%s: cd: HOME not set\n", C_NAME);
			return (1);
		}
		return (chdir(home));
	}
	else
	{
		pwd = cmd->full_cmd[1];
		if (chdir(pwd))
		{
			ft_printf(2, "cd: no such file or directory: %s\n", pwd);
			return (1);
		}
		return (0);
	}
}

int	bn_cd(t_shell *shell, t_pak *cmd)
{
	char	*old_pwd;
	char	*pwd;

	close_pak_infile(cmd);
	if (handle_cd_errors(cmd))
		return (1);
	old_pwd = get_cwd();
	if (!old_pwd)
		return (1);
	if (change_dir(shell, cmd))
	{
		free(old_pwd);
		return (1);
	}
	pwd = get_cwd();
	env_update(shell->envp, "OLDPWD", old_pwd);
	if (!cmd->full_cmd[1])
		env_update(shell->envp, "PWD", env_grab(shell->envp, "HOME"));
	else
		env_update(shell->envp, "PWD", pwd);
	free(pwd);
	free(old_pwd);
	return (0);
}

/*static int	handle_cd_errors(t_pak *cmd)
{
	int	i;

	i = 0;
	while (cmd->full_cmd && cmd->full_cmd[i])
		i++;
	if (i < 1)
	{
		ft_printf(2, "%s: cd: path required\n", C_NAME);
		return (1);
	}
	if (i > 2)
	{
		ft_printf(2, "%s: cd: too many arguments\n", C_NAME);
		return (1);
	}
	return (0);
}

static char	*get_curr_dir(void)
{
	char	*cwd;
	char	*error;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		error = "cd: error retrieving current directory";
		perror(error);
		return (NULL);
	}
	return (cwd);
}

static char	**prepare_export_args(char *curr, char *oldpwd)
{
	char	**cmd;
	char	*pwd_str;
	char	*oldpwd_str;

	if (!curr || !oldpwd)
		return (NULL);
	cmd = malloc(sizeof(char *) * 4);
	if (!cmd)
		return (NULL);
	pwd_str = ft_strjoin(ft_strdup("PWD="), curr);
	oldpwd_str = ft_strjoin(ft_strdup("OLDPWD="), oldpwd);
	if (!pwd_str || !oldpwd_str)
	{
		free(pwd_str);
		free(oldpwd_str);
		free(cmd);
		return (NULL);
	}
	cmd[0] = "export";
	cmd[1] = pwd_str;
	cmd[2] = oldpwd_str;
	cmd[3] = NULL;
	return (cmd);
}

static int	update_pwd_vars(t_shell *shell, char *oldpwd)
{
	t_pak	tmp_cmd;
	char	*curr;
	char	**cmd;

	curr = get_curr_dir();
	if (!curr)
		return (1);
	cmd = prepare_export_args(curr, oldpwd);
	if (!cmd)
	{
		free(curr);
		free(oldpwd);
		return (1);
	}
	tmp_cmd.full_cmd = cmd;
	export(&tmp_cmd, &shell->envp, false);
	free(cmd[1]);
	free(cmd[2]);
	free(cmd);
	free(curr);
	free(oldpwd);
	return (0);
}

int	cd(t_shell *shell, t_pak *cmd)
{
	char	*oldpwd;
	int		ret;

	ret = 0;
	close_pak_infile(cmd);
	if (handle_cd_errors(cmd))
		return (1);
	oldpwd = get_curr_dir();
	if (!oldpwd)
		return (1);
	if (!cmd->full_cmd[1])
		ret = chdir_home(shell);
	else
		ret = chdir(cmd->full_cmd[1]);
	if (ret == -1)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	return (update_pwd_vars(shell, oldpwd));
}*/
