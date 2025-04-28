/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halmuhis <halmuhis@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:25:17 by halmuhis          #+#    #+#             */
/*   Updated: 2025/04/28 15:03:59 by halmuhis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_line_to_content(char *content, char *line)
{
	char	*temp;
	size_t	len;

	len = ft_strlen(content) + ft_strlen(line) + 2;
	temp = malloc(len);
	if (!temp)
		return (0);
	ft_strlcpy(temp, content, len);
	ft_strcat(temp, line);
	ft_strcat(temp, "\n");
	free(content);
	return (temp);
}

static char	*get_heredoc_input(char *delimiter)
{
	char	*line;
	char	*content;

	content = malloc(1);
	if (!content)
		return (0);
	content[0] = '\0';
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, delimiter, ft_strlen(delimiter)))
			break ;
		content = append_line_to_content(content, line);
		if (!content)
		{
			free(line);
			return (0);
		}
		free(line);
	}
	free(line);
	return (content);
}

int	handle_heredoc(char *delimiter)
{
	char	*content;
	char	*heredoc_file;
	int		fd;

	if (!delimiter)
		return (-1); // Return -1 for invalid input
	heredoc_file = "/tmp/.minishell_heredoc";
	content = get_heredoc_input(delimiter);
	if (!content)
		return (-1); // Return -1 if input retrieval fails
	fd = open(heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error opening heredoc file");
		free(content);
		return (-1);
	}
	if (write(fd, content, ft_strlen(content)) == -1)
	{
		perror("Error writing to heredoc file");
		free(content);
		close(fd);
		return (-1);
	}
	close(fd);
	free(content);
	fd = open(heredoc_file, O_RDONLY);
	if (fd == -1)
		perror("Error opening heredoc file for reading");
	return (fd); // Return the file descriptor
}
