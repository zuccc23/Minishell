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

//copy the env and replace the right variable
//takes command->args[i] as parameter
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
	tmp[i + 1] = NULL;
	return (tmp);
}

//delete later
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
