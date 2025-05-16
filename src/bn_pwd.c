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

int	pwd(t_pak *cmd)
{
	char	*pwd;

	close_pak_infile(cmd);
	pwd = getcwd(NULL, 0);
	ft_printf(1, "%s\n", pwd);
	free(pwd);
	return (0);
}
