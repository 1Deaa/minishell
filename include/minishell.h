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
# include <fcntl.h>
# include <limits.h>
# include <termios.h>
# include "colors.h"
# include "structs.h"
# include "libft.h"

# define DEBUG 42

/*
Creates a custom prompt for the shell.
*/
char			*create_prompt(void);
/*
Handles the signals CTRL-C CTRL-\
*/
void			shell_signal_handlers(void);
/*
Keeps the shell alive and working.
*/
void			shell_loop(int mode);
/*
Find the path for CMD.
*/
char			*find_cmd_path(char *cmd);
/* ************************************************************************** */
/*                           TOKEN.C  TOKEN_UTILS.C                           */
/* ************************************************************************** */
/*
Allocates COUNT tokens.
*/
char			**alloc_tokens(int count);
/*
Count tokens in INPUT. 
*/
int				count_tokens(const char *input);
/*
frees COUNT tokens.
*/
void			free_tokens(char **tokens, int count);
/* ************************************************************************** */
/* 							PARSE.C PARSE_UTILS.C							  */
/* ************************************************************************** */
struct s_cmd		*parse_redir(char **tokens, int *index);
struct s_cmd		*parse_pipe(char **tokens, int *index);
struct s_execcmd	*parse_exec(char **tokens, int *index);
int					count_exec_args(char **tokens);
struct s_cmd		*parser(char **tokens);

#endif