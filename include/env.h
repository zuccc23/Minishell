/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:38:26 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:38:27 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

// value = Exemple : "PATH=usr/bin:/bin:..."
typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}	t_env;

//recupere l'env

char	*ft_getenv(char *str, char **env);
char	*copy_path(const char *s1, int start);
char	**copy_env(char **env);
char	**mini_env(void);

#endif