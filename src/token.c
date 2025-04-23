/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:26:52 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/10 17:17:43 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*skip_whitespace(const char *p)
{
	while (*p && ft_isspace((unsigned char)*p))
	{
		p++;
	}
	return (p);
}

static char	*special_token(const char **p)
{
	char	buffer[3];
	char	*token;

	if (!p || !*p || !**p)
		return (NULL);
	buffer[0] = **p;
	(*p)++;
	if ((buffer[0] == '<' || buffer[0] == '>') && **p == buffer[0])
	{
		buffer[1] = **p;
		(*p)++;
	}
	else
	{
		buffer[1] = '\0';
	}
	buffer[2] = '\0';
	token = ft_strdup(buffer);
	return (token);
}

static char	*quoted_token(const char **p)
{
	char		quote;
	const char	*start;
	size_t		len;
	char		*token;

	if (!p || !*p || !**p)
		return (NULL);
	quote = **p;
	start = *p;
	(*p)++;
	while (**p && **p != quote)
		(*p)++;
	if (**p == quote)
		(*p)++;
	len = *p - start;
	token = (char *)malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strncpy(token, start, len);
	token[len] = '\0';
	return (token);
}

static char	*word_token(const char **p)
{
	const char	*start;
	size_t		len;
	char		*token;

	start = *p;
	while (**p && !ft_isspace((unsigned char)**p) && !ft_strchr("|><'\"", **p))
	{
		(*p)++;
	}
	len = *p - start;
	token = (char *)malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strncpy(token, start, len);
	token[len] = '\0';
	return (token);
}

t_token	*tokenizer(const char *input)
{
	t_token		*head;
	const char	*p;
	char		*token;

	head = NULL;
	p = input;
	while (p &&*p)
	{
		p = skip_whitespace(p);
		if (*p == '\0')
			break ;
		if (ft_strchr("<|>", *p))
			token = special_token(&p);
		else if (ft_strchr("'\"", *p))
			token = quoted_token(&p);
		else
			token = word_token(&p);
		if (token)
		{
			add_token(&head, token);
			free(token);
		}
	}
	assign_token_types(head);
	return (head);
}
