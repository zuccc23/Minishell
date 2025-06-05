#include "../../include/minishell.h"

//export a variable in the environment
int	bltin_export(t_command *cmd, char ***env)
{
	int	i;

	i = 1;
	if (!cmd->args[i])
		return (ER_OK);
	while (cmd->args[i])
	{

		if (get_new_env(&(*env), cmd->args[i]) == 1)
			return (1);
		i++;
	}
	// print_strs(*env);
	// get_new_env(&(*env), cmd->args[1]);
	print_strs(*env);
	return (ER_OK);
}

int	get_new_env(char ***env, char *cmd)
{
	char	**tmp;

	tmp = copy_and_add(*env, cmd);
	if (!tmp)
		return (1);
	free_strs(*env);
	*env = tmp;
	return (ER_OK);
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

int	count_strings(char **strs)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!strs)
		return (0);
	while (strs[i])
	{
		count++;
		i++;
	}
	return (count);
}

//checks if the export is correct format (var=value)
//returns 0 if ok, 1 if not
int	check_export(char *cmd)
{
	int	i;

	i = 0;
	if (ft_isalnum(cmd[0])  )
	while (cmd[i])
	{
		if 
		i++;
	}
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
