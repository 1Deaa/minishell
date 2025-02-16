/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:50:24 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/14 19:50:25 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tokenize(const char *input)
{
	t_tokenize	t;

	t.i = -1;
	t.token_count = count_tokens(input);
	t.tokens = alloc_tokens(t.token_count);
	if (!t.tokens)
		return (NULL);
	while (*input)
	{
		while (ft_isspace((unsigned char)*input))
			input++;
		if (*input == '\0')
			break ;
		t.start = input;
		while (*input && !ft_isspace((unsigned char)*input))
			input++;
		t.len = input - t.start;
		t.tokens[++t.i] = ft_strndup(t.start, t.len);
		if (!t.tokens[t.i])
			free_tokens(t.tokens, t.i);
		if (!t.tokens[t.i])
			return (NULL);
	}
	t.tokens[t.i] = NULL;
	return (t.tokens);
}

/* ************************************************************************** */