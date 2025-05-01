/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:51:11 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/16 14:51:12 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*shell_error(t_shell *shell, int err_type, char *param, int err)
{
	shell->e_status = err;
	if (err_type == QUOTE)
		ft_printf(2, "%s: error while looking for matching quote!", C_NAME);
	else if (err_type == NDIR)
		ft_printf(2, "%s: No such file or directory: ", C_NAME);
	else if (err_type == NPERM)
		ft_printf(2, "%s: permission denied: ", C_NAME);
	else if (err_type == NCMD)
		ft_printf(2, "%s: command not found: ", C_NAME);
	else if (err_type == DUPERR)
		ft_printf(2, "%s: dup2 failed\n", C_NAME);
	else if (err_type == FORKERR)
		ft_printf(2, "%s: fork failed\n", C_NAME);
	else if (err_type == PIPERR)
		ft_printf(2, "%s: error creating pipe\n", C_NAME);
	else if (err_type == NEARERR)
		ft_printf(2, "%s: syntax error near unexpected token: ", C_NAME);
	else if (err_type == MEM)
		ft_printf(2, "%s: no memory left on device\n", C_NAME);
	else if (err_type == IS_DIR)
		ft_printf(2, "%s: Is a directory: ", C_NAME);
	else if (err_type == NOT_DIR)
		ft_printf(2, "%s: Not a directory: ", C_NAME);
	ft_printf(2, "%s\n", param);
	return (NULL);
}
