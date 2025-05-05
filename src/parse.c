/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 07:47:06 by drahwanj          #+#    #+#             */
/*   Updated: 2025/04/17 07:47:07 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_pak	*new_pak(void)
{
	t_pak	*pak;

	pak = (t_pak *)ft_calloc(1, sizeof(t_pak));
	if (!pak)
		return (NULL);
	pak->infile = STDIN_FILENO;
	pak->outfile = STDOUT_FILENO;
	return (pak);
}

int	parse_pipe(t_pak **curr, t_token **token)
{
	t_pak	*next;

	if (!curr || !*curr)
		return (-1);
	next = new_pak();
	if (!next)
		return (-1);
	(*curr)->next = next;
	next->prev = *curr;
	*curr = next;
	(*token) = (*token)->next;
	return (0);
}

int	parse_words(t_shell *shell, t_pak **curr, t_token **token)
{
	char	**argv;
	int		i;
	int		wc;

	if (!curr || !*curr)
		return (-1);
	wc = count_word_tokens(*token);
	argv = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!argv)
		return (-1);
	i = 0;
	while (i < wc)
	{
		argv[i] = (*token)->value;
		(*token) = (*token)->next;
		i++;
	}
	argv[i] = NULL;
	(*curr)->full_cmd = argv;
	(*curr)->full_path = find_path(shell, argv[0]);
	return (0);
}

int	parse_token(t_shell *shell, t_pak **curr, t_token **token)
{
	if ((*token)->type == TK_PIPE)
	{
		if (parse_pipe(curr, token) < 0)
			return (-1);
		return (0);
	}
	else if ((*token)->type == TK_WORD || (*token)->type == TK_DOUBLE_QUOTED
		|| (*token)->type == TK_SINGLE_QUOTED)
	{
		if (parse_words(shell, curr, token) < 0)
			return (-1);
		return (0);
	}
	else if (is_redirection(*token))
	{
		if (parse_redir(shell, curr, token) < 0)
			return (-1);
		return (0);
	}
	return (-1);
}

t_pak	*parser(t_shell *shell, t_token *token)
{
	t_pak	*head;
	t_pak	*curr;
	int		res;

	curr = new_pak();
	if (!curr)
		return (NULL);
	head = curr;
	while (token)
	{
		res = parse_token(shell, &curr, &token);
		if (res < 0)
			break ;
	}
	return (head);
}
