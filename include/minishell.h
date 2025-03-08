/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:29:39 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/08 21:23:00 by drahwanj         ###   ########.fr       */
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
# include "structs.h"
# include "token.h"
# include "../libft/libft.h"

# define DEBUG 42

/*
Creates a custom prompt for the shell.
*/
char				*create_prompt(void);
/*
Handles the signals CTRL-C CTRL-\
*/
void				shell_signal(void);
/*
Keeps the shell alive and working.
*/
void				shell_loop(int mode);
/*
Find the path for CMD.
*/
char				*find_cmd_path(char *cmd);

/* ************************************************************************** */
/*                          PARSE.C PARSE_UTILS.C							  */
/* ************************************************************************** */
struct s_cmd		*parse_redir(char **tokens, int *index);
struct s_cmd		*parse_pipe(char **tokens, int *index);
struct s_cmd		*parse_exec(char **tokens, int *index);
int					count_exec_args(char **tokens);
struct s_cmd		*parser(char **tokens);
struct s_redircmd	*create_redircmd(struct s_cmd *cmd,
						char **tokens, int *index);
void				print_cmd(struct s_cmd *cmd, int indent);
/* ************************************************************************** */
/*                               BUILT-IN       							  */
/* ************************************************************************** */

void				echo(struct s_cmd *cmd);

/* ************************************************************************** */
/*                             EXECUTIONER.C       							  */
/* ************************************************************************** */

void				run_cmd(struct s_cmd *parse);

#endif