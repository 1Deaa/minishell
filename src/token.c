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

static const char	*extract_operator_or_quote(const char *input, t_tokenize *t)
{
	char	quote;

	if (ft_strchr("|<>&", *input))
	{
		t->start = input;
		t->len = 1;
		if ((*input == '<' && *(input + 1) == '<')
			|| (*input == '>' && *(input + 1) == '>'))
			t->len = 2;
		return (input + t->len);
	}
	else if (*input == '"' || *input == '\'')
	{
		quote = *input++;
		t->start = input;
		while (*input && *input != quote)
			input++;
		t->len = input - t->start;
		if (*input == quote)
			input++;
		return (input);
	}
	return (NULL);
}

/* ************************************************************************** */
static const char	*extract_token(const char *input, t_tokenize *t)
{
	const char	*next;

	while (ft_isspace(*input))
		input++;
	if (*input == '\0')
		return (NULL);
	next = extract_operator_or_quote(input, t);
	if (next)
		return (next);
	t->start = input;
	while (*input && !ft_isspace(*input) && !ft_strchr("|<>&", *input))
		input++;
	t->len = input - t->start;
	return (input);
}

/* ************************************************************************** */

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
		input = extract_token(input, &t);
		if (!input)
			break ;
		t.tokens[++t.i] = ft_strndup(t.start, t.len);
		if (!t.tokens[t.i])
		{
			free_tokens(t.tokens, t.i);
			return (NULL);
		}
	}
	t.tokens[++t.i] = NULL;
	return (t.tokens);
}
/* ************************************************************************** */
