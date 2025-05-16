/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:50:20 by drahwanj          #+#    #+#             */
/*   Updated: 2025/05/16 10:50:21 by drahwanj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_TOOLS_H
# define ENV_TOOLS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

char	**env_dup(char **envp);
void	*env_free_i(char **envp, size_t n);
void	env_free(char **envp);
char	**env_app(char **envp, char *value);
size_t	env_count(char **args);
void	env_print(const char *prefix, char **envp);
void	env_print_export(const char *prefix, char **envp);
char	*env_grabentry(char **envp, const char *name);
char	*env_newentry(char *name, char *value);
char	*env_grab(char **envp, const char *name);
int		env_index(char **envp, char *name);
char	**env_del(char **envp, char *name);
char	*env_entry_name(char *entry);
char	*env_entry_value(char *entry);
char	*env_entry_grab(char *entry);
void	env_update(char **envp, char *name, char *value);

#endif
