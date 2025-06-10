#include "../../include/minishell.h"

//export a variable in the environment
int	bltin_export(t_command *cmd, char ***env)
{
	int	er_code;
	int	i;

	er_code = 0;
	i = 1;
	if (check_args(cmd) == 2)
		return (2);
	while (cmd->args[i])
	{
		while (cmd->args[i] && check_export(cmd->args[i]) != 0)
		{
			if (check_export(cmd->args[i]) == 1)
			{
				ft_printf("minishell: export: %s:", cmd->args[i]);
				ft_printf(" not a valid identifier\n");
				er_code = 1;
			}
			i++;
		}
		if (cmd->args[i] && get_new_env(&(*env), cmd->args[i]) == 1)
			return (1);
		if (cmd->args[i])
			i++;
	}
	return (er_code);
}

// changes the current env to the new one with the added variable
int	get_new_env(char ***env, char *cmd)
{
	char	**tmp;
	int		i;

	i = 0;
	while ((*env)[i])
	{
		if (is_same_var_exp((*env)[i], cmd) == 1)
		{
			tmp = copy_and_replace(*env, cmd);
			if (!tmp)
				return (1);
			free_strs(*env);
			*env = tmp;
			return (ER_OK);
		}
		i++;
	}
	tmp = copy_and_add(*env, cmd);
	if (!tmp)
		return (1);
	free_strs(*env);
	*env = tmp;
	return (ER_OK);
}

int	is_same_var_exp(char *str1, char *str2)
{
	size_t	len;
	size_t	len2;

	len = char_position(str1, '=');
	len2 = char_position(str2, '=');
	if (len == 0 || len2 == 0)
		return (0);
	if (ft_strncmp(str1, str2, len) == 0 \
		&& len == len2)
		return (1);
	return (0);
}

//check for empty args or invalid options
int	check_args(t_command *cmd)
{
	if (!cmd->args[1])
		return (ER_OK);
	if (invalid_option(cmd->args, "env") == 2)
		return (2);
	return (0);
}

char	**copy_and_replace(char **env, char *cmd)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * (count_strings(env) + 1));
	if (!tmp)
		return (NULL);
	while (env[i])
	{
		if (is_same_var_exp(env[i], cmd) == 1)
			tmp[i] = ft_strdup(cmd);
		else
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

//copy the env and add the variable to it
//takes command->args[i] as parameter
char	**copy_and_add(char **env, char *cmd)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * (count_strings(env) + 2));
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
	tmp[i] = ft_strdup(cmd);
	if (!tmp[i])
	{
		free_strs(tmp);
		return (NULL);
	}
	tmp[i+1] = NULL;
	return (tmp);
}

//checks if the export is correct format (var=value)
//returns 0 if ok, 1 if not
int	check_export(char *cmd)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (ft_isalpha(cmd[0]) == 0 && cmd[0] != '_')
		return (1);
	while (cmd[i])
	{
		if (ft_isalnum(cmd[i]) == 0 && cmd[i] != '_'&& cmd[i] != '=')
			return (1);
		if (cmd[i] == '=')
			count = 1;
		i++;
	}
	if (count == 0)
		return (2);
	return (0);
}

char	**copy_env(char **env)
{
	char	**tmp;
	int		i;

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
