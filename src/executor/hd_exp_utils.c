#include "../../include/minishell.h"

// Convertit le code d'erreur et calcule la taille après expansion
size_t	expanded_len(const char *line, char **env, int error_code)
{
	size_t	len;
	char	*exit_str;

	exit_str = ft_itoa(error_code);
	if (!exit_str)
		return (ft_strlen(exit_str));
	len = find_expd_len(line, env, exit_str);
	free(exit_str);
	return (len);
}

// Ajoute la longueur du code de sortie au calcul de taille
void	exit_code_len(int *i, size_t *len, const char *exit_str)
{
	*len += ft_strlen(exit_str);
	(*i)++;
}

// Ajoute 2 caractères pour les dollars non reconnus au calcul
void	unknown_dollar_len(size_t *len, int *i)
{
	*len += 2;
	(*i)++;
}

// Calcule la longueur d'un nom de variable ou retourne 1 pour '$?'
int	get_var_name_len(const char *str, int start)
{
	int	len;

	len = 0;
	if (str[start] == '?')
		return (1);
	while (str[start + len] && (ft_isalnum(str[start + len])
			|| str[start + len] == '_'))
		len++;
	return (len);
}

// Ajoute la longueur de la valeur d'une variable au calcul de taille
void	hdle_env_var_len(const char *line, int *i, size_t *len, char **env)
{
	int		var_len;
	char	*var_name;
	char	*var_value;

	var_len = get_var_name_len(line, *i);
	var_name = ft_substr(line, *i, var_len);
	var_value = get_env_value(var_name, env);
	*len += ft_strlen(var_value);
	free(var_name);
	*i += var_len;
}
