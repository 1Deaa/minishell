/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:29:39 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/19 15:42:43 by drahwanj         ###   ########.fr       */
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
# include "../libft/libft.h"

typedef struct s_shell	t_shell;
typedef struct s_token	t_token;

/* ************************************************************************** */
/*                                 DEFINES                                    */
/* ************************************************************************** */

# define PROMPT "\033[1;34m· \033[0m\033[1;31mstarshell\033[1;34m $ \033[0m"
# define NAME	"starshell"

/* ************************************************************************** */
/*                                 SHELL                                      */
/* ************************************************************************** */

typedef struct s_shell
{
	char			*command;
	char			**argv;
	char			**envp;
	bool			debug;
	int				exit;
	t_token			*tokens;
	struct s_cmd	*parse;
}	t_shell;

void	shell_signal(void);
void	shell_loop(t_shell *shell);
void	shell_debug(t_shell *shell);
char	*shell_read(char *prompt);

/* ************************************************************************** */
/*                               BUILT-IN                                     */
/* ************************************************************************** */

void	echo(struct s_cmd *cmd);

/* ************************************************************************** */
/*                         TOKEN + EXPANDER + SYNTAX                          */
/* ************************************************************************** */

typedef enum e_token_type
{
	TK_PIPE,
	TK_WORD,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_AMPERSAND,
	TK_SINGLE_QUOTED,
	TK_DOUBLE_QUOTED,
	TK_APPEND,
	TK_HEREDOC,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

//EXPAND PROTOTYPES
t_token	*expander(t_token *tokens, t_shell *shell);
char	*special_expand(char *str, t_shell *shell);
bool	is_expandable(char c);

//TOKEN PROTOTYPES
t_token	*new_token(const char *value);
t_token	*tokenize(const char *input);
void	add_token(t_token **head, const char *value);
void	free_tokens(t_token	*token);
void	print_tokens(t_token *token);
void	assign_token_types(t_token *tokens);

//REDIRECTION PROTOTYPES
bool	is_redirection(t_token *node);
bool	is_special(t_token *node);
bool	is_correct_syntax(t_token *tokens);

/* ************************************************************************** */

#endif
