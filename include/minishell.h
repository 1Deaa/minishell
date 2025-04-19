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
# include "libft.h"
# include "ft_printf.h"

typedef struct s_shell	t_shell;
typedef struct s_token	t_token;
typedef struct s_pak	t_pak;

/* ************************************************************************** */
/*                                 DEFINES                                    */
/* ************************************************************************** */

# define READ_END 0
# define WRITE_END 1
# define WPROMPT "\033[1;33m· \033[0m\033[1;34mstarshell\033[1;32m $ \033[0m"
# define XPROMPT "\033[1;33m· \033[0m\033[1;34mstarshell\033[1;31m $ \033[0m"
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
	t_token			*tokens;
	t_pak			*cmds;
}	t_shell;

//SHELL PROTOTYPES
void	shell_signal(void);
void	shell_signal_reset(void);
void	shell_loop(t_shell *shell);
void	shell_clean(t_shell *shell);
void	shell_debug(t_shell *shell);
char	*shell_read(t_shell *shell);

/* ************************************************************************** */
/*                           TOKEN + EXPAND + SYNTAX                          */
/* ************************************************************************** */

typedef enum e_token_type
{
	TK_PIPE,
	TK_WORD,
	TK_REDIR_IN,
	TK_REDIR_OUT,
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
int		count_word_tokens(t_token *token);
void	assign_token_types(t_token *tokens);

//SYNTAX PROTOTYPES
bool	is_redirection(t_token *node);
bool	is_special(t_token *node);
bool	is_correct_syntax(t_token *tokens);

/* ************************************************************************** */
/*                                  PARSE                                     */
/* ************************************************************************** */

typedef struct s_pak
{
	char			**full_cmd;
	char			*full_path;
	int				infile;
	int				outfile;
	struct s_pak	*next;
	struct s_pak	*prev;
}					t_pak;

t_pak	*parse(t_shell *shell, t_token *token);
int		parse_redir(t_pak **curr, t_token **token);
int		parse_redir_out(t_pak **curr, t_token **token);
int		parse_redir_in(t_pak **curr, t_token **token);
int		parse_redir_app(t_pak **curr, t_token **token);
void	print_paks(t_pak *head);

/* ************************************************************************** */
/*                                  ERROR                                     */
/* ************************************************************************** */

enum	e_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 6,
	DUPERR = 7,
	FORKERR = 8,
	PIPERR = 9,
	NEARERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13
};

void	*shell_error(int err_type, char *param, int err);

/* ************************************************************************** */
/*                                  ENVP                                      */
/* ************************************************************************** */

char	**dup_envp(char **envp);
void	free_envp(char **envp, int count);
int		count_envp(char **envp);
char	*get_envp(char **envp, const char *name);
void	print_envp(const char *prefix, char **envp);

/* ************************************************************************** */
/*                                EXECUTE                                     */
/* ************************************************************************** */

char	*find_path(t_shell *shell, char *command);

/* ************************************************************************** */
/*                               BUILT-IN                                     */
/* ************************************************************************** */

void	echo(int argc, char **argv, char **envp);
void	env(int argc, char **argv, char **envp);
void	export(t_shell *shell, char **argv, char **envp);
void	pwd(int argc, char **argv, char **envp);

#endif
