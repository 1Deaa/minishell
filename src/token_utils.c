/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 09:18:01 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/15 09:18:01 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_quoted_string(const char **p)
{
	char	q;

	q = *(*p)++;
	while (**p && **p != q)
		(*p)++;
	if (**p)
		(*p)++;
}

/* ************************************************************************** */

static void	count_op_and_strings(const char **p, int *count)
{
	if (ft_strchr("|<>&", **p))
	{
		(*count)++;
		if ((**p == '<' && *(*p + 1) == '<')
			|| (**p == '>' && *(*p + 1) == '>'))
			(*p) += 2;
		else
			(*p)++;
	}
	else if (**p == '"' || **p == '\'')
	{
		(*count)++;
		skip_quoted_string(p);
	}
}
/* ************************************************************************** */

int	count_tokens(const char *input)
{
	int			count;
	const char	*p;

	p = input;
	count = 0;
	while (*p)
	{
		while (ft_isspace((unsigned char)*p))
			p++;
		if (!*p)
			break ;
		count_op_and_strings(&p, &count);
		if (!ft_strchr("|<>&", *p) && *p != '"' && *p != '\'')
		{
			count++;
			while (*p && !ft_isspace((unsigned char)*p)
				&& !ft_strchr("|<>&", *p))
				p++;
		}
	}
	return (count);
}

/* ************************************************************************** */
char	**alloc_tokens(int count)
{
	char	**tokens;

	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	return (tokens);
}

/* ************************************************************************** */
void	free_tokens(char **tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
/* ************************************************************************** */
