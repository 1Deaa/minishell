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

//SHELL PROTOTYPES
void	shell_signal(void);
void	shell_signal_reset(void);
void	shell_loop(t_shell *shell);
void	shell_clean(t_shell *shell);
void	shell_debug(t_shell *shell);
char	*shell_read(t_shell *shell, char *prompt);

/* ************************************************************************** */
/*                           TOKEN + EXPAND + SYNTAX                          */
/* ************************************************************************** */

typedef enum e_token_type
{
	TK_PIPE,
	TK_WORD,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	//TK_AMPERSAND,
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

//SYNTAX PROTOTYPES
bool	is_redirection(t_token *node);
bool	is_special(t_token *node);
bool	is_correct_syntax(t_token *tokens);

/* ************************************************************************** */
/*                                  PARSE                                     */
/* ************************************************************************** */

typedef enum e_parse
{
	PS_EXEC,
	PS_PIPE,
	PS_REDIR,
}	t_parse;

typedef struct s_cmd
{
	t_parse	type;
}	t_cmd;

typedef struct s_execcmd
{
	t_parse	type;
	char	**argv;
	char	*path;
}	t_execmd;

typedef struct s_pipecmd
{
	t_parse	type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

typedef struct s_redircmd
{
	t_parse	type;
	t_cmd	*cmd;
	char	*file;
	int		flags;
	int		mode;
	int		fd;
}	t_redircmd;

/*PARSE PROTOTYPES*/
t_cmd	*parser(t_token *tokens);
t_cmd	*parse_exec(t_token **token);
void	parse_clean(t_cmd *cmd);

/*PARSE UTILS*/
bool	is_exec(t_token *token);
int		count_exec_args(t_token *token);
void	configure_redir(t_redircmd *rcmd, const char *op);

/*PRINT ABSTRACT SYNTAX TREE*/
void	print_ast_tree(t_cmd *ast);
void	print_indent(int depth, bool parent_last[]);
void	print_branch(int depth, bool is_last);
void	print_exec(t_execmd *ecmd);
void	print_pipe(t_pipecmd *pcmd, int depth, bool parent_last[]);
void	print_redir(t_redircmd *rcmd, int depth, bool parent_last[]);
void	print_ast(t_cmd *cmd, int depth, bool is_last, bool parent_last[]);

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
void	run_exec(t_shell *shell, t_execmd *ecmd);
void	run_redir(t_shell *shell, t_redircmd *rcmd);

/* ************************************************************************** */
/*                               BUILT-IN                                     */
/* ************************************************************************** */

void	echo(int argc, char **argv, char **envp);
void	env(int argc, char **argv, char **envp);
void	export(t_shell *shell, char **argv, char **envp);
void	pwd(int argc, char **argv, char **envp);

#endif
