/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halmuhis <halmuhis@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:29:39 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/12 10:37:49 by halmuhis         ###   ########.fr       */
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
# include <dirent.h>
# include "colors.h"
# include "libft.h"
# include "ft_printf.h"
# include "env_tools.h"

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
# define C_NAME "\033[0m\033[1;34mstarshell\001\033[0m\002"
# define NO_SIG 0
# define HEREDOC_FILE "/tmp/.minishell_heredoc"

/* ************************************************************************** */
/*                                 SHELL                                      */
/* ************************************************************************** */

typedef struct s_shell
{
	char			*command;
	char			**argv;
	char			**envp;
	bool			debug;
	bool			exit;
	int				shlvl;
	int				e_status;
	pid_t			last_pid;
	t_token			*tokens;
	t_pak			*cmds;
}	t_shell;

//SHELL PROTOTYPES
void	shell_signal(void);
void	shell_signal_reset(void);
void	shell_signal_ignore(void);
void	enable_ctrl_backslash(void);
void	shell_loop(t_shell *shell);
void	shell_clean(t_shell *shell);
void	shell_debug(t_shell *shell);
char	*shell_read(t_shell *shell);
void	shell_init(t_shell *shell);
void	shell_exit(t_shell *shell);

/* ************************************************************************** */
/*                           TOKEN + EXPAND + SYNTAX                          */
/* ************************************************************************** */

struct	s_tokenizer
{
	t_token		*head;
	const char	*p;
	char		*token;
	bool		combine;
};

typedef enum e_tokenization_type
{
	DEFAULT,
	REMAKE,
}	t_tokenization;

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

typedef struct s_args
{
	int		argc;
	char	**argv;
}			t_args;

typedef struct s_token
{
	char			*value;
	bool			combine;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

//EXPAND PROTOTYPES
t_token	*expander(t_token *tokens, t_shell *shell);
char	*special_expand(char *str, t_shell *shell);
bool	is_expandable(char c);
char	*exname(char *token, int *index);
bool	check_heredoc_filename(t_token *token);
void	expand_single_quoted(t_token *token);
void	expand_quoted(t_token *token, t_shell *shell);
void	expand_word(t_token *token, t_shell *shell);
void	expand_heredoc(t_token *current);
void	expand_heredoc_quoted(t_token *token);

//TOKEN PROTOTYPES
t_token	*new_token(const char *value);
t_token	*tokenizer(const char *input, t_tokenization type);
t_token	*filter_tokens(t_token *head);
t_token	*retokenize(t_token *head);
void	add_token(t_token **head, const char *value, bool *combine);
void	free_tokens(t_token	*token);
void	print_tokens(t_token *token);
int		count_args_tokens(t_token *token);
void	fill_args_tokens(t_shell *shell, t_args *args, t_pak **cur,\
	t_token **token);
void	assign_token_types(t_token *tokens, t_tokenization type);

//SYNTAX PROTOTYPES
bool	is_redirection(t_token *node);
bool	is_special(t_token *node);
bool	is_correct_syntax(t_shell *shell, t_token *tokens);

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

t_pak	*parser(t_shell *shell, t_token *token);
int		get_fd(t_shell *shell, int oldfd, t_token *token, int type);
int		ambiguous_redirect(t_shell *shell, char *name, int err);
int		parse_redir(t_shell *shell, t_pak **curr, t_token **token);
void	*pak_redir_util(t_shell *shell, t_pak *cmd, int fd[2]);
int		parse_redir_out(t_shell *shell, t_pak **curr, t_token **token);
int		parse_redir_in(t_shell *shell, t_pak **curr, t_token **token);
int		parse_redir_app(t_shell *shell, t_pak **curr, t_token **token);
int		parse_heredoc(t_shell *shell, t_pak **curr, t_token **token);
int		handle_heredoc(char *delimiter);
void	print_paks(t_pak *head);
void	free_paks(t_shell *shell, t_pak *head);
int		count_paks(t_pak *head);

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

void	*shell_error(t_shell *shell, int err_type, char *param, int err);
int		redir_error(t_shell *shell, int err_type, char *param, int err);
void	print_heredoc_warning(char *line, char *delimiter);

/* ************************************************************************** */
/*                                  ENVP                                      */
/* ************************************************************************** */

char	**dup_envp(char **envp);
void	free_envp(char **envp, int count);
int		count_envp(char **envp);
char	*get_envp(char **envp, const char *name);
int		chdir_home(t_shell *shell);
void	print_envp(const char *prefix, char **envp);
void	update_underscore_env(t_shell *shell, t_pak *cmd);

/* ************************************************************************** */
/*                                EXECUTE                                     */
/* ************************************************************************** */

typedef struct s_proc
{
	int		status;
	pid_t	pid;
}			t_proc;

/*
EXEC
*/
void	*exec_pak(t_shell *shell, t_pak *cmd);
int		executer(t_shell *shell, t_pak *cmd);
void	pak_fork(t_shell *shell, t_pak *cmd, int fd[2]);
void	wait_processes(t_shell *shell, int count);
void	*is_forkable(t_shell *shell, t_pak *cmd, int fd[2]);
void	handle_fork(int infile, int outfile, int fd[2]);
DIR		*check_cmd(t_shell *shell, t_pak *cmd);
/*
EXEC_UTILS
*/
bool	is_builtin(t_pak *cmd);
void	*pak_redir(t_shell *shell, t_pak *cmd, int fd[2]);
void	*pak_process(t_shell *shell, t_pak *cmd, int fd[2]);
void	close_pak_infile(t_pak *pak);
/*
FIND_PATH
*/
char	*find_path(t_shell *shell, char *command);

/* ************************************************************************** */
/*                               BUILT-IN                                     */
/* ************************************************************************** */

int		echo(t_pak *cmd);
int		env(char **envp, t_pak *pak);
int		export(t_shell *shell, t_pak *cmd); // Changed from char **envp
int		pwd(t_pak *cmd);
int		bn_exit(t_shell *shell, t_pak *pak);
int		cd(t_shell *shell, t_pak *cmd);
int		unset(t_shell *shell, t_pak *cmd);

#endif
