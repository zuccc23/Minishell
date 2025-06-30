#include "../../include/minishell.h"

//count strings in a char**
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
int	check_args(char **args)
{
	if (args[1])
		return (ER_OK);
	if (invalid_option(args, "env") == 2)
		return (2);
	return (0);
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
		if (ft_isalnum(cmd[i]) == 0 && cmd[i] != '_' && cmd[i] != '=' \
		&& cmd[i] != ' ' && cmd[i] != '/' && is_ok_dash(cmd[i], count) != 1)
			return (1);
		if (cmd[i] == '=')
			count = 1;
		i++;
	}
	if (count == 0)
		return (2);
	return (0);
}

//returns 1 if ok -, 0 if not
int	is_ok_dash(char c, int count)
{
	if (c == '-' && count == 1)
		return (1);
	if (c == '-' && count == 0)
		return (0);
	return (0);
}
