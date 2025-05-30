/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:36:47 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/14 15:23:52 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand(char *name, t_shell *shell)
{
	char	*ret;

	if (!name)
		return (NULL);
	if (!ft_strcmp(name, "0") || !ft_strcmp(name, "1") || !ft_strcmp(name, "?"))
	{
		ret = special_expand(name, shell);
		free(name);
		if (!ret)
			ret = ft_strdup("");
		return (ret);
	}
	if (!ft_strcmp(name, ""))
	{
		free(name);
		return (ft_strdup("$"));
	}
	ret = ft_strdup(env_grab(shell->envp, name));
	if (!ret)
	{
		free(name);
		return (ft_strdup(""));
	}
	free(name);
	return (ret);
}

void	expand_single_quoted(t_token *token)
{
	int		i;
	char	*exp;

	i = 0;
	i++;
	while (token->value[i] && token->value[i] != '\'')
		i++;
	exp = ft_strndup((token->value) + 1, i - 1);
	free(token->value);
	token->value = exp;
}

void	expand_quoted(t_token *token, t_shell *shell)
{
	int		i;
	char	*str;
	char	*exp;

	i = 0;
	str = NULL;
	exp = NULL;
	if (token->value[0] == '"')
		i++;
	while (token->value[i])
	{
		while (token->value[i] == '$' && token->value[i + 2] != '\0')
		{
			exp = expand(exname(token->value, &i), shell);
			str = ft_strjoin(str, exp);
			free(exp);
		}
		if (token->value[i] == '"')
			break ;
		str = ft_charjoin(str, token->value[i]);
		i++;
	}
	free(token->value);
	token->value = str;
}

void	expand_word(t_token *token, t_shell *shell)
{
	int		i;
	char	*str;
	char	*exp;

	i = 0;
	str = NULL;
	exp = NULL;
	while (token->value[i])
	{
		if (token->value[i] == '$' && token->value[i + 1] != '\0')
		{
			exp = expand(exname(token->value, &i), shell);
			str = ft_strjoin(str, exp);
			free(exp);
		}
		else
		{
			str = ft_charjoin(str, token->value[i]);
			i++;
		}
	}
	free(token->value);
	token->value = str;
}

t_token	*expander(t_token *tokens, t_shell *shell)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (check_heredoc_filename(current))
			expand_heredoc(current);
		else if (current->type == TK_WORD)
			expand_word(current, shell);
		else if (current->type == TK_DOUBLE_QUOTED)
		{
			expand_quoted(current, shell);
			if (!current->value)
				current->value = ft_strdup("");
		}
		else if (current->type == TK_SINGLE_QUOTED)
		{
			expand_single_quoted(current);
			if (!current->value)
				current->value = ft_strdup("");
		}
		current = current->next;
	}
	return (tokens);
}
