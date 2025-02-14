/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 00:18:08 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/14 00:18:08 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_prompt(t_input *prt)
{
	size_t	size;

	prt->device = getenv("NAME");
	prt->user = getenv("USER");
	prt->cwd = getcwd(NULL, 0);
	prt->prompt = "";
	if (!prt->user)
		prt->user = "unknown";
	if (!prt->device)
		prt->device = "minishell";
	if (!prt->cwd)
		prt->cwd = "shell";
	size = ft_strlen(prt->device) + ft_strlen(prt->cwd) + ft_strlen(prt->user)
		+ ft_strlen(YELLOW) + ft_strlen(RESET) + ft_strlen(RED) + 5;
	prt->prompt = (char *)ft_calloc(size, sizeof(char));
}

char	*create_prompt(void)
{
	t_input	prt;

	init_prompt(&prt);
	if (!prt.prompt)
	{
		free(prt.cwd);
		return (RED"minishell$ "RESET);
	}
	ft_strcat(prt.prompt, YELLOW);
	ft_strcat(prt.prompt, prt.user);
	ft_strcat(prt.prompt, "@");
	ft_strcat(prt.prompt, prt.device);
	ft_strcat(prt.prompt, ":");
	ft_strcat(prt.prompt, RED);
	ft_strcat(prt.prompt, prt.cwd);
	ft_strcat(prt.prompt, RESET);
	ft_strcat(prt.prompt, "$ ");
	free(prt.cwd);
	return (prt.prompt);
}
