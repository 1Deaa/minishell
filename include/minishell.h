/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:29:39 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/13 18:29:40 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <signal.h>
# include <termios.h>
# include "colors.h"

typedef struct s_input
{
	char	*device;
	char	*user;
	char	*cwd;
	char	*prompt;
	char	*command;
}	t_input;

/*
Return the length of S
*/
int		ft_strlen(const char *s);
/*
Allocate COUNT elements of SIZE bytes each, all initialized to 0.
*/
void	*ft_calloc(size_t count, size_t size);
/*
Append SRC onto DEST.
*/
char	*ft_strcat(char *dest, const char *src);
/*
Creates a custom prompt for the shell.
*/
char	*create_prompt(void);
/*
Handles the signals CTRL-C CTRL-\
*/
void	setup_signal_handlers(void);
/*
Keeps the shell alive and working.
*/
void	shell_loop(void);

#endif