/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:13:55 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/19 09:13:56 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_heredoc_file(int file)
{
	char	*number;
	char	*file_name;
	char	*heredoc_file;

	number = ft_itoa(file);
	if (!number)
		return (NULL);
	heredoc_file = ft_strdup(HEREDOC_FILE);
	if (!heredoc_file)
	{
		free(number);
		return (NULL);
	}
	file_name = ft_strjoin(heredoc_file, number);
	if (!file_name)
	{
		free(number);
		free(heredoc_file);
		return (NULL);
	}
	free(number);
	return (file_name);
}

int	open_heredoc(char *file)
{
	int	fd;

	if (!file)
		return (-1);
	fd = open(file, O_RDONLY);
	return (fd);
}
