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
# include <limits.h>
# include <termios.h>
# include "colors.h"
# include "structs.h"
# include "libft.h"

typedef enum
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_AMPERSAND,
	TOKEN_UNKNOWN
}	e_tokentype;

typedef struct
{
	e_tokentype	type;
	char		*value;
}	t_token;

typedef struct s_input
{
	char	*device;
	char	*user;
	char	*cwd;
	char	*prompt;
	char	*command;
}	t_input;

/*
Creates a custom prompt for the shell.
*/
char	*create_prompt(void);
/*
Handles the signals CTRL-C CTRL-\
*/
void	shell_signal_handlers(void);
/*
Keeps the shell alive and working.
*/
void	shell_loop(void);
/*
Find the path for CMD.
*/
char	*find_cmd_path(char *cmd);

#endif