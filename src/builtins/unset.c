#include "../../include/minishell.h"

//unsets/remove a variable form env
//  Unsetting a variable or function that was not previously set shall
//  not be considered an error and does not cause the shell to abort.
//  0    All name operands were successfully unset.
// >0    At least one name could not be unset.
int	bltin_unset(t_command *cmd, char ***env)
{
	int	er_code;
	int	i;

	er_code = 0;
	i = 1;
	if (!cmd->args[i])
		return (ER_OK);
	if (invalid_option(cmd->args, "unset") == 2)
		return (2);
	while (cmd->args[i])
	{
		if (cmd->args[i] && get_new_env_unset(&(*env), cmd->args[i]) == 1)
			return (1);
		if (cmd->args[i])
			i++;
	}
	return (er_code);
}

// changes the current env to the new one with the removed variable
int	get_new_env_unset(char ***env, char *cmd)
{
	char	**tmp;
	int		i;
	int		var_exists;

	i = 0;
	var_exists = 0;
	while ((*env)[i])
	{
		if (is_same_var((*env)[i], cmd) == 1)
			var_exists = 1;
		i++;
	}
	if (var_exists == 0)
		return (ER_OK);
	tmp = copy_and_remove(*env, cmd);
	if (!tmp)
		return (1);
	free_strs(*env);
	*env = tmp;
	return (ER_OK);
}

//copy the env and add the variable to it
//takes command->args[i] as parameter
char	**copy_and_remove(char **env, char *cmd)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char *) * (count_strings(env)));
	if (!tmp)
		return (NULL);
	while (env[i])
	{
		if (is_same_var(env[i], cmd) == 0)
		{
			tmp[j] = ft_strdup(env[i]);
			if (!tmp[j])
			{
				free_strs(tmp);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

//returns 1 if same vars, 0 if not
//str1 = env
//str2 = variable name you want to check
int	is_same_var(char *str1, char *str2)
{
	size_t	len;

	len = char_position(str1, '=');
	if (len == 0)
		return (0);
	if (ft_strncmp(str1, str2, len) == 0 \
&& len == ft_strlen(str2))
		return (1);
	return (0);
}

//returns the position of char c in string str
size_t	char_position(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}
