/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_re.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:21:49 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/03 15:21:49 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*retokenize(t_token *head)
{
	t_token	*curr;
	t_token	*next;
	char	*value;

	curr = head;
	while (curr)
	{
		if (true == curr->combine && curr->next)
		{
			next = curr->next;
			value = ft_strjoin(curr->value, next->value);
			if (!value)
				break ;
			free(next->value);
			curr->value = value;
			curr->combine = next->combine;
			curr->next = next->next;
			if (next->next)
				(next->next)->prev = curr;
			free(next);
		}
		else
			curr = curr->next;
	}
	return (head);
}
