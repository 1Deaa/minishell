/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bn_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:27:35 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/17 14:27:37 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_cmp(char *s, char c)
{
	int	count;

	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count);
}

int	echo(t_pak *cmd)
{
	bool	newline;
	int		i[2];
	char	**argv;
	int		ret;

	i[0] = 0;
	i[1] = 0;
	newline = true;
	argv = cmd->full_cmd;
	close_pak_infile(cmd);
	while (argv && argv[++i[0]])
	{
		if (!i[1] && !ft_strncmp(argv[i[0]], "-n", 2)
			&& (count_cmp(argv[i[0]], 'n') == (ft_strlen(argv[i[0]]) - 1)))
			newline = false;
		else
		{
			i[1] = 1;
			ft_printf(1, argv[i[0]]);
			if (argv[i[0] + 1])
				ft_printf(1, " ");
		}
	}
	ret = write(1, "\n", newline);
	return (ret == -1);
}
