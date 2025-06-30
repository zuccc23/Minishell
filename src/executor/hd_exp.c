/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_exp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:34:00 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:34:01 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Recherche et retourne la valeur d'une variable d'environnement
char	*get_env_value(const char *var_name, char **env)
{
	char	**tmp;
	char	*equals_pos;
	size_t	var_len;
	int		i;

	i = 0;
	var_len = ft_strlen(var_name);
	tmp = env;
	while (tmp[i])
	{
		equals_pos = ft_strchr(tmp[i], '=');
		if (equals_pos)
		{
			if (ft_strncmp(tmp[i], var_name, var_len) == 0
				&& tmp[i][var_len] == '=')
				return (equals_pos + 1);
		}
		i++;
	}
	return ("");
}

// Calcule la taille nécessaire après expansion des variables
size_t	find_expd_len(const char *line, char **env, const char *exit_str)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
		{
			i++;
			if (line[i] == '?')
				exit_code_len(&i, &len, exit_str);
			else if (ft_isalpha(line[i]) || line[i] == '_')
				hdle_env_var_len(line, &i, &len, env);
			else
				unknown_dollar_len(&len, &i);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

// Initialise les données nécessaires à l'expansion
static t_expand_data	*init_expand_data(t_data shell, size_t result_len)
{
	t_expand_data	*data;

	data = malloc(sizeof(t_expand_data));
	if (!data)
		return (NULL);
	data->exit_str = ft_itoa(shell.exec->last_exit_status);
	data->envp = shell.exec->envp;
	data->result = malloc(sizeof(char) * (result_len + 1));
	data->result_pos = 0;
	if (!data->exit_str || !data->result)
	{
		free(data->exit_str);
		free(data->result);
		free(data);
		return (NULL);
	}
	return (data);
}

// Copie une chaîne dans le résultat et met à jour la position
void	copy_to_result(t_expand_data *data, const char *str)
{
	size_t	len;

	len = ft_strlen(str);
	ft_strlcpy(data->result + data->result_pos, str, len + 1);
	data->result_pos += len;
}

// Fonction principale d'expansion
char	*expand_variables(const char *line, t_data shell)
{
	size_t			i;
	size_t			n_len;
	t_expand_data	*data;
	char			*result;

	if (!line)
		return (NULL);
	n_len = expanded_len(line, shell.exec->envp, shell.exec->last_exit_status);
	data = init_expand_data(shell, n_len);
	if (!data)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
			handle_var_exp(line, &i, data);
		else
			handle_char(line, &i, data);
	}
	data->result[data->result_pos] = '\0';
	result = data->result;
	data->result = NULL;
	free_expand_data(data);
	return (result);
}
