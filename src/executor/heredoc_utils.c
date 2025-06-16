#include "../../include/minishell.h"

static char	*get_env_value(const char *var_name, t_env *env)
{
	t_env	*tmp;
	char	*equals_pos;
	size_t	var_len;

	var_len = ft_strlen(var_name);
	tmp = env;
	while (tmp)
	{
		equals_pos = ft_strchr(tmp->value, '=');
		if (equals_pos)
		{
			if (ft_strncmp(tmp->value, var_name, var_len) == 0
				&& tmp->value[var_len] == '=')
				return (equals_pos + 1);
		}
		tmp = tmp->next;
	}
	return ("");
}

static int	get_var_name_len(const char *str, int start)
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

static size_t	expanded_len(const char *line, t_env *env, int error_code)
{
	size_t	len;
	int		i;
	char	*exit_str;

	len = 0;
	i = 0;
	exit_str = ft_itoa(error_code);
	if (!exit_str)
		return (ft_strlen(exit_str));
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
		{
			i++;
			if (line[i] == '?')
			{
				len += ft_strlen(exit_str);
				i++;
			}
			else if (ft_isalpha(line[i]) || line[i] == '_')
			{
				int var_len = get_var_name_len(line, i);
				char *var_name = ft_substr(line, i, var_len);
				char *var_value = get_env_value(var_name, env);
				len += ft_strlen(var_value);
				free(var_name);
				i += var_len;
			}
			else
			{
				len += 2;
				i++;
			}
		}
		else
		{
			len++;
			i++;
		}
	}
	free(exit_str);
	return (len);
}

char *expand_variables(const char *line, t_env *env, int error_code)
{
	size_t	i;
	size_t	j;
	char	*res;
	char	*exit_str;
	size_t	new_len;

	if (!line)
		return (NULL);
	i = 0;
	j = 0;
	exit_str = ft_itoa(error_code);
	new_len = expanded_len(line, env, error_code);
	res = malloc(sizeof(char) * (new_len + 1));
	if (!res || !exit_str)
		return (free(exit_str), NULL);
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
		{
			i++;
			if (line[i] == '?')
			{
				j += ft_strlcpy(res + j, exit_str, ft_strlen(exit_str) + 1);
				//j += ft_strlen(exit_str);
				i++;
			}
			else if (ft_isalpha(line[i]) || line[i] == '_')
			{
				int var_len = get_var_name_len(line, i);
				char *var_name = ft_substr(line, i, var_len);
				char *var_value = get_env_value(var_name, env);

				j += ft_strlcpy(res + j, var_value, ft_strlen(var_value) + 1);
				// j += ft_strlen(var_value);
				i += var_len;
				free(var_name);
			}
			else
			{
				res[j++] = '$';
				res[j++] = line[i++];
			}
		}
		else
			res[j++] = line[i++];
	}
	res[j] = '\0';
	free(exit_str);
	return (res);
}
