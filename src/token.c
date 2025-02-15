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

static void	skip_quoted_string(const char **p)
{
	char	q;

	q = *(*p)++;
	while (**p && **p != q)
		(*p)++;
	if (**p)
		(*p)++;
}

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
		count++;
		if (*p == '|' || *p == '<' || *p == '>' || *p == '&')
			p++;
		else if (*p == '"' || *p == '\'')
			skip_quoted_string(&p);
		else
		{
			while (*p && !ft_isspace((unsigned char)*p)
				&& !ft_strchr("|<>&", *p))
				p++;
		}
	}
	return (count);
}
