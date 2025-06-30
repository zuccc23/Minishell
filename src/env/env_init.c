/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:32:53 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:32:54 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//returns a copy of the envp
char	**copy_env(char **env)
{
	char	**tmp;
	int		i;

	if (!env || !env[0])
		return (mini_env());
	i = 0;
	tmp = malloc(sizeof(char *) * (count_strings(env) + 1));
	if (!tmp)
		return (NULL);
	while (env[i])
	{
		tmp[i] = ft_strdup(env[i]);
		if (!tmp[i])
		{
			free_strs(tmp);
			return (NULL);
		}
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

char	**mini_env(void)
{
	char	**env;

	env = malloc(sizeof(char *) * 5);
	if (!env)
		return (NULL);
	env[0] = ft_strdup("USER=dahmane");
	if (!env[0])
		return (NULL);
	env[1] = ft_strdup("PATH=/home/dahmane/.local/funcheck/host:/home/\
dahmane/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin\
:/bin:/usr/games:/usr/local/games:/snap/bin");
	if (!env[1])
		return (NULL);
	env[2] = ft_strdup("HOME=/home/dahmane");
	if (!env[2])
		return (NULL);
	env[3] = ft_strdup("LOGNAME=dahmane");
	if (!env[3])
		return (NULL);
	env[4] = NULL;
	return (env);
}

//recree la fonction getenv pour recuperer le bon environnement
char	*ft_getenv(char *str, char **env)
{
	int		i;
	char	*expand;

	i = 0;
	expand = NULL;
	if (!str)
		return (NULL);
	if (!env || !env[i])
		return (NULL);
	while (env[i])
	{
		if (is_same_var(env[i], str) == 1)
		{
			expand = copy_path(env[i], ft_strlen(str) + 1);
			if (!expand)
				return (NULL);
		}
		i++;
	}
	return (expand);
}

//strdup du bon chemin pour la var d'environnement
char	*copy_path(const char *s1, int start)
{
	int		i;
	int		j;
	int		size;
	char	*dest;

	i = 0;
	j = 0;
	size = ft_strlen(s1 + start);
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (i < start)
		i++;
	while (s1[i])
	{
		dest[j] = s1[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}
