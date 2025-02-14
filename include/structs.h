/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:40:26 by drahwanj          #+#    #+#             */
/*   Updated: 2025/02/14 18:40:27 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/*
Function specific struct.
*/
typedef struct s_find_cmd_path
{
	char	*start;
	char	*end;
	char	*path;
}	t_find_cmd_path;

#endif
