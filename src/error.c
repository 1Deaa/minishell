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

extern int	g_status;

void	*shell_error(int err_type, char *param, int err)
{
	g_status = err;
	if (err_type == QUOTE)
		ft_printf(2, "%s: error while looking for matching quote!", NAME);
	else if (err_type == NDIR)
		ft_printf(2, "%s: No such file for directory: ", NAME);
	else if (err_type == NPERM)
		ft_printf(2, "%s: permission denied: ", NAME);
	else if (err_type == NCMD)
		ft_printf(2, "%s: command not found: ", NAME);
	else if (err_type == DUPERR)
		ft_printf(2, "%s: dup2 failed\n", NAME);
	else if (err_type == FORKERR)
		ft_printf(2, "%s: fork failed\n", NAME);
	else if (err_type == PIPERR)
		ft_printf(2, "%s: error creating pipe\n", NAME);
	else if (err_type == NEARERR)
		ft_printf(2, "%s: syntax error near unexpected token: ", NAME);
	else if (err_type == MEM)
		ft_printf(2, "%s: no memory left on device\n", NAME);
	else if (err_type == IS_DIR)
		ft_printf(2, "%s: Is a directory: ", NAME);
	else if (err_type == NOT_DIR)
		ft_printf(2, "%s: Not a directory: ", NAME);
	ft_printf(2, "%s\n", param);
	return (NULL);
}
