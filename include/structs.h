/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:40:26 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/14 00:03:46 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/*
*/
typedef enum e_parse_type
{
	EXEC,
	REDIR,
	PIPE
}	t_parse_type;
/*
*/
struct s_cmd
{
	t_parse_type	type;
};
/*
*/
struct s_execcmd
{
	t_parse_type	type;
	char			**argv;
};
/*
*/
struct s_pipecmd
{
	t_parse_type	type;
	struct s_cmd	*left;
	struct s_cmd	*right;
};
/*
*/
struct s_redircmd
{
	t_parse_type	type;
	struct s_cmd	*cmd;
	char			*file;
	char			*efile;
	int				mode;
	int				fd;
};

#endif
