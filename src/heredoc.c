/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halmuhis <halmuhis@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:25:17 by halmuhis          #+#    #+#             */
/*   Updated: 2025/04/28 17:43:12 by halmuhis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

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
	while (true)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, delimiter, ft_strlen(delimiter)))
		{
			print_heredoc_warning(line, delimiter);
			break ;
		}
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

static int	write_heredoc_to_file(char *content, char *heredoc_file)
{
	int	fd;

	fd = open(heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		ft_printf(2, "Error opening heredoc file");
		return (-1);
	}
	if (write(fd, content, ft_strlen(content)) == -1)
	{
		ft_printf(2, "Error writing to heredoc file");
		close(fd);
		return (-1);
	}
	close(fd);
	return (open(heredoc_file, O_RDONLY));
}

void	heredoc_child(char *delimiter)
{
	char	*content;
	int		fd;

	if (!delimiter)
		return ;
	content = get_heredoc_input(delimiter);
	if (!content)
		return ;
	fd = write_heredoc_to_file(content, HEREDOC_FILE);
	free(content);
	if (fd < 0)
		exit(1);
	close(fd);
	exit(0);
}

int	handle_heredoc(char *delimiter)
{
	t_proc	process;

	process.pid = fork();
	if (process.pid < 0)
		return (-1);
	if (process.pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		heredoc_child(delimiter);
	}
	else
	{
		shell_signal_ignore();
		waitpid(process.pid, &(process.status), 0);
		shell_signal();
		if (WIFSIGNALED(process.status) && WTERMSIG(process.status) == SIGINT)
		{
			g_signal = SIGINT;
			return (-1);
		}
		if (WIFEXITED(process.status) && WEXITSTATUS(process.status) != 0)
			return (-1);
		return (open(HEREDOC_FILE, O_RDONLY));
	}
	return (-1);
}
