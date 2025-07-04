/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:39:08 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:39:09 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

typedef struct s_command	t_command;

// get the path

char	*get_path(t_command *command, char **env);
char	*get_okpath(char **paths);
int		find_path_line(char **path_line, char **env);
int		join_paths(char **paths, char *command, char ***j_path);

// path utils 

void	init_paths(char ***paths, char ***jpaths, char **fpath, char **cmdtmp);
char	*free_paths(char ***paths, char ***j_paths, char **cmd_tmp);

#endif
