/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_exp_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:33:56 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:33:57 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Traite l'expansion d'une variable d'environnement
void	handle_env_var(const char *line, size_t *i, t_expand_data *data)
{
	int		var_len;
	char	*var_name;
	char	*var_value;

	var_len = get_var_name_len(line, *i);
	var_name = ft_substr(line, *i, var_len);
	if (!var_name)
		return ;
	var_value = get_env_value(var_name, data->envp);
	copy_to_result(data, var_value);
	*i += var_len;
	free(var_name);
}

// Traite un dollar non reconnu (copie littéralement)
static void	hdl_literal_dollar(const char *line, size_t *i, t_expand_data *data)
{
	data->result[data->result_pos++] = '$';
	data->result[data->result_pos++] = line[*i];
	(*i)++;
}

// Traite l'expansion d'une variable ($ suivi de quelque chose)
void	handle_var_exp(const char *line, size_t *i, t_expand_data *data)
{
	(*i)++;
	if (line[*i] == '?')
		handle_exit_code(line, i, data);
	else if (ft_isalpha(line[*i]) || line[*i] == '_')
		handle_env_var(line, i, data);
	else
		hdl_literal_dollar(line, i, data);
}

// Copie un caractère normal dans le résultat
void	handle_char(const char *line, size_t *i, t_expand_data *data)
{
	data->result[data->result_pos++] = line[*i];
	(*i)++;
}

// Libère les données d'expansion
void	free_expand_data(t_expand_data *data)
{
	if (data)
	{
		free(data->exit_str);
		free(data);
	}
}
