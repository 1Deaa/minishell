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
# include "colors.h"
# include <signal.h>

typedef struct s_input
{
	char	*device;
	char	*user;
	char	*cwd;
	char	*prompt;
	char	*command;
}	t_input;

/*
Return the length of s
*/
int		ft_strlen(const char *s);
/*
Join two strings together
*/
void	*ft_calloc(size_t count, size_t size);
char	*ft_strcat(char *dest, const char *src);
char	*create_prompt(void);
void	setup_signal_handlers(void);

#endif