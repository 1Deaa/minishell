/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:29:39 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/03 21:41:47 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# include <termios.h>
# include "colors.h"

# define DEBUG 42

typedef struct	s_mini
{
	int	pid;
	int	exit;
	int	ret;
	int	in;
	int	out;
	int	fdin;
	int	fdout;
	int	pipout;
	int	pipin;
	int	parent;
	int	last;
}	t_mini;

#endif