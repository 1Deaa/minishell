/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:15:24 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/16 16:15:25 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_args(char **cmd)
{
	int	i;

	if (cmd && cmd[0])
	{
		printf(" full_cmd:");
		i = 0;
		while (cmd[i])
		{
			printf(" \"%s\"", cmd[i]);
			i++;
		}
		printf("\n");
	}
	else
		printf(" full_cmd: (none)\n");
}

void	print_fd_info(int infile, int outfile)
{
	printf(" infile fd : %d\n", infile);
	printf(" outfile fd: %d\n", outfile);
}

void	print_link_info(t_pak *prev, t_pak *next)
{
	printf(" prev pak  : %p\n", (void *)prev);
	printf(" next pak  : %p\n", (void *)next);
}

void	print_one_pak(t_pak *pak, int idx)
{
	printf("━━━ Pak %d ━━━\n", idx);
	print_cmd_args(pak->full_cmd);
	if (pak->full_path)
		printf(" full_path: %s\n", pak->full_path);
	else
		printf(" full_path: (null)\n");
	print_fd_info(pak->infile, pak->outfile);
	print_link_info(pak->prev, pak->next);
	printf("\n");
}

void	print_paks(t_pak *head)
{
	t_pak	*curr;
	int		idx;

	curr = head;
	idx = 0;
	while (curr)
	{
		print_one_pak(curr, idx);
		curr = curr->next;
		idx++;
	}
}
