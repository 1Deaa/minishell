/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:25:56 by drahwanj          #+#    #+#             */
/*   Updated: 2025/03/13 22:35:26 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include "../libft/libft.h"

typedef enum e_token_type
{
	TK_PIPE,			/*0*/
	TK_WORD,			/*1*/
	TK_REDIR_IN,		/*2*/
	TK_REDIR_OUT,		/*3*/
	TK_AMPERSAND,		/*4*/
	TK_SINGLE_QUOTED,	/*5*/
	TK_DOUBLE_QUOTED,	/*6*/
	TK_APPEND,			/*7*/
	TK_HEREDOC,			/*8*/
}	t_type;

typedef struct s_token
{
	char			*value;
	t_type			type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

t_token	*new_token(const char *value);
t_token	*tokenize(const char *input);
t_token	*expander(t_token *tokens);
void	add_token(t_token **head, const char *value);
void	free_tokens(t_token	*token);
void	print_tokens(t_token *token);
void	assign_token_types(t_token *tokens);

#endif