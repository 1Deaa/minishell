/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:40:26 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/08 21:23:08 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "token.h"

/*
*/
typedef enum e_parse_type
{
	EXEC,
	REDIR,
	PIPE
}	t_type;
/*
*/
struct s_cmd
{
	t_type	type;
};
/*
*/
struct s_execcmd
{
	t_type	type;
	char	**argv;
};
/*
*/
struct s_pipecmd
{
	t_type			type;
	struct s_cmd	*left;
	struct s_cmd	*right;
};
/*
*/
struct s_redircmd
{
	t_type			type;
	struct s_cmd	*cmd;
	char			*file;
	char			*efile;
	int				mode;
	int				fd;
};
/*
Function specific struct.
*/
typedef struct s_find_cmd_path
{
	char	*start;
	char	*end;
	char	*path;
}	t_find_cmd_path;
/*
Function specific struct.
*/
typedef struct s_tokenize
{
	const char	*start;
	char		**tokens;
	int			token_count;
	int			len;
	int			i;
}	t_tokenize;

typedef struct s_shell
{
	char			*device;
	char			*user;
	char			*cwd;
	char			*prompt;
	char			*command;
	t_token			*tokens;
	struct s_cmd	*parse;
}	t_shell;

#endif
