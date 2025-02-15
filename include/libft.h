/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:30:52 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/14 19:30:55 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

#include "minishell.h"

/*
Return the length of S
*/
int		ft_strlen(const char *s);
/*
Allocate COUNT elements of SIZE bytes each, all initialized to 0.
*/
void	*ft_calloc(size_t count, size_t size);
/*
Append SRC onto DEST.
*/
char	*ft_strcat(char *dest, const char *src);
/*
Finds the first occurence of C in S.
*/
char	*ft_strchr(const char *s, int c);
/*
Checks for whitespace.
*/
int		ft_isspace(char c);

#endif
